#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

source "$DIR/launch_env.sh"

export SP_BOOT_TIMING_LOG="${SP_BOOT_TIMING_LOG:-/tmp/starpilot_boot_timing.log}"
: > "$SP_BOOT_TIMING_LOG" 2>/dev/null || true
SP_LAUNCH_LAST_SECONDS=$SECONDS

function sp_boot_timing_line {
  echo "$1"
  printf '%s\n' "$1" >> "$SP_BOOT_TIMING_LOG" 2>/dev/null || true
}

function sp_launch_timing {
  local now=$SECONDS
  local delta=$((now - SP_LAUNCH_LAST_SECONDS))
  sp_boot_timing_line "SP_BOOT_TIMING launch $1 +${delta}s total=${now}s"
  SP_LAUNCH_LAST_SECONDS=$now
}

MICI_WESTON_COLOR_DROPIN_DIR="/run/systemd/system/weston.service.d"
MICI_WESTON_COLOR_DROPIN="$MICI_WESTON_COLOR_DROPIN_DIR/starpilot-mici-color.conf"
MICI_SCREEN_CALIBRATION_MARKER="/run/starpilot-mici-screen-calibration.done"

function mici_weston_has_color_correction_disabled {
  local main_pid
  main_pid="$(sudo /usr/bin/systemctl show --property=MainPID --value weston.service 2>/dev/null || true)"
  [[ "$main_pid" =~ ^[1-9][0-9]*$ ]] || return 1

  sudo /bin/cat "/proc/$main_pid/environ" 2>/dev/null \
    | /usr/bin/tr '\000' '\n' \
    | /usr/bin/grep -qx 'DISABLE_COLOR_CORRECTION=1'
}

function wait_for_mici_weston {
  local tick
  for ((tick = 0; tick < 200; tick++)); do
    if sudo /usr/bin/systemctl is-active --quiet weston.service \
        && sudo /usr/bin/systemctl is-active --quiet weston-ready.service \
        && [ -e /var/tmp/weston/wayland-0 ] \
        && /usr/bin/ss -xlH | /usr/bin/grep -Fq /var/tmp/weston/wayland-0; then
      return 0
    fi
    /bin/sleep 0.1
  done
  return 1
}

function restart_mici_weston {
  sudo /usr/bin/systemctl restart --no-block weston.service || return 1
  # weston-ready is PartOf=weston.service in Dom's AGNOS image. Queue it
  # explicitly as a fallback, but let the readiness loop enforce our timeout.
  sudo /usr/bin/systemctl restart --no-block weston-ready.service >/dev/null 2>&1 || true
}

function restore_mici_weston_color_correction {
  sudo /bin/rm -f "$MICI_WESTON_COLOR_DROPIN"
  sudo /usr/bin/systemctl daemon-reload >/dev/null 2>&1 || true

  if restart_mici_weston \
      && wait_for_mici_weston; then
    sp_boot_timing_line "Mici Weston restored after color-pipeline rollback"
  else
    echo "Mici Weston color-pipeline rollback could not confirm display readiness"
  fi
}

