#!/usr/bin/env python3
import dataclasses
import json
import os
import threading
import time

from pathlib import Path
from types import SimpleNamespace

from openpilot.common.basedir import BASEDIR
from openpilot.common.params import Params
from openpilot.common.time_helpers import system_time_valid
from openpilot.system.hardware import HARDWARE

STARPILOT_API = os.getenv("STARPILOT_API", "https://frogpilot.com/api")
BOOT_LOGO_STATE_PATH = Path("/cache/starpilot_boot_logo_state_v1")
ACTIVE_THEME_PATH = Path(BASEDIR) / "starpilot/assets/active_theme"
STOCK_THEME_PATH = Path(BASEDIR) / "starpilot/assets/stock_theme"
ACTIVE_THEME_REQUIRED_PATHS = (
  ACTIVE_THEME_PATH / "colors/colors.json",
  ACTIVE_THEME_PATH / "icons",
  ACTIVE_THEME_PATH / "distance_icons",
  ACTIVE_THEME_PATH / "sounds",
  ACTIVE_THEME_PATH / "steering_wheel",
)
ACTIVE_THEME_BOOTSTRAP_LINKS = (
  ("colors", STOCK_THEME_PATH / "colors"),
  ("icons", STOCK_THEME_PATH / "icons"),
  ("distance_icons", STOCK_THEME_PATH / "distance_icons"),
  ("sounds", STOCK_THEME_PATH / "sounds"),
  ("steering_wheel", STOCK_THEME_PATH / "steering_wheel"),
)


def _starpilot_data_root():
  if HARDWARE.get_device_type() == "pc":
    from openpilot.system.hardware.hw import Paths

    return Path(Paths.comma_home()) / "starpilot" / "data"
  return Path("/data")


def _starpilot_persist_root():
  if HARDWARE.get_device_type() == "pc":
    from openpilot.system.hardware.hw import Paths

    return Path(Paths.persist_root())
  return Path("/persist")


def _theme_save_path():
  return _starpilot_data_root() / "themes"


def _maps_path():
  return _starpilot_data_root() / "media/0/osm/offline"


def _run_cmd(*args, **kwargs):
  from openpilot.starpilot.common.starpilot_utilities import run_cmd

  return run_cmd(*args, **kwargs)


def _path_has_content(path):
  if path.is_symlink() and not path.exists():
    return False
  if path.is_file():
    return True
  if not path.is_dir():
    return False
  try:
    next(path.iterdir())
    return True
  except (OSError, StopIteration):
    return False


def _active_theme_ready():
  return all(_path_has_content(path) for path in ACTIVE_THEME_REQUIRED_PATHS)


def _replace_with_symlink(path, target):
  if path.is_symlink() or path.is_file():
    try:
      path.unlink()
    except OSError:
      return
  elif path.exists():
    import shutil

    try:
      shutil.rmtree(path)
    except OSError:
      return

  path.parent.mkdir(parents=True, exist_ok=True)
  try:
    path.symlink_to(target, target_is_directory=target.is_dir())
  except OSError:
    pass


def _ensure_minimal_active_theme():
  for name, target in ACTIVE_THEME_BOOTSTRAP_LINKS:
    if target.exists() and not _path_has_content(ACTIVE_THEME_PATH / name):
      _replace_with_symlink(ACTIVE_THEME_PATH / name, target)

  signals_path = ACTIVE_THEME_PATH / "signals"
  if signals_path.is_symlink() and not signals_path.exists():
    try:
      signals_path.unlink()
    except OSError:
      pass


def _normalize_dongle_id(value):
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="ignore")
  if value is None:
    return None
  value = str(value).strip()
  return value or None


def _read_persisted_stock_dongle_id():
  persisted_dongle_id_path = _starpilot_persist_root() / "comma" / "dongle_id"
  if not persisted_dongle_id_path.is_file():
    return None
  return _normalize_dongle_id(persisted_dongle_id_path.read_text())


