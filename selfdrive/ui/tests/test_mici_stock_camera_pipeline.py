import hashlib
import importlib.util
import json
from pathlib import Path

import pytest


ROOT = Path(__file__).parents[3]
DEVICE_CONFIG_PATH = ROOT / "system/hardware/tici/device_config.py"
DEVICE_CONFIG_SPEC = importlib.util.spec_from_file_location("device_config", DEVICE_CONFIG_PATH)
assert DEVICE_CONFIG_SPEC is not None and DEVICE_CONFIG_SPEC.loader is not None
DEVICE_CONFIG = importlib.util.module_from_spec(DEVICE_CONFIG_SPEC)
DEVICE_CONFIG_SPEC.loader.exec_module(DEVICE_CONFIG)
agnos_manifest_path = DEVICE_CONFIG.agnos_manifest_path
is_mici = DEVICE_CONFIG.is_mici
pandad_api_extension = DEVICE_CONFIG.pandad_api_extension
runtime_executable = DEVICE_CONFIG.runtime_executable


def normalized_sha256(relative_path: str, replacements: tuple[tuple[bytes, bytes], ...] = ()) -> str:
  contents = (ROOT / relative_path).read_bytes().replace(b"\r\n", b"\n")
  for old, new in replacements:
    contents = contents.replace(old, new)
  return hashlib.sha256(contents).hexdigest()


def binary_sha256(relative_path: str) -> str:
  return hashlib.sha256((ROOT / relative_path).read_bytes()).hexdigest()


STOCK_MICI_TEXT_FILES = {
  "system/ui/lib/egl_mici.py": "586de0f96d508848d289ed8c7cca556ac289738e7878fec6fac302137081d09c",
  "system/hardware/tici/agnos-mici.json": "c6977d057f66f5b05553a337fc7580f81e9492f44418c9a781460f3c172f3b84",
}

DOM_LEGACY_TEXT_FILES = {
  "system/ui/lib/egl.py": "748335cc64cd7cdd684f25916b56c369129e3bcd7bfac6e65481191dd454e71e",
  "system/hardware/tici/agnos.json": "4b67785d0518a131ce641aac2578b579be85cffd59c36d557b66d5885c86dc9a",
  "system/camerad/cameras/bps_blobs.h": "40fa664885c86782debd0d646c134045507c1444330da3e3eb9fd8176aec7863",
  "system/camerad/sensors/ar0231.cc": "4ec1579df82ccccfb29708b4a14ac48f391dc2e34e75b11b9668ed8b100c9523",
  "system/camerad/sensors/ar0231_cl.h": "eb7eb29ae381418009bf6ed72521214203c80cee234e056d5613cc321ca19c92",
  "system/camerad/sensors/ar0231_registers.h": "c12605d85214225ac9cf078f2909fc9aba19d331cc8d181d8ef5596fd48f015a",
}

DOM_LEGACY_BINARIES = {
  "system/camerad/camerad": "95103c82e713a83c7cd5ec3750d91fabd811b28a2eef7db653ff048e735ffb18",
  "system/loggerd/loggerd": "ca020e1fc7ab68def3c64510c0407ddd0e0e0a7b27a9d84793b6c3b0d88e9e1e",
  "system/loggerd/encoderd": "8121a57db53ad1b61d60e89a82628182640a4e131a68d94163e3c4510b634abf",
  "system/loggerd/bootlog": "4988a450d97fca585a64a89324b4fdb9e7c2c32de6fc9c3ad1509f8a1dc9f43c",
  "selfdrive/pandad/pandad": "f90f891ac2e972987a270984c2a5d9872d93ac2455f56f3b96a324d266725433",
  "selfdrive/pandad/pandad_api_impl.so": "0d41667a30493489b2b00fbf5f59bcf08566007312f20d7a20025c4db545d6f5",
  "selfdrive/modeld/models/commonmodel_pyx.so": "bdac6d07e9287bc68b36afc1610e1d12d0f25874fd19e6b7703a1fe9adb1f5f6",
}

