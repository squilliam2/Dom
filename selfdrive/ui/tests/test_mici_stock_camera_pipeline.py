import json
from pathlib import Path

ROOT = Path(__file__).parents[3]


def test_mici_keeps_dom_camera_lifecycle_with_stock_color_states():
  wrapper = (ROOT / "selfdrive/ui/mici/onroad/cameraview.py").read_text()
  shared = (ROOT / "selfdrive/ui/onroad/cameraview.py").read_text()

  assert "class CameraView(SharedCameraView)" in wrapper
  assert "_use_upstream_engaged_color = True" in wrapper
  assert "def _fallback_to_textures" in shared
  assert "def _accept_frame" in shared
  assert "def _reset_camera_connection" in shared
  assert "FRAME_FRAGMENT_SHADER_EXTERNAL_MICI" in shared
  assert "FRAME_FRAGMENT_SHADER_YUV_MICI" in shared
  assert shared.count("uniform int engaged;") == 2
  assert shared.count("if (engaged == 1)") == 2
  assert shared.count("*= 0.85;") >= 2
  assert "ui_state.status != UIStatus.DISENGAGED or ui_state.always_on_lateral_active" in shared


def test_mici_keeps_dom_egl_recovery_implementation():
  assert not (ROOT / "system/ui/lib/egl_mici.py").exists()
  egl = (ROOT / "system/ui/lib/egl.py").read_text()
  assert "def create_external_texture" in egl
  assert "def destroy_external_texture" in egl
  assert "def finish_gl" in egl


def test_mici_gets_a_patched_dom_image_while_other_devices_keep_the_original():
  default_manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  mici_manifest = json.loads((ROOT / "system/hardware/tici/agnos-mici.json").read_text())
  default_system = next(partition for partition in default_manifest if partition["name"] == "system")
  mici_system = next(partition for partition in mici_manifest if partition["name"] == "system")

  assert "dropbox.com" in default_system["url"]
  assert default_system["hash_raw"] == "4c01245932068aedfceb41cb1aab1f7f044f6659aa2fe2de558f99e2d3aa5793"
  assert "agnos-sq-mici-12.8.28.1" in mici_system["url"]
  assert mici_system["hash"] == "14ff858e40e4a2df0883f8029ae649ea069d302e5ceef59e483230c87b7e2361"
  assert mici_system["hash_raw"] == mici_system["hash"]
  assert mici_system["size"] == 5368709120
  assert not mici_system["sparse"]

  default_by_name = {partition["name"]: partition for partition in default_manifest}
  mici_by_name = {partition["name"]: partition for partition in mici_manifest}
  assert default_by_name.keys() == mici_by_name.keys()
  assert all(default_by_name[name] == mici_by_name[name] for name in default_by_name if name != "system")


def test_agnos_target_is_strictly_selected_by_physical_device_type():
  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'SP_DEVICE_TYPE=""' in launch_env
  assert 'SP_DEVICE_TYPE="${SP_DEVICE_TYPE##*comma }"' in launch_env
  assert 'if [ -z "$SP_DEVICE_TYPE" ]' not in launch_env
  assert launch_env.rindex('SP_DEVICE_TYPE=""') > launch_env.index("starpilot/system/environment_variables")
  assert 'export AGNOS_VERSION="12.8.28"' in launch_env
  assert 'if [ "$SP_DEVICE_TYPE" = "mici" ]' in launch_env
  assert 'export SP_AGNOS_TARGET_VERSION="12.8.28-sq-mici.1"' in launch_env
  assert 'export SP_AGNOS_MANIFEST="system/hardware/tici/agnos-mici.json"' in launch_env
  assert 'export SP_AGNOS_TARGET_VERSION="$AGNOS_VERSION"' in launch_env
  assert 'export SP_AGNOS_MANIFEST="system/hardware/tici/agnos.json"' in launch_env


def test_camera_fix_adds_no_runtime_weston_restart_or_panel_calibration():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  assert "disable_mici_weston_color_correction" not in launcher
  assert "apply_mici_screen_calibration" not in launcher
  assert "systemctl restart --no-block weston.service" not in launcher
  assert "/run/systemd/system/weston.service.d" not in launcher
  assert "SP_AGNOS_ACCEPTED_VERSIONS" in launcher
  assert 'MANIFEST="$DIR/$SP_AGNOS_MANIFEST"' in launcher


def test_background_updater_and_galaxy_use_the_selected_manifest():
  updated = (ROOT / "system/updated/updated.py").read_text()
  assert "SP_AGNOS_TARGET_VERSION" in updated
  assert "SP_AGNOS_MANIFEST" in updated
  assert '"system/hardware/tici/agnos-mici.json"' in updated
  assert "manifest_relative_path" in updated

  galaxy = (ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text()
  assert '_AGNOS_MICI_MANIFEST_PATH = "system/hardware/tici/agnos-mici.json"' in galaxy
  assert 'os.getenv("SP_AGNOS_MANIFEST", _AGNOS_DEFAULT_MANIFEST_PATH)' in galaxy
  assert "_AGNOS_ALLOWED_MANIFEST_PATHS" in galaxy


def test_dom_runtime_processes_remain_unchanged_by_the_agnos_split():
  forbidden_paths = (
    "system/camerad/camerad_mici",
    "system/loggerd/loggerd_mici",
    "system/loggerd/encoderd_mici",
    "system/loggerd/bootlog_mici",
    "selfdrive/pandad/pandad_mici",
    "selfdrive/pandad/pandad_api_impl_mici.so",
    "selfdrive/modeld/models/mici/commonmodel_pyx.so",
    "system/hardware/tici/device_config.py",
  )
  assert not any((ROOT / relative_path).exists() for relative_path in forbidden_paths)

  process_config = (ROOT / "system/manager/process_config.py").read_text()
  assert 'NativeProcess("camerad", "system/camerad", ["./camerad"]' in process_config
  assert "runtime_executable" not in process_config

  galaxy = (ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text()
  assert "hardware.tici.device_config" not in galaxy
  assert '_AGNOS_DEFAULT_MANIFEST_PATH = "system/hardware/tici/agnos.json"' in galaxy


def test_mici_uses_stock_direct_rendering_with_dom_frame_limiter():
  application = (ROOT / "system/ui/lib/application.py").read_text()
  assert 'MICI_FORCE_RENDER_TEXTURE = os.getenv("MICI_FORCE_RENDER_TEXTURE", "0") == "1"' in application
  assert '"0" if PC or DEVICE_TYPE == "mici" else "1"' in application
  assert 'rl.set_target_fps(0 if OFFSCREEN else fps)' in application
  assert 'vblank_control = DEVICE_TYPE == "mici"' not in application
