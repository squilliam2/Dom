#!/usr/bin/env bash

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1

# On AGNOS, prefer the managed venv runtime (has required Python deps like pyzmq).
if [ -x /usr/local/venv/bin/python3 ]; then
  export PATH="/usr/local/venv/bin:${PATH}"
fi

# models get lower priority than ui
# - ui is ~5ms
# - modeld is 20ms
# - DM is 10ms
# in order to run ui at 60fps (16.67ms), we need to allow
# it to preempt the model workloads. we have enough
# headroom for this until ui is moved to the CPU.
export QCOM_PRIORITY=12

if [ -z "$AGNOS_VERSION" ]; then
  export AGNOS_VERSION="12.8.28"
fi

if [ -z "$AGNOS_ACCEPTED_VERSIONS" ]; then
  export AGNOS_ACCEPTED_VERSIONS="$AGNOS_VERSION"
fi

export STAGING_ROOT="/data/safe_staging"

# StarPilot variables (only available after StarPilot is installed to /data/openpilot)
if [ -x /data/openpilot/starpilot/system/environment_variables ]; then
  eval "$(/data/openpilot/starpilot/system/environment_variables)"
fi

# Hardware identity must not be overridable by persisted or inherited settings.
SP_DEVICE_TYPE=""
if [ -r /sys/firmware/devicetree/base/model ]; then
  SP_DEVICE_TYPE="$(tr -d '\000' < /sys/firmware/devicetree/base/model)"
  SP_DEVICE_TYPE="${SP_DEVICE_TYPE##*comma }"
fi
export SP_DEVICE_TYPE

# Keep AGNOS_VERSION stable for older updaters. New launch/update code uses
# these physically selected targets so only comma four receives the Mici image.
if [ "$SP_DEVICE_TYPE" = "mici" ]; then
  export SP_AGNOS_TARGET_VERSION="12.8.28-sq-mici.2"
  export SP_AGNOS_ACCEPTED_VERSIONS="$SP_AGNOS_TARGET_VERSION"
  export SP_AGNOS_MANIFEST="system/hardware/tici/agnos-mici.json"
else
  export SP_AGNOS_TARGET_VERSION="$AGNOS_VERSION"
  export SP_AGNOS_ACCEPTED_VERSIONS="$AGNOS_ACCEPTED_VERSIONS"
  export SP_AGNOS_MANIFEST="system/hardware/tici/agnos.json"
fi