MICI_BINARIES = {
  "selfdrive/modeld/models/mici/commonmodel_pyx.so": "f0a0c18a117d749dd79b70cac72595ee3b3a35cc6e2060e871ddfe0d58f8ee17",
  "system/camerad/camerad_mici": "8ef36928c7e2f8dd5ef536c37a02981bff76ca8760f4c4866704b6ce297201a2",
  "system/loggerd/loggerd_mici": "eeaf74b0cc836149f66aa0f18584f951e7ccb227dbb1a6c48185ecaa921890eb",
  "system/loggerd/encoderd_mici": "671fb4479eb2f24354c448146aa9c1f9737982f48eb005705b37b8ee7cf07b0a",
  "system/loggerd/bootlog_mici": "cc5a6834e652500a76edfe63169dec494c8af95dc2ad685f3f11ef19aebf02ba",
  "selfdrive/pandad/pandad_mici": "bce081529dbecff5a07cf58188dc4269ae6dca3b4c6fe73d95bc08369b1d18ec",
  "selfdrive/pandad/pandad_api_impl_mici.so": "37842a1cc828f89285517836b0f03702af2588dc6faad37870cc77b2560f52c0",
}


def test_mici_camera_renderer_matches_stock_openpilot():
  # The only allowed difference is the import path for the Mici-only EGL module.
  replacements = ((b"openpilot.system.ui.lib.egl_mici", b"openpilot.system.ui.lib.egl"),)
  assert normalized_sha256("selfdrive/ui/mici/onroad/cameraview.py", replacements) == (
    "4ca438be9e2cd2c6ed27fc26424622c75a3b9398f4bd55ff77b52e0823a3d9e4"
  )


@pytest.mark.parametrize(("relative_path", "expected_hash"), STOCK_MICI_TEXT_FILES.items())
def test_mici_text_runtime_matches_stock_openpilot(relative_path: str, expected_hash: str):
  assert normalized_sha256(relative_path) == expected_hash


@pytest.mark.parametrize(("relative_path", "expected_hash"), DOM_LEGACY_TEXT_FILES.items())
def test_legacy_camera_runtime_matches_upstream_dom(relative_path: str, expected_hash: str):
  assert normalized_sha256(relative_path) == expected_hash


@pytest.mark.parametrize(("relative_path", "expected_hash"), DOM_LEGACY_BINARIES.items())
def test_legacy_binaries_match_upstream_dom(relative_path: str, expected_hash: str):
  assert binary_sha256(relative_path) == expected_hash


@pytest.mark.parametrize(("relative_path", "expected_hash"), MICI_BINARIES.items())
def test_mici_binaries_match_verified_stock_agnos_build(relative_path: str, expected_hash: str):
  assert binary_sha256(relative_path) == expected_hash


@pytest.mark.parametrize("device_type", ("tici", "tizi", "pc"))
def test_legacy_devices_keep_dom_runtime(device_type: str):
  assert not is_mici(device_type)
  assert agnos_manifest_path(device_type) == "system/hardware/tici/agnos.json"
  assert runtime_executable("./camerad", device_type) == "./camerad"
  assert runtime_executable("./loggerd", device_type) == "./loggerd"
  assert pandad_api_extension(device_type) == "pandad_api_impl.so"


def test_mici_selects_stock_runtime():
  assert is_mici("mici")
  assert agnos_manifest_path("mici") == "system/hardware/tici/agnos-mici.json"
  assert runtime_executable("./camerad", "mici") == "./camerad_mici"
  assert runtime_executable("./loggerd", "mici") == "./loggerd_mici"
  assert pandad_api_extension("mici") == "pandad_api_impl_mici.so"


