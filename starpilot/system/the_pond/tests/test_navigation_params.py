import json

from openpilot.common.params import ParamKeyType
from openpilot.starpilot.system.the_pond import the_pond


class FakeParamsBackend:
  def __init__(self, key_types=None, default_values=None, values=None):
    self.key_types = key_types or {}
    self.default_values = default_values or {}
    self.values = values or {}
    self.writes = []

  def get_key_type(self, key):
    return self.key_types[key]

  def get_default_value(self, key):
    return self.default_values.get(key)

  def put(self, key, value):
    self.writes.append((key, value))
    self.values[key] = value

  def get(self, key, block=False):
    return self.values.get(key)


def test_params_compat_accepts_json_strings_for_json_keys():
  backend = FakeParamsBackend(
    key_types={"FavoriteDestinations": ParamKeyType.JSON},
    default_values={"FavoriteDestinations": []},
  )
  compat = the_pond.ParamsCompat(backend)

  compat.put("FavoriteDestinations", json.dumps([{"name": "Home"}]))

  assert backend.writes == [("FavoriteDestinations", [{"name": "Home"}])]


def test_navigation_last_position_uses_recent_persisted_fix(monkeypatch):
  recent_payload = json.dumps({
    "latitude": 41.0,
    "longitude": -87.0,
    "hasFix": True,
    "updatedAtSec": 10_000.0,
  })
  memory_backend = FakeParamsBackend(values={"LastGPSPosition": ""})
  persisted_backend = FakeParamsBackend(values={"LastGPSPosition": recent_payload})

  monkeypatch.setattr(the_pond, "params_memory", the_pond.ParamsCompat(memory_backend))
  monkeypatch.setattr(the_pond, "params", the_pond.ParamsCompat(persisted_backend))
  monkeypatch.setattr(the_pond.time, "time", lambda: 10_300.0)
  monkeypatch.setattr(the_pond, "system_time_valid", lambda: True)

  position = the_pond._get_navigation_last_position()

  assert position["latitude"] == 41.0
  assert position["longitude"] == -87.0


def test_navigation_last_position_rejects_stale_persisted_fix(monkeypatch):
  stale_payload = json.dumps({
    "latitude": 41.0,
    "longitude": -87.0,
    "hasFix": True,
    "updatedAtSec": 10_000.0,
  })
  memory_backend = FakeParamsBackend(values={"LastGPSPosition": ""})
  persisted_backend = FakeParamsBackend(values={"LastGPSPosition": stale_payload})

  monkeypatch.setattr(the_pond, "params_memory", the_pond.ParamsCompat(memory_backend))
  monkeypatch.setattr(the_pond, "params", the_pond.ParamsCompat(persisted_backend))
  monkeypatch.setattr(the_pond.time, "time", lambda: 10_000.0 + the_pond.NAVIGATION_PERSISTED_LOCATION_MAX_AGE_SECONDS + 1.0)
  monkeypatch.setattr(the_pond, "system_time_valid", lambda: True)

  assert the_pond._get_navigation_last_position() is None
