import hashlib
import json
from pathlib import Path

import pytest


ROOT = Path(__file__).parents[3]

STOCK_MICI_FILES = {
  "selfdrive/ui/mici/onroad/cameraview.py": "4ca438be9e2cd2c6ed27fc26424622c75a3b9398f4bd55ff77b52e0823a3d9e4",
  "system/ui/lib/egl.py": "586de0f96d508848d289ed8c7cca556ac289738e7878fec6fac302137081d09c",
  "system/camerad/camerad": "9d4b36abd39b09594dec0e97f07caf045ae8a87fa3c52d4070a3cb38a6d040c8",
  "system/camerad/cameras/spectra.cc": "a59d0ab1450221003a617ebe4be7efa4dfdf108330ab666c026195f47a3cae04",
  "system/camerad/cameras/bps_blobs.h": "d8a2d426c7578d59b30b527b47192583db55aa5a6bef36c0b51ffc979dd53364",
  "system/camerad/cameras/camera_qcom2.cc": "573c45e4799bf816e31aa60945cf5175d38dd0fb34f532f1697c8dcec0eacb29",
  "system/hardware/tici/agnos.json": "c6977d057f66f5b05553a337fc7580f81e9492f44418c9a781460f3c172f3b84",
}


@pytest.mark.parametrize(("relative_path", "expected_hash"), STOCK_MICI_FILES.items())
def test_mici_camera_runtime_matches_stock_openpilot(relative_path: str, expected_hash: str):
  contents = (ROOT / relative_path).read_bytes()
  if relative_path != "system/camerad/camerad":
    contents = contents.replace(b"\r\n", b"\n")
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