function disable_mici_weston_color_correction {
  [ "${SP_DEVICE_TYPE:-}" = "mici" ] || return 0

  local weston_load_state
  weston_load_state="$(sudo /usr/bin/systemctl show --property=LoadState --value weston.service 2>/dev/null || true)"
  [ "$weston_load_state" = "loaded" ] || return 1

  local legacy_renderer="/usr/lib/arm-linux-gnueabihf/weston/gl-renderer.so"
  [ -f "$legacy_renderer" ] || return 1
  /usr/bin/grep -aq 'DISABLE_COLOR_CORRECTION' "$legacy_renderer" || return 1

  # comma.service and Weston start in parallel on Dom's AGNOS image. Wait for
  # the real Wayland listener so an early manager launch cannot skip the fix.
  if ! wait_for_mici_weston; then
    echo "Mici Weston was not ready for the stock color pipeline; continuing with the existing display state"
    return 1
  fi
  if [ -f "$MICI_WESTON_COLOR_DROPIN" ] && mici_weston_has_color_correction_disabled; then
    return 0
  fi

  if ! sudo /bin/mkdir -p "$MICI_WESTON_COLOR_DROPIN_DIR"; then
    echo "Mici Weston color correction could not be disabled; continuing with the existing display state"
    return 1
  fi
  if ! printf '%s\n' '[Service]' 'Environment="DISABLE_COLOR_CORRECTION=1"' \
      | sudo /usr/bin/tee "$MICI_WESTON_COLOR_DROPIN" >/dev/null; then
    echo "Mici Weston color correction could not be disabled; continuing with the existing display state"
    sudo /bin/rm -f "$MICI_WESTON_COLOR_DROPIN"
    return 1
  fi
  if ! sudo /usr/bin/systemctl daemon-reload; then
    echo "Mici Weston color correction could not be disabled; continuing with the existing display state"
    sudo /bin/rm -f "$MICI_WESTON_COLOR_DROPIN"
    sudo /usr/bin/systemctl daemon-reload >/dev/null 2>&1 || true
    return 1
  fi

  if restart_mici_weston \
      && wait_for_mici_weston \
      && mici_weston_has_color_correction_disabled; then
    sp_boot_timing_line "Mici Weston legacy color correction disabled"
    return 0
  fi

  echo "Mici Weston did not restart with stock color behavior; rolling back"
  restore_mici_weston_color_correction
  return 1
}

function apply_mici_screen_calibration {
  [ "${SP_DEVICE_TYPE:-}" = "mici" ] || return 0

  local calibration_script="/usr/comma/screen_calibration.py"
  local gamma_curves="/persist/comma/dwo_gamma_curves"
  local calibration_interface="/sys/kernel/debug/dsi_dwo_video_display/mipi_command"

  [ -e "$MICI_SCREEN_CALIBRATION_MARKER" ] && return 0
  if [ ! -f "$calibration_script" ]; then
    echo "Mici screen calibration skipped: custom AGNOS calibration utility not found"
    return 0
  fi
  [ -f "$gamma_curves" ] || return 0

  if ! sudo /usr/bin/test -e "$calibration_interface"; then
    echo "Mici screen calibration skipped: panel command interface not found"
    return 0
  fi

  # Stock Mici applies the persisted, per-panel gamma before its renderer. Dom's
  # image ships the same panel-calibration mechanism but does not start it.
  # Run it synchronously so manager cannot draw a frame before calibration ends.
  if sudo /usr/bin/timeout --signal=TERM --kill-after=1s 10s "$calibration_script"; then
    sudo /usr/bin/touch "$MICI_SCREEN_CALIBRATION_MARKER" || true
    sp_boot_timing_line "Mici screen calibration applied"
  else
    echo "Mici screen calibration failed or timed out; continuing with the existing display state"
  fi
}

