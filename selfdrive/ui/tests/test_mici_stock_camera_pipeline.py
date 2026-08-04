import hashlib
import json
from pathlib import Path

import pytest


ROOT = Path(__file__).parents[3]

STOCK_MICI_FILES = {
  "selfdrive/ui/mici/onroad/cameraview.py": "4ca438be9e2cd2c6ed27fc26424622c75a3b9398f4bd55ff77b52e0823a3d9e4",
  "system/ui/lib/egl.py": "586de0f96d508848d289ed8c7cca556ac289738e7878fec6fac302137081d09c",
  "system/camerad/cameras/bps_blobs.h": "d8a2d426c7578d59b30b527b47192583db55aa5a6bef36c0b51ffc979dd53364",
  "system/camerad/sensors/os04c10.cc": "8a3463b7c2c38492a0d9fc648c5444b91882cb7294b2523c0eda476d6a4b5ef6",
  "system/camerad/sensors/ox03c10.cc": "205f915afc2422358c1cbc26d69b98da0b4ee0571c3fc79595dc4acee8231877",
  "system/hardware/tici/agnos.json": "c6977d057f66f5b05553a337fc7580f81e9492f44418c9a781460f3c172f3b84",
}


@pytest.mark.parametrize(("relative_path", "expected_hash"), STOCK_MICI_FILES.items())
def test_mici_camera_runtime_matches_stock_openpilot(relative_path: str, expected_hash: str):
  contents = (ROOT / relative_path).read_bytes().replace(b"\r\n", b"\n")
  assert hashlib.sha256(contents).hexdigest() == expected_hash


def test_mici_uses_stock_agnos_18_4():
  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'export AGNOS_VERSION="18.4"' in launch_env

  manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  system_partition = next(partition for partition in manifest if partition["name"] == "system")
  assert system_partition["url"].startswith("https://commadist.azureedge.net/agnosupdate/")
  assert "dropbox.com" not in system_partition["url"]


def test_custom_display_calibration_is_removed_during_migration():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  assert "/data/misc/display/color_cal/color_cal" in launcher
  assert "/cache/starpilot/stock_camera_pipeline_18_4" in launcher


def test_mici_uses_stock_direct_framebuffer_presentation():
  application = (ROOT / "system/ui/lib/application.py").read_text()

  assert 'MICI_FORCE_RENDER_TEXTURE = os.getenv("MICI_FORCE_RENDER_TEXTURE", "0") == "1"' in application
  assert '"0" if PC or DEVICE_TYPE == "mici" else "1"' in application
  assert 'vblank_control = DEVICE_TYPE == "mici"' in application
  assert 'rl.set_target_fps(0 if OFFSCREEN or vblank_control else fps)' in application


def test_camerad_transport_adapter_preserves_stock_image_layout():
  common = (ROOT / "system/camerad/cameras/camera_common.cc").read_text()
  qcom = (ROOT / "system/camerad/cameras/camera_qcom2.cc").read_text()

  assert "cam->yuv_size" in common
  assert "2900" not in common
  assert "init_cl(device_id, context)" in common
  assert 'VisionIpcServer v("camerad", device_id, ctx)' in qcom


def test_stock_agnos_runtime_is_prebuilt_without_legacy_dom_dependencies():
  assert (ROOT / "prebuilt").exists()

  binaries = (
    "system/camerad/camerad",
    "system/loggerd/loggerd",
    "system/loggerd/encoderd",
    "system/loggerd/bootlog",
    "selfdrive/pandad/pandad",
    "selfdrive/pandad/pandad_api_impl.so",
    "selfdrive/modeld/models/commonmodel_pyx.so",
  )
  forbidden_dependencies = (
    b"libavformat.so.58",
    b"libavcodec.so.58",
    b"libavutil.so.56",
    b"libcapnp-1.0.2.so",
    b"libkj-1.0.2.so",
    b"libOmxCore.so",
  )

  for relative_path in binaries:
    contents = (ROOT / relative_path).read_bytes()
    assert contents.startswith(b"\x7fELF")
    assert not any(dependency in contents for dependency in forbidden_dependencies)
