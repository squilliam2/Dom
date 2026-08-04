import hashlib
import json
from pathlib import Path

import pytest


ROOT = Path(__file__).parents[3]


def normalized_sha256(relative_path: str, replacements: tuple[tuple[bytes, bytes], ...] = ()) -> str:
  contents = (ROOT / relative_path).read_bytes().replace(b"\r\n", b"\n")
  for old, new in replacements:
    contents = contents.replace(old, new)
  return hashlib.sha256(contents).hexdigest()


def binary_sha256(relative_path: str) -> str:
  return hashlib.sha256((ROOT / relative_path).read_bytes()).hexdigest()


DOM_RUNTIME_BINARIES = {
  "system/camerad/camerad": "95103c82e713a83c7cd5ec3750d91fabd811b28a2eef7db653ff048e735ffb18",
  "system/loggerd/loggerd": "ca020e1fc7ab68def3c64510c0407ddd0e0e0a7b27a9d84793b6c3b0d88e9e1e",
  "system/loggerd/encoderd": "8121a57db53ad1b61d60e89a82628182640a4e131a68d94163e3c4510b634abf",
  "system/loggerd/bootlog": "4988a450d97fca585a64a89324b4fdb9e7c2c32de6fc9c3ad1509f8a1dc9f43c",
  "selfdrive/pandad/pandad": "f90f891ac2e972987a270984c2a5d9872d93ac2455f56f3b96a324d266725433",
  "selfdrive/pandad/pandad_api_impl.so": "0d41667a30493489b2b00fbf5f59bcf08566007312f20d7a20025c4db545d6f5",
  "selfdrive/modeld/models/commonmodel_pyx.so": "bdac6d07e9287bc68b36afc1610e1d12d0f25874fd19e6b7703a1fe9adb1f5f6",
}


def test_mici_camera_renderer_matches_stock_openpilot_and_sunnypilot():
  replacements = ((b"openpilot.system.ui.lib.egl_mici", b"openpilot.system.ui.lib.egl"),)
  assert normalized_sha256("selfdrive/ui/mici/onroad/cameraview.py", replacements) == (
    "4ca438be9e2cd2c6ed27fc26424622c75a3b9398f4bd55ff77b52e0823a3d9e4"
  )


def test_mici_egl_matches_stock_openpilot_and_sunnypilot():
  assert normalized_sha256("system/ui/lib/egl_mici.py") == (
    "586de0f96d508848d289ed8c7cca556ac289738e7878fec6fac302137081d09c"
  )


def test_dom_custom_agnos_remains_active_for_every_device():
  assert normalized_sha256("system/hardware/tici/agnos.json") == (
    "4b67785d0518a131ce641aac2578b579be85cffd59c36d557b66d5885c86dc9a"
  )
  assert not (ROOT / "system/hardware/tici/agnos-mici.json").exists()

  manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  system_partition = next(partition for partition in manifest if partition["name"] == "system")
  assert "dropbox.com" in system_partition["url"]

  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'export AGNOS_VERSION="12.8.28"' in launch_env
  assert "18.4" not in launch_env
  assert "agnos-mici.json" not in launch_env


def test_screen_calibration_is_strictly_mici_only():
  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'SP_DEVICE_TYPE="${SP_DEVICE_TYPE##*comma }"' in launch_env

  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  function_start = launcher.index("function apply_mici_screen_calibration")
  function_end = launcher.index("\n}\n", function_start)
  calibration_function = launcher[function_start:function_end]

  assert '[ "${SP_DEVICE_TYPE:-}" = "mici" ] || return 0' in calibration_function
  assert 'local calibration_script="/usr/comma/screen_calibration.py"' in calibration_function
  assert "/persist/comma/dwo_gamma_curves" in calibration_function
  assert 'local stock_calibration_unit="screen_calibration.service"' in calibration_function
  assert "/usr/bin/systemd-run" in calibration_function
  assert "--service-type=oneshot" in calibration_function
  assert "--remain-after-exit" in calibration_function
  assert "--property=After=multi-user.target" in calibration_function
  assert "--no-block" in calibration_function
  assert "sleep " not in calibration_function
  assert "rm -f /persist/comma/dwo_gamma_curves" not in launcher
  assert launcher.count("apply_mici_screen_calibration") == 2
  update_block = launcher.index('if [ "$AGNOS_UPDATE_REQUIRED" = "1" ]')
  assert launcher.index("apply_mici_screen_calibration", function_end) > update_block


def test_legacy_weston_color_correction_is_disabled_only_on_mici():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  function_start = launcher.index("function disable_mici_weston_color_correction")
  function_end = launcher.index("\n}\n", function_start)
  correction_function = launcher[function_start:function_end]

  assert '[ "${SP_DEVICE_TYPE:-}" = "mici" ] || return 0' in correction_function
  assert "systemctl is-active --quiet weston.service || return 0" in correction_function
  assert "systemctl is-active --quiet weston-ready.service || return 0" in correction_function
  assert "/usr/lib/arm-linux-gnueabihf/weston/gl-renderer.so" in correction_function
  assert "grep -aq 'DISABLE_COLOR_CORRECTION'" in correction_function
  assert 'Environment="DISABLE_COLOR_CORRECTION=1"' in correction_function
  assert "/run/systemd/system/weston.service.d" in launcher
  assert "systemctl restart weston.service" in correction_function
  assert "systemctl restart weston-ready.service" in correction_function
  assert "mici_weston_has_color_correction_disabled" in correction_function
  assert "/data/misc/display/color_cal/color_cal" in correction_function
  assert "/persist/comma/color_cal" not in launcher
  assert "/etc/systemd/system" not in launcher


def test_weston_color_change_rolls_back_and_precedes_panel_calibration():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  rollback_start = launcher.index("function restore_mici_weston_color_correction")
  rollback_end = launcher.index("\n}\n", rollback_start)
  rollback_function = launcher[rollback_start:rollback_end]

  assert 'rm -f "$MICI_WESTON_COLOR_DROPIN"' in rollback_function
  assert "systemctl daemon-reload" in rollback_function
  assert "systemctl restart weston.service" in rollback_function
  assert "wait_for_mici_weston" in rollback_function

  call_start = launcher.index('if [ "$AGNOS_UPDATE_REQUIRED" = "1" ]')
  disable_call = launcher.index("disable_mici_weston_color_correction", call_start)
  calibration_call = launcher.index("apply_mici_screen_calibration", call_start)
  assert disable_call < calibration_call


@pytest.mark.parametrize(("relative_path", "expected_hash"), DOM_RUNTIME_BINARIES.items())
def test_camera_and_runtime_binaries_remain_dom_builds(relative_path: str, expected_hash: str):
  assert binary_sha256(relative_path) == expected_hash


def test_no_stock_agnos_runtime_split_remains():
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
  assert '_AGNOS_MANIFEST_PATH = "system/hardware/tici/agnos.json"' in galaxy


def test_mici_uses_stock_direct_rendering_with_dom_frame_limiter():
  application = (ROOT / "system/ui/lib/application.py").read_text()
  assert 'MICI_FORCE_RENDER_TEXTURE = os.getenv("MICI_FORCE_RENDER_TEXTURE", "0") == "1"' in application
  assert '"0" if PC or DEVICE_TYPE == "mici" else "1"' in application
  assert 'rl.set_target_fps(0 if OFFSCREEN else fps)' in application
  assert 'vblank_control = DEVICE_TYPE == "mici"' not in application
