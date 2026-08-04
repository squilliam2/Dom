MICI_DEVICE_TYPE = "mici"
DOM_AGNOS_MANIFEST = "system/hardware/tici/agnos.json"
MICI_AGNOS_MANIFEST = "system/hardware/tici/agnos-mici.json"


def is_mici(device_type: str) -> bool:
  return device_type == MICI_DEVICE_TYPE


def agnos_manifest_path(device_type: str) -> str:
  return MICI_AGNOS_MANIFEST if is_mici(device_type) else DOM_AGNOS_MANIFEST


def runtime_executable(executable: str, device_type: str) -> str:
  return f"{executable}_mici" if is_mici(device_type) else executable


def pandad_api_extension(device_type: str) -> str:
  return "pandad_api_impl_mici.so" if is_mici(device_type) else "pandad_api_impl.so"
