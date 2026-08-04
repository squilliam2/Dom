import importlib.util
import sys
from pathlib import Path

from openpilot.system.hardware import HARDWARE
from openpilot.system.hardware.tici.device_config import pandad_api_extension


def _load_pandad_api_impl():
  module_name = f"{__name__}.pandad_api_impl"
  extension_path = Path(__file__).with_name(pandad_api_extension(HARDWARE.get_device_type()))
  spec = importlib.util.spec_from_file_location(module_name, extension_path)
  if spec is None or spec.loader is None:
    raise ImportError(f"Unable to load {extension_path}")

  module = importlib.util.module_from_spec(spec)
  sys.modules[module_name] = module
  spec.loader.exec_module(module)
  return module


_pandad_api_impl = _load_pandad_api_impl()
can_list_to_can_capnp = _pandad_api_impl.can_list_to_can_capnp
can_capnp_to_list = _pandad_api_impl.can_capnp_to_list
