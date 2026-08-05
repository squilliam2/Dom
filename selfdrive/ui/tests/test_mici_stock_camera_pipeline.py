import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).parents[3]


def test_mici_uses_the_dedicated_stock_renderer():
  mici = (ROOT / "selfdrive/ui/mici/onroad/cameraview.py").read_text()
  upstream_mici = mici.replace(
    "from openpilot.system.hardware import TICI",
    "from openpilot.common.hardware import TICI",
  ).encode()
  upstream_blob = hashlib.sha1(f"blob {len(upstream_mici)}\0".encode() + upstream_mici).hexdigest()

  assert "class CameraView(Widget)" in mici
  assert "SharedCameraView" not in mici
  assert "def _update_texture_color_filtering" in mici
  assert "bind_egl_image_to_texture(self.egl_texture.id, egl_image)" in mici
  assert "def _fallback_to_textures" not in mici
  assert "MICI_FORCE_TEXTURE_CAMERA" not in mici
  assert upstream_blob == "4a31a9e04e5d55891eb2aa535c1cc4b171a32b98"


def test_mici_renderer_keeps_stock_engagement_color_states():
  mici = (ROOT / "selfdrive/ui/mici/onroad/cameraview.py").read_text()

  assert mici.count("uniform int engaged;") == 2
  assert mici.count("if (engaged == 1)") == 2
  assert mici.count("*= 0.85;") == 2
  assert "ui_state.status != UIStatus.DISENGAGED" in mici


def test_mici_uses_stock_agnos_18_5_partitions_with_compatible_system():
  default_manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  mici_manifest = json.loads((ROOT / "system/hardware/tici/agnos-mici.json").read_text())
  default_system = next(partition for partition in default_manifest if partition["name"] == "system")
  mici_system = next(partition for partition in mici_manifest if partition["name"] == "system")

  assert "dropbox.com" in default_system["url"]
  assert default_system["hash_raw"] == "4c01245932068aedfceb41cb1aab1f7f044f6659aa2fe2de558f99e2d3aa5793"
  assert mici_system["url"] == (
    "https://github.com/squilliam2/openpilot/releases/download/agnos-sq-mici-18.5.2/"
    "agnos-18.5-sq-mici.2.raw.img.xz"
  )
  assert mici_system["hash"] == "47c5539a9ab6027d5a4265dabef16339cd5eecae4f67589f23e85881f2b96538"
  assert mici_system["hash_raw"] == mici_system["hash"]
  assert mici_system["size"] == 4718592000
  assert not mici_system["sparse"]
  assert not mici_system["full_check"]
  assert "alt" not in mici_system
  assert "ondevice_hash" not in mici_system

  assert {partition["name"] for partition in mici_manifest} == {
    "xbl", "xbl_config", "abl", "aop", "devcfg", "boot", "system",
  }
  stock_partition_hashes = {
    "xbl": "e8acf2a9cc7f0ce84cb803bfea9477f765c0d7b4daf26048e59651b9e6a7bfbb",
    "xbl_config": "758552ecf92b5569677197783bf0ccb73d7f961685308e45d3276ac9dd974f85",
    "abl": "b6fba807b9bcd66a31f2afb0eba5163ec239693ad32e2e4200f6c356adfe098c",
    "aop": "78b2287ca219a0811b3004c523fa0f4749e4d1fd92be3aba61699305b7943ad1",
    "devcfg": "f71df3a86958c093ba3969254c4db025187eef9385427f1ade946742939b43cc",
    "boot": "19ff57b68e219e4503fcaca716967098d5d0a1de8af833f04dbf13b99aeb4d39",
  }
  assert {
    partition["name"]: partition["hash_raw"]
    for partition in mici_manifest if partition["name"] != "system"
  } == stock_partition_hashes


def test_agnos_target_is_strictly_selected_by_physical_device_type():
  launch_env = (ROOT / "launch_env.sh").read_text()

  assert 'SP_DEVICE_TYPE=""' in launch_env
  assert 'SP_DEVICE_TYPE="${SP_DEVICE_TYPE##*comma }"' in launch_env
  assert launch_env.rindex('SP_DEVICE_TYPE=""') > launch_env.index("starpilot/system/environment_variables")
  assert 'if [ "$SP_DEVICE_TYPE" = "mici" ]' in launch_env
  assert 'export SP_AGNOS_TARGET_VERSION="18.5-sq-mici.2"' in launch_env
  assert 'export SP_AGNOS_MANIFEST="system/hardware/tici/agnos-mici.json"' in launch_env
  assert 'export SP_AGNOS_TARGET_VERSION="$AGNOS_VERSION"' in launch_env
  assert 'export SP_AGNOS_MANIFEST="system/hardware/tici/agnos.json"' in launch_env


def test_no_custom_color_or_panel_calibration_is_layered_on_top():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  repository_text = "\n".join(
    (ROOT / relative_path).read_text()
    for relative_path in (
      "launch_chffrplus.sh",
      "launch_env.sh",
      "system/updated/updated.py",
    )
  )

  assert "disable_mici_weston_color_correction" not in repository_text
  assert "apply_mici_screen_calibration" not in repository_text
  assert "DISABLE_COLOR_CORRECTION" not in repository_text
  assert "systemctl restart --no-block weston.service" not in repository_text
  assert "SP_AGNOS_ACCEPTED_VERSIONS" in launcher
  assert 'MANIFEST="$DIR/$SP_AGNOS_MANIFEST"' in launcher


def test_background_updater_and_galaxy_use_the_selected_manifest():
  updated = (ROOT / "system/updated/updated.py").read_text()
  galaxy = (ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text()

  assert "SP_AGNOS_TARGET_VERSION" in updated
  assert "SP_AGNOS_MANIFEST" in updated
  assert '"system/hardware/tici/agnos-mici.json"' in updated
  assert '_AGNOS_MICI_MANIFEST_PATH = "system/hardware/tici/agnos-mici.json"' in galaxy
  assert 'os.getenv("SP_AGNOS_MANIFEST", _AGNOS_DEFAULT_MANIFEST_PATH)' in galaxy
  assert "_AGNOS_ALLOWED_MANIFEST_PATHS" in galaxy


def test_other_devices_keep_dom_camera_and_agnos_paths():
  shared = (ROOT / "selfdrive/ui/onroad/cameraview.py").read_text()
  application = (ROOT / "system/ui/lib/application.py").read_text()

  assert "def _fallback_to_textures" in shared
  assert "def _accept_frame" in shared
  assert 'MICI_FORCE_RENDER_TEXTURE = os.getenv("MICI_FORCE_RENDER_TEXTURE", "1" if DEVICE_TYPE == "mici" else "0") == "1"' in application
  assert not (ROOT / "system/ui/lib/egl_mici.py").exists()
