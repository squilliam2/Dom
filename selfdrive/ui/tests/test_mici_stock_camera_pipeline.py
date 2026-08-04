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


def test_dom_custom_agnos_remains_active_for_every_device():
  assert not (ROOT / "system/hardware/tici/agnos-mici.json").exists()

  manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  system_partition = next(partition for partition in manifest if partition["name"] == "system")
  assert "dropbox.com" in system_partition["url"]

  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'export AGNOS_VERSION="' in launch_env
  assert "agnos-mici.json" not in launch_env


def test_screen_calibration_is_strictly_mici_only():
  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'SP_DEVICE_TYPE=""' in launch_env
  assert 'SP_DEVICE_TYPE="${SP_DEVICE_TYPE##*comma }"' in launch_env
  assert 'if [ -z "$SP_DEVICE_TYPE" ]' not in launch_env
  assert launch_env.rindex('SP_DEVICE_TYPE=""') > launch_env.index("starpilot/system/environment_variables")

  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  function_start = launcher.index("function apply_mici_screen_calibration")
  function_end = launcher.index("\n}\n", function_start)
  calibration_function = launcher[function_start:function_end]

  assert '[ "${SP_DEVICE_TYPE:-}" = "mici" ] || return 0' in calibration_function
  assert 'local calibration_script="/usr/comma/screen_calibration.py"' in calibration_function
  assert "/persist/comma/dwo_gamma_curves" in calibration_function
  assert "/sys/kernel/debug/dsi_dwo_video_display/mipi_command" in calibration_function
  assert 'sudo /usr/bin/timeout --signal=TERM --kill-after=1s 10s "$calibration_script"' in calibration_function
  assert 'touch "$MICI_SCREEN_CALIBRATION_MARKER"' in calibration_function
  assert "/usr/bin/systemd-run" not in calibration_function
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
  assert "/usr/lib/arm-linux-gnueabihf/weston/gl-renderer.so" in correction_function
  assert "grep -aq 'DISABLE_COLOR_CORRECTION'" in correction_function
  assert "if ! wait_for_mici_weston" in correction_function
  assert '[ -f "$MICI_WESTON_COLOR_DROPIN" ] && mici_weston_has_color_correction_disabled' in correction_function
  assert 'Environment="DISABLE_COLOR_CORRECTION=1"' in correction_function
  assert "/run/systemd/system/weston.service.d" in launcher
  assert "restart_mici_weston" in correction_function
  assert "systemctl restart --no-block weston.service" in launcher
  assert "systemctl restart --no-block weston-ready.service" in launcher
  assert "mici_weston_has_color_correction_disabled" in correction_function
  assert "/usr/bin/ss -xlH" in launcher
  assert "/data/misc/display/color_cal" not in launcher
  assert "/persist/comma/color_cal" not in launcher
  assert "/etc/systemd/system" not in launcher


def test_weston_color_change_rolls_back_and_precedes_panel_calibration():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  rollback_start = launcher.index("function restore_mici_weston_color_correction")
  rollback_end = launcher.index("\n}\n", rollback_start)
  rollback_function = launcher[rollback_start:rollback_end]

  assert 'rm -f "$MICI_WESTON_COLOR_DROPIN"' in rollback_function
  assert "systemctl daemon-reload" in rollback_function
  assert "restart_mici_weston" in rollback_function
  assert "wait_for_mici_weston" in rollback_function

  call_start = launcher.index('if [ "$AGNOS_UPDATE_REQUIRED" = "1" ]')
  disable_call = launcher.index("disable_mici_weston_color_correction", call_start)
  calibration_call = launcher.index("apply_mici_screen_calibration", call_start)
  assert disable_call < calibration_call
  assert "if disable_mici_weston_color_correction; then\n      apply_mici_screen_calibration\n    fi" in launcher


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