function agnos_init {
  sp_launch_timing "agnos_init_start"

  # TODO: move this to agnos
  sudo rm -f /data/etc/NetworkManager/system-connections/*.nmmeta

  # set success flag for current boot slot
  sudo abctl --set_success

  # Restore SSH access after a user-triggered reset if keys were backed up to /cache.
  SSH_BACKUP_DIR="/cache/reset_backup"
  if [ -d "$SSH_BACKUP_DIR" ]; then
    sudo mkdir -p /data/params/d
    for key in GithubSshKeys SshEnabled; do
      if [ -f "$SSH_BACKUP_DIR/$key" ]; then
        sudo cp "$SSH_BACKUP_DIR/$key" "/data/params/d/$key"
      fi
    done
    sudo chown comma:comma /data/params/d/GithubSshKeys /data/params/d/SshEnabled 2>/dev/null || true
    sudo chmod 600 /data/params/d/GithubSshKeys /data/params/d/SshEnabled 2>/dev/null || true
    sudo rm -rf "$SSH_BACKUP_DIR"
  fi

  # TODO: do this without udev in AGNOS
  # udev does this, but sometimes we startup faster
  sudo chgrp gpu /dev/adsprpc-smd /dev/ion /dev/kgsl-3d0
  sudo chmod 660 /dev/adsprpc-smd /dev/ion /dev/kgsl-3d0

  # StarPilot variables
  sudo chmod 0777 /cache

  # Check if AGNOS update is required
  AGNOS_CURRENT_VERSION="$(< /VERSION)"
  AGNOS_UPDATE_REQUIRED=1
  for accepted_version in $AGNOS_ACCEPTED_VERSIONS; do
    if [ "$AGNOS_CURRENT_VERSION" = "$accepted_version" ]; then
      AGNOS_UPDATE_REQUIRED=0
      break
    fi
  done

  if [ "$AGNOS_UPDATE_REQUIRED" = "1" ]; then
    AGNOS_PY="$DIR/system/hardware/tici/agnos.py"
    MANIFEST="$DIR/system/hardware/tici/agnos.json"
    if $AGNOS_PY --verify $MANIFEST; then
      sudo reboot
    fi
    $DIR/system/hardware/tici/updater $AGNOS_PY $MANIFEST
  else
    # Dom uses a legacy Weston color stage that stock Mici does not. Disable it
    # before applying the same panel calibration used by stock comma 4 AGNOS.
    if disable_mici_weston_color_correction; then
      apply_mici_screen_calibration
    fi
  fi

  sp_launch_timing "agnos_init_done"
}

function launch {
  sp_launch_timing "launch_start"

  # Remove orphaned git lock if it exists on boot
  [ -f "$DIR/.git/index.lock" ] && rm -f $DIR/.git/index.lock

  # Check to see if there's a valid overlay-based update available. Conditions
  # are as follows:
  #
  # 1. The DIR init file has to exist, with a newer modtime than anything in
  #    the DIR Git repo. This checks for local development work or the user
  #    switching branches/forks, which should not be overwritten.
  # 2. The FINALIZED consistent file has to exist, indicating there's an update
  #    that completed successfully and synced to disk.

  if [ -f "${DIR}/.overlay_init" ]; then
    find ${DIR}/.git -newer ${DIR}/.overlay_init | grep -q '.' 2> /dev/null
    if [ $? -eq 0 ]; then
      echo "${DIR} has been modified, skipping overlay update installation"
    else
      if [ -f "${STAGING_ROOT}/finalized/.overlay_consistent" ]; then
        if [ ! -d /data/safe_staging/old_openpilot ]; then
          echo "Valid overlay update found, installing"
          LAUNCHER_LOCATION="${BASH_SOURCE[0]}"

          mv $DIR /data/safe_staging/old_openpilot
          mv "${STAGING_ROOT}/finalized" $DIR
          cd $DIR

          echo "Restarting launch script ${LAUNCHER_LOCATION}"
          unset AGNOS_VERSION
          exec "${LAUNCHER_LOCATION}"
        else
          echo "openpilot backup found, not updating"
          # TODO: restore backup? This means the updater didn't start after swapping
        fi
      fi
    fi
  fi
  sp_launch_timing "overlay_check_done"

  # handle pythonpath
  ln -sfn $(pwd) /data/pythonpath
  export BASEDIR="$DIR"
  export PYTHONPATH="$DIR/starpilot/third_party:$PWD"
  sp_launch_timing "pythonpath_done"

  # hardware specific init
  if [ -f /AGNOS ]; then
    agnos_init
  fi
  sp_launch_timing "hardware_init_done"

  # write tmux scrollback to a file
  tmux capture-pane -pq -S-1000 > /tmp/launch_log
  sp_launch_timing "capture_launch_log_done"

  # start manager
  cd system/manager

  sp_launch_timing "launch_param_migrations_start"
  if ! python3 ./launch_param_migrations.py; then
    echo "Launch param migrations failed; continuing boot."
  fi
  sp_launch_timing "launch_param_migrations_done"

  # Bootstrap runtime (e.g. /usr/comma after reset/uninstall) must go straight
  # to manager/setup flow. Do not run StarPilot prebuilt checks/builds here.
  if [ "$DIR" = "/usr/comma" ] || [ ! -d "$DIR/.git" ]; then
    sp_launch_timing "bootstrap_manager_start"
    ./manager.py
    while true; do sleep 1; done
  fi

  function prebuilt_runtime_compatible {
    python3 - <<'PY'
import importlib
import os
from pathlib import Path
import sys
import time

start = time.monotonic()
last = start
log_path = os.environ.get("SP_BOOT_TIMING_LOG")

def emit(line):
  print(line, flush=True)
  if log_path:
    try:
      with open(log_path, "a") as f:
        f.write(line + "\n")
    except OSError:
      pass

def log_step(label):
  global last
  now = time.monotonic()
  emit(f"SP_BOOT_TIMING prebuilt_compat {label} +{now - last:.3f}s total={now - start:.3f}s")
  last = now

mods = [
  "openpilot.common.params_pyx",
  "msgq.ipc_pyx",
  "msgq.visionipc.visionipc_pyx",
  "openpilot.common.transformations.transformations",
  "openpilot.selfdrive.pandad.pandad_api_impl",
  "openpilot.selfdrive.controls.lib.lateral_mpc_lib.c_generated_code.acados_ocp_solver_pyx",
  "openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.c_generated_code.acados_ocp_solver_pyx",
]

for mod in mods:
  try:
    importlib.import_module(mod)
  except Exception as e:
    print(f"Prebuilt compatibility failure in {mod}: {e}", file=sys.stderr)
    raise
  log_step(f"import:{mod}")

repo_root = Path.cwd().parents[1]
required_files = [
  repo_root / "selfdrive/modeld/models/driving_tinygrad.pkl",
  repo_root / "selfdrive/modeld/models/dmonitoring_model_metadata.pkl",
  repo_root / "selfdrive/modeld/models/dmonitoring_model_tinygrad.pkl",
  repo_root / "selfdrive/modeld/models/dm_warp_1928x1208_tinygrad.pkl",
  repo_root / "selfdrive/modeld/models/dm_warp_1344x760_tinygrad.pkl",
  repo_root / "selfdrive/pandad/pandad_api_impl.so",
  repo_root / "selfdrive/controls/lib/lateral_mpc_lib/c_generated_code/acados_ocp_solver_pyx.so",
  repo_root / "selfdrive/controls/lib/lateral_mpc_lib/c_generated_code/libacados_ocp_solver_lat.so",
  repo_root / "selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/acados_ocp_solver_pyx.so",
  repo_root / "selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/libacados_ocp_solver_long.so",
  repo_root / "opendbc_repo/opendbc/dbc/gm_global_a_powertrain_generated.dbc",
]

for path in required_files:
  if not path.is_file():
    raise FileNotFoundError(f"Missing prebuilt runtime artifact: {path}")
log_step("required_files")
PY
  }

  USE_PREBUILT=1
  if [ -f /data/params/d/UsePrebuilt ]; then
    USE_PREBUILT=$(tr -d '\n' < /data/params/d/UsePrebuilt)
  fi

  sp_launch_timing "prebuilt_decision_done"
  if [ "$USE_PREBUILT" = "1" ] && [ -f $DIR/prebuilt ] && ! prebuilt_runtime_compatible; then
    echo "Prebuilt runtime artifacts are incompatible on this device; rebuilding locally."
    USE_PREBUILT=0
  fi
  sp_launch_timing "prebuilt_compat_done"

  if [ "$USE_PREBUILT" != "1" ] || [ ! -f $DIR/prebuilt ]; then
    sp_launch_timing "build_start"
    ./build.py
    sp_launch_timing "build_done"
  fi
  sp_launch_timing "manager_start"
  ./manager.py

  # if broken, keep on screen error
  while true; do sleep 1; done
}

launch
