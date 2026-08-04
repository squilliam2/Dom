import datetime
import os
import time

from openpilot.system import timed


def test_gps_timestamp_is_decoded_as_utc(monkeypatch):
  original_timezone = os.environ.get("TZ")
  monkeypatch.setenv("TZ", "America/New_York")
  time.tzset()
  try:
    gps_time = timed.utc_from_unix_millis(1782694275400)
  finally:
    if original_timezone is None:
      monkeypatch.delenv("TZ")
    else:
      monkeypatch.setenv("TZ", original_timezone)
    time.tzset()

  assert gps_time == datetime.datetime(2026, 6, 29, 0, 51, 15, 400000)
  assert gps_time.tzinfo is None


def test_set_time_uses_utc_for_comparison_and_clock_update(monkeypatch):
  now = datetime.datetime(2026, 6, 28, 20, 51, 15, 400000)
  gps_time = datetime.datetime(2026, 6, 29, 0, 51, 15, 400000)
  calls = []

  monkeypatch.setattr(timed, "utc_now", lambda: now)
  monkeypatch.setattr(timed.subprocess, "run", lambda *args, **kwargs: calls.append((args, kwargs)))

  timed.set_time(gps_time)

  assert calls == [
    ((["date", "-u", "-s", "2026-06-29 00:51:15.400000"],), {"check": True}),
  ]


def test_set_time_ignores_small_utc_difference(monkeypatch):
  now = datetime.datetime(2026, 6, 29, 0, 51, 20)
  calls = []

  monkeypatch.setattr(timed, "utc_now", lambda: now)
  monkeypatch.setattr(timed.subprocess, "run", lambda *args, **kwargs: calls.append((args, kwargs)))

  timed.set_time(datetime.datetime(2026, 6, 29, 0, 51, 15))

  assert calls == []
