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

if [ -z "$SP_DEVICE_TYPE" ] && [ -r /sys/firmware/devicetree/base/model ]; then
  SP_DEVICE_TYPE="$(tr -d '\000' < /sys/firmware/devicetree/base/model)"
  SP_DEVICE_TYPE="${SP_DEVICE_TYPE#comma }"
fi
export SP_DEVICE_TYPE

# The comma 4 camera stack is paired with stock Mici AGNOS. Keep Dom's custom
# AGNOS on comma 3/3X, where its legacy camera and runtime libraries are needed.
if [ "$SP_DEVICE_TYPE" = "mici" ]; then
  DEFAULT_AGNOS_VERSION="18.4"
  DEFAULT_AGNOS_MANIFEST="system/hardware/tici/agnos-mici.json"
else
  DEFAULT_AGNOS_VERSION="12.8.28"
  DEFAULT_AGNOS_MANIFEST="system/hardware/tici/agnos.json"
fi

if [ -z "$AGNOS_VERSION" ]; then
  export AGNOS_VERSION="$DEFAULT_AGNOS_VERSION"
fi

if [ -z "$AGNOS_MANIFEST" ]; then
  export AGNOS_MANIFEST="$DEFAULT_AGNOS_MANIFEST"
fi

if [ -z "$AGNOS_ACCEPTED_VERSIONS" ]; then
  export AGNOS_ACCEPTED_VERSIONS="$AGNOS_VERSION"
fi

export STAGING_ROOT="/data/safe_staging"

# StarPilot variables (only available after StarPilot is installed to /data/openpilot)
if [ -x /data/openpilot/starpilot/system/environment_variables ]; then
  eval "$(/data/openpilot/starpilot/system/environment_variables)"
fi