def _ensure_stock_dongle_id_fast(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  konik_dongle_id = _normalize_dongle_id(params.get("KonikDongleId"))
  stock_dongle_id = _normalize_dongle_id(params.get("StockDongleId"))

  if stock_dongle_id not in (None, konik_dongle_id):
    return stock_dongle_id

  candidate = _read_persisted_stock_dongle_id()
  if candidate in (None, konik_dongle_id):
    candidate = current_dongle_id if current_dongle_id != konik_dongle_id else None

  if candidate is not None and candidate != stock_dongle_id:
    params.put("StockDongleId", candidate)

  return candidate


def _sync_cached_konik_dongle_id(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  konik_dongle_id = _normalize_dongle_id(params.get("KonikDongleId"))
  stock_dongle_id = _ensure_stock_dongle_id_fast(params)

  if params.get_bool("UseKonikServer"):
    if konik_dongle_id is not None and current_dongle_id != konik_dongle_id:
      params.put("DongleId", konik_dongle_id)
  elif current_dongle_id == konik_dongle_id and stock_dongle_id is not None:
    params.put("DongleId", stock_dongle_id)


def _boot_logo_cache_key(selected_logo, source_logo):
  try:
    source_stat = source_logo.stat()
    source_path = source_logo.resolve()
  except OSError:
    return None

  selected = selected_logo.decode("utf-8", "ignore") if isinstance(selected_logo, (bytes, bytearray)) else str(selected_logo or "")
  return "\n".join([
    selected.strip().lower(),
    str(source_path),
    str(source_stat.st_mtime_ns),
    str(source_stat.st_size),
    "",
  ])


def _boot_logo_cache_matches(cache_key):
  if cache_key is None:
    return False
  try:
    return BOOT_LOGO_STATE_PATH.read_text() == cache_key
  except OSError:
    return False


def _write_boot_logo_cache(cache_key):
  if cache_key is None:
    return
  try:
    BOOT_LOGO_STATE_PATH.parent.mkdir(parents=True, exist_ok=True)
    BOOT_LOGO_STATE_PATH.write_text(cache_key)
  except OSError:
    pass


def seed_desktop_theme_assets():
  from openpilot.starpilot.assets.theme_manager import ThemeManager

  params = Params()
  params_memory = Params(memory=True)
  params_defaults = Params(return_defaults=True)
  theme_manager = ThemeManager(params, params_memory, boot_run=True)

  custom_themes = params_defaults.get_bool("CustomThemes")
  random_themes = custom_themes and params_defaults.get_bool("RandomThemes")

  starpilot_toggles = SimpleNamespace(
    boot_logo=params_defaults.get("BootLogo", encoding="utf-8", default="starpilot"),
    holiday_themes=params_defaults.get_bool("HolidayThemes"),
    random_themes=random_themes,
    random_themes_holidays=random_themes and params_defaults.get_bool("RandomThemesHolidays"),
    color_scheme=params_defaults.get("ColorScheme", encoding="utf-8", default="stock") if custom_themes else "stock",
    distance_icons=params_defaults.get("DistanceIconPack", encoding="utf-8", default="stock") if custom_themes else "stock",
    icon_pack=params_defaults.get("IconPack", encoding="utf-8", default="stock") if custom_themes else "stock",
    sound_pack=params_defaults.get("SoundPack", encoding="utf-8", default="stock") if custom_themes else "stock",
    signal_icons=params_defaults.get("SignalAnimation", encoding="utf-8", default="stock") if custom_themes else "stock",
    wheel_image=params_defaults.get("WheelIcon", encoding="utf-8", default="stock") if custom_themes else "stock",
  )

  theme_manager.update_active_theme(
    time_validated=system_time_valid(),
    starpilot_toggles=starpilot_toggles,
    boot_run=True,
  )
  theme_manager.update_theme_asset("distance_icons", starpilot_toggles.distance_icons, boot_run=True)
  theme_manager.update_wheel_image(starpilot_toggles.wheel_image, boot_run=True)


def starpilot_boot_functions(build_metadata, params):
  params.put("BuildMetadata", json.dumps(dataclasses.asdict(build_metadata)))
  _sync_cached_konik_dongle_id(params)

  def boot_thread():
    try:
      _finish_starpilot_boot(build_metadata)
    except Exception as error:
      print(f"StarPilot boot functions failed: {error}")

  if _active_theme_ready():
    threading.Thread(target=boot_thread, daemon=True).start()
    return

  # Brand-new or partially migrated installs need basic active theme links
  # before UI starts. Use stock links here and let the full theme refresh run
  # off the manager hot path.
  _ensure_minimal_active_theme()
  threading.Thread(target=boot_thread, daemon=True).start()


def _refresh_active_theme(params):
  from openpilot.starpilot.assets.theme_manager import ThemeManager
  from openpilot.starpilot.common.starpilot_variables import StarPilotVariables

  params_memory = Params(memory=True)
  starpilot_toggles = StarPilotVariables().starpilot_toggles
  ThemeManager(params, params_memory, boot_run=True).update_active_theme(time_validated=system_time_valid(), starpilot_toggles=starpilot_toggles, boot_run=True)


def _finish_starpilot_boot(build_metadata):
  from openpilot.starpilot.common.connect_server import sync_konik_dongle_id
  from openpilot.starpilot.common.maps_catalog import sanitize_selected_locations_csv
  from openpilot.starpilot.common.starpilot_backups import backup_starpilot

  params = Params()

  maps_selected_raw = params.get("MapsSelected")
  maps_selected = sanitize_selected_locations_csv(maps_selected_raw)
  if isinstance(maps_selected_raw, bytes):
    maps_selected_raw = maps_selected_raw.decode("utf-8", errors="ignore")
  if maps_selected != (maps_selected_raw or ""):
    params.put("MapsSelected", maps_selected)

  params.put("BuildMetadata", json.dumps(dataclasses.asdict(build_metadata)))

  _refresh_active_theme(params)
  sync_konik_dongle_id(params)

  while not system_time_valid():
    print("Waiting for system time to become valid...")
    time.sleep(1)

  backup_starpilot(build_metadata, params)


def install_starpilot(build_metadata, params):
  data_root = _starpilot_data_root()
  paths = [
    data_root / "error_logs",
    data_root / "media/0/realdata_HD",
    data_root / "media/0/realdata_konik",
    data_root / "media/0/osm/offline",
    _theme_save_path()
  ]
  for path in paths:
    path.mkdir(parents=True, exist_ok=True)

  register_device(build_metadata, params)

  update_boot_logo(starpilot=True, selected_logo=params.get("BootLogo"))

  frogs_go_moo_path = _starpilot_persist_root() / "frogsgomoo.py"
  if frogs_go_moo_path.is_file():
    mount_options = _run_cmd(["findmnt", "-n", "-o", "OPTIONS", "/persist"], "Successfully retrieved mount options", "Failed to retrieve mount options")
    _run_cmd(["sudo", "mount", "-o", "remount,rw", "/persist"], "Successfully remounted /persist as read-write", "Failed to remount /persist")
    _run_cmd(["sudo", "python3", frogs_go_moo_path], "Successfully ran frogsgomoo.py", "Failed to run frogsgomoo.py")
    _run_cmd(["sudo", "mount", "-o", f"remount,{mount_options}", "/persist"], "Successfully restored /persist mount options", "Failed to restore /persist mount options")


def register_device(build_metadata, params):
  def register_thread():
    import requests

    def is_url_pingable(url):
      if not url:
        return False
      try:
        response = requests.head(url, timeout=10, allow_redirects=True, headers={"User-Agent": "starpilot-ping-test/1.0 (https://github.com/FrogAi/StarPilot)"})
        return response.ok
      except Exception:
        return False

    dongle_id = params.get("DongleId")
    if isinstance(dongle_id, bytes):
      dongle_id = dongle_id.decode("utf-8", errors="ignore")
    starpilot_dongle_id = params.get("StarPilotDongleId")
    if isinstance(starpilot_dongle_id, bytes):
      starpilot_dongle_id = starpilot_dongle_id.decode("utf-8", errors="ignore")

    # Keep a stable local identifier even if the remote registration endpoint
    # is unavailable or slow to respond.
    if dongle_id and not starpilot_dongle_id:
      params.put("StarPilotDongleId", dongle_id)

    while not is_url_pingable(STARPILOT_API):
      time.sleep(60)

    payload = {
      "api_token": params.get("StarPilotApiToken"),
      "build_metadata": dataclasses.asdict(build_metadata),
      "device": HARDWARE.get_device_type(),
      "dongle_id": dongle_id,
      "starpilot_dongle_id": params.get("StarPilotDongleId"),
    }

    try:
      response = requests.post(f"{STARPILOT_API}/register", json=payload, headers={"Content-Type": "application/json", "User-Agent": "starpilot-api/1.0"}, timeout=10)
      response.raise_for_status()

      data = response.json()
      params.put("StarPilotApiToken", data.get("api_token", ""))
      params.put("StarPilotDongleId", data.get("starpilot_dongle_id"))
    except Exception:
      pass

  threading.Thread(target=register_thread, daemon=True).start()


def uninstall_starpilot():
  update_boot_logo(stock=True)

  HARDWARE.uninstall()


def update_boot_logo(starpilot=False, stock=False, selected_logo=None):
  if HARDWARE.get_device_type() == "pc":
    return

  boot_logo_location = Path("/usr/comma/bg.jpg")

  if starpilot:
    target_logo = Path(BASEDIR) / "starpilot/assets/other_images/starpilot_boot_logo.jpg"
    if selected_logo:
      selected = selected_logo.decode("utf-8", "ignore") if isinstance(selected_logo, (bytes, bytearray)) else str(selected_logo)
      selected = selected.strip()
      if selected.lower() not in {"", "stock", "default"}:
        from openpilot.starpilot.common.theme_asset_names import find_matching_theme_asset_file

        matched_logo = find_matching_theme_asset_file(_theme_save_path() / "bootlogos", selected)
        if matched_logo is not None:
          target_logo = matched_logo
  elif stock:
    target_logo = Path(BASEDIR) / "starpilot/assets/other_images/stock_bg.jpg"
  else:
    print(f'Error: Must specify either "starpilot=True" or "stock=True"')
    return

  if not target_logo.is_file():
    print(f"Error: Target logo file not found at {target_logo}")
    return

  cache_key = _boot_logo_cache_key(selected_logo, target_logo)
  if boot_logo_location.is_file() and _boot_logo_cache_matches(cache_key):
    return

  source_logo = target_logo
  staged_logo = Path("/tmp/starpilot_boot_logo.jpg")
  try:
    from PIL import Image

    with Image.open(target_logo) as img:
      # weston.service always writes a JPEG copy of /usr/comma/bg.jpg; make sure
      # the source image is already RGB JPEG to avoid startup failure on RGBA assets.
      if img.format != "JPEG" or img.mode != "RGB":
        img.convert("RGB").save(staged_logo, format="JPEG", quality=95)
        source_logo = staged_logo
  except Exception as error:
    print(f"Error normalizing boot logo {target_logo}: {error}")
    if target_logo.suffix.lower() not in {".jpg", ".jpeg"}:
      print("Skipping boot logo update to keep weston startup stable.")
      return

  current_logo = boot_logo_location.read_bytes() if boot_logo_location.is_file() else b""
  desired_logo = source_logo.read_bytes()
  if current_logo != desired_logo:
    mount_options = _run_cmd(["findmnt", "-n", "-o", "OPTIONS", "/"], "Successfully retrieved mount options", "Failed to retrieve mount options")
    _run_cmd(["sudo", "mount", "-o", "remount,rw", "/"], "Successfully remounted / as read-write", "Failed to remount /")
    if _run_cmd(["sudo", "cp", source_logo, boot_logo_location], "Successfully replaced boot logo", "Failed to replace boot logo") is None:
      return
    _run_cmd(["sudo", "mount", "-o", f"remount,{mount_options}", "/"], "Successfully restored / mount options", "Failed to restore / mount options")
  _write_boot_logo_cache(cache_key)


def update_maps(now, params, params_memory, manual_update=False):
  from cereal import messaging
  from openpilot.starpilot.common.maps_catalog import normalize_schedule_value, sanitize_selected_locations_csv

  maps_selected_raw = params.get("MapsSelected")
  maps_selected = sanitize_selected_locations_csv(maps_selected_raw)
  if not maps_selected:
    return
  if isinstance(maps_selected_raw, bytes):
    maps_selected_raw = maps_selected_raw.decode("utf-8", errors="ignore")
  if maps_selected != (maps_selected_raw or ""):
    params.put("MapsSelected", maps_selected)

  day = now.day
  is_first = day == 1
  is_sunday = now.weekday() == 6
  schedule = normalize_schedule_value(params.get("PreferredSchedule"))

  maps_path = _maps_path()
  maps_downloaded = maps_path.exists() and any(path.is_file() for path in maps_path.rglob("*"))
  if maps_downloaded and (schedule == 0 or (schedule == 1 and not is_sunday) or (schedule == 2 and not is_first)) and not manual_update:
    return

  suffix = "th" if 11 <= day <= 13 else {1: "st", 2: "nd", 3: "rd"}.get(day % 10, "th")
  todays_date = now.strftime(f"%B {day}{suffix}, %Y")

  if maps_downloaded and params.get("LastMapsUpdate") == todays_date and not manual_update:
    return

  pm = messaging.PubMaster(["mapdIn"])
  sm = messaging.SubMaster(["mapdExtendedOut"])

  time.sleep(1)

  msg = messaging.new_message("mapdIn")
  msg.mapdIn.type = 0
  msg.mapdIn.str = maps_selected
  pm.send("mapdIn", msg)

  started = False
  while True:
    sm.update(1000)

    if params_memory.get_bool("CancelDownloadMaps"):
      msg = messaging.new_message("mapdIn")
      msg.mapdIn.type = 27
      pm.send("mapdIn", msg)

      params_memory.remove("CancelDownloadMaps")
      params_memory.remove("DownloadMaps")
      return

    if sm.updated["mapdExtendedOut"]:
      progress = sm["mapdExtendedOut"].downloadProgress

      if progress.active:
        started = True

      if not progress.active and started:
        break

  params.put("LastMapsUpdate", todays_date)
  params_memory.remove("DownloadMaps")


def update_openpilot(thread_manager, params):
  def update_available():
    _run_cmd(["pkill", "-SIGUSR1", "-f", "system.updated.updated"], "Checking for updates...", "Failed to check for update...", report=False)

    while params.get("UpdaterState") != "checking...":
      time.sleep(1)

    while params.get("UpdaterState") == "checking...":
      time.sleep(1)

    if not params.get_bool("UpdaterFetchAvailable"):
      return False

    while params.get_bool("IsOnroad") or thread_manager.is_thread_alive("lock_doors"):
      time.sleep(60)

    _run_cmd(["pkill", "-SIGHUP", "-f", "system.updated.updated"], "Update available, downloading...", "Failed to download update...", report=False)

    while not params.get_bool("UpdateAvailable"):
      time.sleep(60)

    return True

  if params.get("UpdaterState") != "idle":
    return

  while params.get_bool("IsOnroad") or thread_manager.is_thread_alive("lock_doors"):
    time.sleep(60)

  if not update_available():
    return

  while True:
    if not update_available():
      break

  while params.get_bool("IsOnroad") or thread_manager.is_thread_alive("lock_doors"):
    time.sleep(60)

  HARDWARE.reboot()