def test_device_specific_agnos_manifests():
  dom_manifest = json.loads((ROOT / "system/hardware/tici/agnos.json").read_text())
  mici_manifest = json.loads((ROOT / "system/hardware/tici/agnos-mici.json").read_text())
  dom_system = next(partition for partition in dom_manifest if partition["name"] == "system")
  mici_system = next(partition for partition in mici_manifest if partition["name"] == "system")

  assert "dropbox.com" in dom_system["url"]
  assert mici_system["url"].startswith("https://commadist.azureedge.net/agnosupdate/")
  assert "dropbox.com" not in mici_system["url"]

  launch_env = (ROOT / "launch_env.sh").read_text()
  assert 'if [ "$SP_DEVICE_TYPE" = "mici" ]; then' in launch_env
  assert 'DEFAULT_AGNOS_VERSION="18.4"' in launch_env
  assert 'DEFAULT_AGNOS_MANIFEST="system/hardware/tici/agnos-mici.json"' in launch_env
  assert 'DEFAULT_AGNOS_VERSION="12.8.28"' in launch_env
  assert 'DEFAULT_AGNOS_MANIFEST="system/hardware/tici/agnos.json"' in launch_env


def test_mici_display_migration_cannot_run_on_legacy_devices():
  launcher = (ROOT / "launch_chffrplus.sh").read_text()
  assert 'if [ "$SP_DEVICE_TYPE" = "mici" ] && [ ! -f "$STOCK_CAMERA_MIGRATION_MARKER" ]; then' in launcher
  assert "/persist/comma/dwo_gamma_curves" in launcher
  assert "rm -f /persist/comma/dwo_gamma_curves" not in launcher
  assert 'MANIFEST="${AGNOS_MANIFEST:-system/hardware/tici/agnos.json}"' in launcher
  assert "unset AGNOS_VERSION AGNOS_ACCEPTED_VERSIONS AGNOS_MANIFEST SP_DEVICE_TYPE" in launcher


def test_runtime_call_sites_use_device_selection():
  model_package = (ROOT / "selfdrive/modeld/models/__init__.py").read_text()
  process_config = (ROOT / "system/manager/process_config.py").read_text()
  helpers = (ROOT / "system/manager/helpers.py").read_text()
  pandad = (ROOT / "selfdrive/pandad/pandad.py").read_text()
  pandad_package = (ROOT / "selfdrive/pandad/__init__.py").read_text()
  updater = (ROOT / "system/updated/updated.py").read_text()
  galaxy = (ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text()

  assert 'if is_mici(HARDWARE.get_device_type()):' in model_package
  assert '__path__.insert(0, str(Path(__file__).with_name("mici")))' in model_package
  assert 'runtime_executable("./camerad", DEVICE_TYPE)' in process_config
  assert 'runtime_executable("./loggerd", DEVICE_TYPE)' in process_config
  assert 'runtime_executable("./encoderd", DEVICE_TYPE)' in process_config
  assert 'runtime_executable("./bootlog", HARDWARE.get_device_type())' in helpers
  assert 'runtime_executable("./pandad", HARDWARE.get_device_type())' in pandad
  assert "pandad_api_extension(HARDWARE.get_device_type())" in pandad_package
  assert "agnos_manifest_path(HARDWARE.get_device_type())" in updater
  assert "agnos_manifest_path(HARDWARE.get_device_type())" in galaxy


def test_mici_uses_stock_direct_framebuffer_presentation():
  application = (ROOT / "system/ui/lib/application.py").read_text()

  assert 'MICI_FORCE_RENDER_TEXTURE = os.getenv("MICI_FORCE_RENDER_TEXTURE", "0") == "1"' in application
  assert '"0" if PC or DEVICE_TYPE == "mici" else "1"' in application
  assert 'vblank_control = DEVICE_TYPE == "mici"' in application
  assert 'rl.set_target_fps(0 if OFFSCREEN or vblank_control else fps)' in application


def test_mici_runtime_has_no_custom_agnos_only_dependencies():
  assert (ROOT / "prebuilt").exists()
  forbidden_dependencies = (
    b"libavformat.so.58",
    b"libavcodec.so.58",
    b"libavutil.so.56",
    b"libcapnp-1.0.2.so",
    b"libkj-1.0.2.so",
    b"libOmxCore.so",
  )

  for relative_path in MICI_BINARIES:
    contents = (ROOT / relative_path).read_bytes()
    assert contents.startswith(b"\x7fELF")
    assert not any(dependency in contents for dependency in forbidden_dependencies)
