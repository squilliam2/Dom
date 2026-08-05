import numpy as np

from openpilot.tools.tuning.analyze_hyundai_torque_feedback import (
  angle_rate_quality_metrics,
  estimate_tracking_delay,
  fit_torque_map,
  tracking_stats,
)


def _synthetic_arrays(count: int = 12000, dt: float = 0.01) -> dict[str, np.ndarray]:
  t = np.arange(count) * dt
  desired = 0.7 * np.sin(2 * np.pi * 0.23 * t) + 0.2 * np.sin(2 * np.pi * 0.67 * t)
  desired_jerk = np.gradient(desired, dt)
  lag = 18
  actual = np.concatenate((np.zeros(lag), desired[:-lag]))
  torque = -((actual / 2.8) + 0.09 * np.sign(actual))
  angle = actual * 10.0
  return {
    "t": t,
    "segment": np.zeros(count, dtype=int),
    "v_ego": np.full(count, 20.0),
    "angle": angle,
    "angle_rate_sensor": np.gradient(angle, dt),
    "driver_torque": np.zeros(count),
    "steering_pressed": np.zeros(count, dtype=bool),
    "lat_active": np.ones(count, dtype=bool),
    "saturated": np.zeros(count, dtype=bool),
    "lane_change": np.zeros(count, dtype=bool),
    "applied_torque": torque,
    "actual_la": actual,
    "desired_la": desired,
    "desired_jerk": desired_jerk,
    "p": np.zeros(count),
    "i": np.zeros(count),
  }


def test_tracking_delay_recovers_known_lag():
  arrays = _synthetic_arrays()
  mask = np.ones(len(arrays["t"]), dtype=bool)
  result = estimate_tracking_delay(arrays, mask, 0.01)
  assert result["identifiable"]
  np.testing.assert_allclose(result["lag_s"], 0.18, atol=0.01)


def test_torque_map_recovers_linear_gain_and_friction():
  arrays = _synthetic_arrays()
  mask = np.ones(len(arrays["t"]), dtype=bool)
  result = fit_torque_map(arrays, mask)
  assert result["identifiable"]
  np.testing.assert_allclose(result["implied_lat_accel_factor"], 2.8, atol=0.02)
  np.testing.assert_allclose(result["friction_torque"], 0.09, atol=0.005)


def test_tracking_stats_reports_bias_and_gain():
  arrays = _synthetic_arrays(2000)
  arrays["actual_la"] = arrays["desired_la"] * 0.8 + 0.05
  stats = tracking_stats(arrays, np.ones(2000, dtype=bool))
  np.testing.assert_allclose(stats["bias"], 0.05 - 0.2 * np.mean(arrays["desired_la"]), atol=1e-8)
  assert stats["mae"] > 0.05


def test_angle_rate_quality_rejects_unsigned_hyundai_signal():
  arrays = _synthetic_arrays()
  mask = np.ones(len(arrays["t"]), dtype=bool)
  signed = angle_rate_quality_metrics(arrays, mask, 0.01)
  assert signed["usable_signed_feedback"]

  arrays["angle_rate_sensor"] = np.abs(arrays["angle_rate_sensor"])
  unsigned = angle_rate_quality_metrics(arrays, mask, 0.01)
  assert not unsigned["usable_signed_feedback"]
