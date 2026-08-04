from pathlib import Path

from openpilot.system.hardware import HARDWARE
from openpilot.system.hardware.tici.device_config import is_mici


# Keep extension loading lazy while giving Mici its stock-AGNOS build. Python
# searches package paths in order when commonmodel_pyx is imported.
if is_mici(HARDWARE.get_device_type()):
  __path__.insert(0, str(Path(__file__).with_name("mici")))
