#!/usr/bin/env python3
"""Identify torque-steering behavior from raw openpilot rlogs.

This tool deliberately separates observations from tuning decisions. It only
uses rlogs, removes driver overrides and saturated samples from system
identification, and reports when an estimate is too weak to trust.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass, field
import json
import math
from pathlib import Path
import re
import sys
from typing import Any

import numpy as np

from openpilot.tools.lib.logreader import LogReader, ReadMode, parse_indirect
from openpilot.tools.lib.route import Route, SegmentRange


MIN_IDENT_SPEED = 3.0
MIN_STEADY_SPEED = 8.0
MAX_IDENT_LAG_S = 0.50
TRANSITION_JERK = 0.15


SAMPLE_FIELDS = (
  "t", "segment", "v_ego", "angle", "angle_rate_sensor", "driver_torque", "eps_torque",
  "steering_pressed", "lat_active", "saturated", "lane_change", "left_blinker", "right_blinker",
  "requested_torque", "applied_torque", "torque_output_can", "actual_la", "desired_la", "desired_jerk",
  "curvature", "desired_curvature", "model_curvature", "p", "i", "d", "f", "roll", "angle_offset",
  "live_steer_ratio", "live_stiffness", "live_delay", "controller_version", "lane_confidence",
  "lane_center_0", "lane_width_0", "left_lane_y_0", "right_lane_y_0", "planned_path_offset_10",
)


@dataclass
class RouteData:
  route: str
  values: dict[str, list[Any]] = field(default_factory=lambda: {key: [] for key in SAMPLE_FIELDS})
  metadata: dict[str, Any] = field(default_factory=dict)

  def append(self, **sample: Any) -> None:
    for key in SAMPLE_FIELDS:
      self.values[key].append(sample[key])

  def arrays(self) -> dict[str, np.ndarray]:
    bool_fields = {
      "steering_pressed", "lat_active", "saturated", "lane_change", "left_blinker", "right_blinker",
    }
    int_fields = {"segment", "controller_version"}
    arrays: dict[str, np.ndarray] = {}
    for key, values in self.values.items():
      dtype = bool if key in bool_fields else int if key in int_fields else float
      arrays[key] = np.asarray(values, dtype=dtype)
    return arrays

  def save(self, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = self.arrays()
    payload["route"] = np.asarray(self.route)
    payload["metadata_json"] = np.asarray(json.dumps(self.metadata, allow_nan=True))
    np.savez_compressed(path, **payload)

  @classmethod
  def load(cls, path: Path) -> RouteData:
    with np.load(path, allow_pickle=False) as payload:
      data = cls(route=str(payload["route"]))
      data.metadata = json.loads(str(payload["metadata_json"]))
      for key in SAMPLE_FIELDS:
        data.values[key] = payload[key].tolist()
    return data


def cache_path(cache_dir: Path, route: str) -> Path:
  return cache_dir / f"{re.sub(r'[^A-Za-z0-9_.-]+', '_', route)}.npz"


def _enum_name(value: Any) -> str:
  return str(value).rsplit(".", 1)[-1].lower()


def _finite_float(value: Any, default: float = math.nan) -> float:
  try:
    converted = float(value)
    return converted if math.isfinite(converted) else default
  except (TypeError, ValueError):
    return default


def _safe_attr(obj: Any, name: str, default: Any = None) -> Any:
  try:
    return getattr(obj, name)
  except Exception:
    return default


def _extract_car_params(cp: Any) -> dict[str, Any]:
  tune = _safe_attr(_safe_attr(cp, "lateralTuning"), "torque")
  return {
    "car_fingerprint": str(_safe_attr(cp, "carFingerprint", "")),
    "car_name": str(_safe_attr(cp, "carName", "")),
    "steer_ratio": _finite_float(_safe_attr(cp, "steerRatio")),
    "actuator_delay": _finite_float(_safe_attr(cp, "steerActuatorDelay")),
    "steer_limit_timer": _finite_float(_safe_attr(cp, "steerLimitTimer")),
    "vehicle_width": _finite_float(_safe_attr(cp, "width")),
    "lat_accel_factor": _finite_float(_safe_attr(tune, "latAccelFactor")),
    "lat_accel_offset": _finite_float(_safe_attr(tune, "latAccelOffset")),
    "friction": _finite_float(_safe_attr(tune, "friction")),
    "steering_angle_deadzone_deg": _finite_float(_safe_attr(tune, "steeringAngleDeadzoneDeg")),
  }


def _extract_init_data(init_data: Any) -> dict[str, Any]:
  return {
    "git_commit": str(_safe_attr(init_data, "gitCommit", "")),
    "git_branch": str(_safe_attr(init_data, "gitBranch", "")),
    "git_remote": str(_safe_attr(init_data, "gitRemote", "")),
    "version": str(_safe_attr(init_data, "version", "")),
  }


def _interpolate_xy(polyline: Any, distance: float) -> float:
  try:
    x = np.asarray(polyline.x, dtype=float)
    y = np.asarray(polyline.y, dtype=float)
  except Exception:
    return math.nan
  valid = np.isfinite(x) & np.isfinite(y)
  if valid.sum() < 2:
    return math.nan
  x = x[valid]
  y = y[valid]
  order = np.argsort(x)
  x = x[order]
  y = y[order]
  if distance < x[0] or distance > x[-1]:
    return math.nan
  return float(np.interp(distance, x, y))


def _extract_lane_geometry(model: Any) -> tuple[float, float, float, float, float, float]:
  if model is None:
    return (math.nan,) * 6
  try:
    lane_lines = model.laneLines
    lane_probs = np.asarray(model.laneLineProbs, dtype=float)
    if len(lane_lines) < 4 or lane_probs.size < 4:
      return (math.nan,) * 6
    left = lane_lines[1]
    right = lane_lines[2]
    confidence = float(min(lane_probs[1], lane_probs[2]))
    left_0 = _interpolate_xy(left, 0.0)
    right_0 = _interpolate_xy(right, 0.0)
    left_10 = _interpolate_xy(left, 10.0)
    right_10 = _interpolate_xy(right, 10.0)
    path_10 = _interpolate_xy(model.position, 10.0)
    lane_center_0 = 0.5 * (left_0 + right_0)
    lane_width_0 = right_0 - left_0
    # modelV2 uses +y right; expose offsets as +left in the report.
    planned_offset_10 = 0.5 * (left_10 + right_10) - path_10
    return confidence, lane_center_0, lane_width_0, left_0, right_0, planned_offset_10
  except Exception:
    return (math.nan,) * 6


def read_route(route: str, max_segments: int | None = None) -> RouteData:
  # Resolve signed rlog URLs once, then release each segment after parsing it.
  source_route = parse_indirect(route)
  segment_range = SegmentRange(source_route)
  remote_route = Route(segment_range.route_name)
  rlog_paths = remote_route.log_paths()
  requested_segments = segment_range.seg_idxs if segment_range.slice else list(range(len(rlog_paths)))
  if max_segments is not None:
    requested_segments = requested_segments[:max_segments]
  identifiers = [(segment, rlog_paths[segment]) for segment in requested_segments
                 if 0 <= segment < len(rlog_paths) and rlog_paths[segment] is not None]
  missing_segments = [segment for segment in requested_segments
                      if segment < 0 or segment >= len(rlog_paths) or rlog_paths[segment] is None]
  if not identifiers:
    raise RuntimeError(f"no rlogs available; requested segments={requested_segments}")

  result = RouteData(route=route)
  result.metadata["segments"] = len(identifiers)
  result.metadata["segments_requested"] = len(requested_segments)
  result.metadata["missing_rlog_segments"] = missing_segments
  latest: dict[str, Any] = {}
  latest_time: dict[str, float] = {}

  for progress_index, (segment_index, identifier) in enumerate(identifiers):
    print(f"[{route}] rlog segment {segment_index} ({progress_index + 1}/{len(identifiers)})", file=sys.stderr)
    for msg in LogReader(identifier, default_mode=ReadMode.RLOG, sort_by_time=True):
      which = msg.which()
      t = msg.logMonoTime / 1e9

      if which == "initData" and "git_commit" not in result.metadata:
        result.metadata.update(_extract_init_data(msg.initData))
      elif which == "carParams" and "car_fingerprint" not in result.metadata:
        result.metadata.update(_extract_car_params(msg.carParams))
      elif which in ("carState", "carControl", "carOutput", "liveParameters", "liveDelay", "modelV2"):
        latest[which] = getattr(msg, which)
        latest_time[which] = t

      if which != "controlsState" or "carState" not in latest or "carControl" not in latest:
        continue
      if t - latest_time["carState"] > 0.10 or t - latest_time["carControl"] > 0.10:
        continue

      controls = msg.controlsState
      lateral_state = controls.lateralControlState
      if lateral_state.which() != "torqueState":
        continue

      torque_state = lateral_state.torqueState
      car_state = latest["carState"]
      car_control = latest["carControl"]
      car_output = latest.get("carOutput")
      live_params = latest.get("liveParameters")
      live_delay = latest.get("liveDelay")
      model = latest.get("modelV2")

      model_curvature = math.nan
      lane_change = False
      if model is not None:
        action = _safe_attr(model, "action")
        model_curvature = _finite_float(_safe_attr(action, "desiredCurvature"))
        meta = _safe_attr(model, "meta")
        lane_change = _enum_name(_safe_attr(meta, "laneChangeState", "off")) != "off"
      lane_confidence, lane_center_0, lane_width_0, left_lane_y_0, right_lane_y_0, planned_path_offset_10 = \
        _extract_lane_geometry(model)

      output_actuators = _safe_attr(car_output, "actuatorsOutput")
      requested_torque = _finite_float(_safe_attr(car_control.actuators, "torque"))
      applied_torque = _finite_float(_safe_attr(output_actuators, "torque"), requested_torque)

      result.append(
        t=t,
        segment=segment_index,
        v_ego=_finite_float(car_state.vEgo),
        angle=_finite_float(car_state.steeringAngleDeg),
        angle_rate_sensor=_finite_float(car_state.steeringRateDeg),
        driver_torque=_finite_float(car_state.steeringTorque),
        eps_torque=_finite_float(car_state.steeringTorqueEps),
        steering_pressed=bool(car_state.steeringPressed),
        lat_active=bool(car_control.latActive),
        saturated=bool(torque_state.saturated),
        lane_change=lane_change,
        left_blinker=bool(_safe_attr(car_state, "leftBlinker", False)),
        right_blinker=bool(_safe_attr(car_state, "rightBlinker", False)),
        requested_torque=requested_torque,
        applied_torque=applied_torque,
        torque_output_can=_finite_float(_safe_attr(output_actuators, "torqueOutputCan")),
        actual_la=_finite_float(torque_state.actualLateralAccel),
        desired_la=_finite_float(torque_state.desiredLateralAccel),
        desired_jerk=_finite_float(torque_state.desiredLateralJerk),
        curvature=_finite_float(controls.curvature),
        desired_curvature=_finite_float(controls.desiredCurvature),
        model_curvature=model_curvature,
        p=_finite_float(torque_state.p),
        i=_finite_float(torque_state.i),
        d=_finite_float(torque_state.d),
        f=_finite_float(torque_state.f),
        roll=_finite_float(_safe_attr(live_params, "roll")),
        angle_offset=_finite_float(_safe_attr(live_params, "angleOffsetDeg")),
        live_steer_ratio=_finite_float(_safe_attr(live_params, "steerRatio")),
        live_stiffness=_finite_float(_safe_attr(live_params, "stiffnessFactor")),
        live_delay=_finite_float(_safe_attr(live_delay, "lateralDelay")),
        controller_version=int(_safe_attr(torque_state, "version", 0)),
        lane_confidence=lane_confidence,
        lane_center_0=lane_center_0,
        lane_width_0=lane_width_0,
        left_lane_y_0=left_lane_y_0,
        right_lane_y_0=right_lane_y_0,
        planned_path_offset_10=planned_path_offset_10,
      )

  return result


def _sample_dt(a: dict[str, np.ndarray]) -> float:
  same_segment = a["segment"][1:] == a["segment"][:-1]
  diffs = np.diff(a["t"])[same_segment]
  diffs = diffs[(diffs > 0.001) & (diffs < 0.1)]
  return float(np.median(diffs)) if diffs.size else 0.01


def clean_mask(a: dict[str, np.ndarray], *, include_lane_changes: bool = False) -> np.ndarray:
  finite = np.ones(len(a["t"]), dtype=bool)
  for field in ("v_ego", "actual_la", "desired_la", "desired_jerk", "applied_torque", "angle"):
    finite &= np.isfinite(a[field])
  mask = finite & a["lat_active"] & (~a["steering_pressed"]) & (~a["saturated"]) & (a["v_ego"] >= MIN_IDENT_SPEED)
  if not include_lane_changes:
    mask &= ~a["lane_change"]
  return mask


def tracking_stats(a: dict[str, np.ndarray], mask: np.ndarray) -> dict[str, float | int]:
  if mask.sum() == 0:
    return {"n": 0}
  residual = a["actual_la"][mask] - a["desired_la"][mask]
  desired = a["desired_la"][mask]
  denominator = float(np.dot(desired, desired))
  gain = float(np.dot(desired, a["actual_la"][mask]) / denominator) if denominator > 1e-9 else math.nan
  return {
    "n": int(mask.sum()),
    "mae": float(np.mean(np.abs(residual))),
    "rmse": float(np.sqrt(np.mean(residual ** 2))),
    "bias": float(np.mean(residual)),
    "p95_abs": float(np.percentile(np.abs(residual), 95)),
    "gain_through_origin": gain,
  }


def tracking_contexts(a: dict[str, np.ndarray], base: np.ndarray) -> dict[str, dict[str, float | int]]:
  desired = a["desired_la"]
  jerk = a["desired_jerk"]
  contexts = {
    "all": base,
    "straight": base & (np.abs(desired) < 0.15),
    "left": base & (desired >= 0.15),
    "right": base & (desired <= -0.15),
    "turn_in": base & (np.abs(jerk) >= TRANSITION_JERK) & ((desired * jerk) > 0.0),
    "unwind": base & (np.abs(jerk) >= TRANSITION_JERK) & ((desired * jerk) < 0.0),
    "low_speed": base & (a["v_ego"] < 8.0),
    "medium_speed": base & (a["v_ego"] >= 8.0) & (a["v_ego"] < 18.0),
    "high_speed": base & (a["v_ego"] >= 18.0),
  }
  return {name: tracking_stats(a, mask) for name, mask in contexts.items()}


def _moving_average(values: np.ndarray, count: int) -> np.ndarray:
  count = max(int(count), 1)
  if count == 1:
    return values.copy()
  left = count // 2
  right = count - 1 - left
  padded = np.pad(values, (left, right), mode="edge")
  return np.convolve(padded, np.ones(count) / count, mode="valid")


def estimate_tracking_delay(a: dict[str, np.ndarray], base: np.ndarray, dt: float) -> dict[str, float | int | bool]:
  """Cross-correlate desired and measured lateral jerk.

  This is the closed-loop desired-to-measured delay, not a claim about pure EPS
  transport delay. It is only accepted when transitions have useful correlation.
  """
  smooth_count = max(round(0.12 / dt), 3)
  actual = _moving_average(a["actual_la"], smooth_count)
  actual_jerk = np.gradient(actual, dt)
  max_lag = max(1, round(MAX_IDENT_LAG_S / dt))
  scores: list[tuple[int, float, int]] = []
  for lag in range(max_lag + 1):
    current = np.arange(lag, len(actual))
    source = current - lag
    valid = base[current] & base[source] & (a["segment"][current] == a["segment"][source])
    valid &= np.abs(a["desired_jerk"][source]) >= TRANSITION_JERK
    x = a["desired_jerk"][source][valid]
    y = actual_jerk[current][valid]
    if x.size < 250 or np.std(x) < 1e-5 or np.std(y) < 1e-5:
      continue
    scores.append((lag, float(np.corrcoef(x, y)[0, 1]), int(x.size)))

  if not scores:
    return {"identifiable": False, "reason": "insufficient transition data"}
  best_lag, best_corr, count = max(scores, key=lambda item: item[1])
  zero_corr = next((corr for lag, corr, _ in scores if lag == 0), math.nan)
  near_best = [lag for lag, corr, _ in scores if corr >= best_corr - 0.01]
  identifiable = best_corr >= 0.20 and len(near_best) * dt <= 0.20
  return {
    "identifiable": identifiable,
    "lag_s": best_lag * dt,
    "correlation": best_corr,
    "zero_lag_correlation": zero_corr,
    "near_best_min_s": min(near_best) * dt,
    "near_best_max_s": max(near_best) * dt,
    "n": count,
  }


def _standardized_lstsq(x_train: np.ndarray, y_train: np.ndarray, x_test: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
  mean = np.mean(x_train, axis=0)
  scale = np.std(x_train, axis=0)
  scale[scale < 1e-8] = 1.0
  train = (x_train - mean) / scale
  test = (x_test - mean) / scale
  train = np.column_stack((train, np.ones(len(train))))
  test = np.column_stack((test, np.ones(len(test))))
  beta = np.linalg.lstsq(train, y_train, rcond=None)[0]
  return train @ beta, test @ beta


def estimate_torque_to_motion_delay(a: dict[str, np.ndarray], base: np.ndarray, dt: float) -> dict[str, float | int | bool]:
  """Select a bounded ARX input lag using held-out 10-second blocks."""
  if len(a["t"]) < 1000:
    return {"identifiable": False, "reason": "insufficient samples"}
  angle = _moving_average(a["angle"], max(round(0.08 / dt), 3))
  angle_rate = np.gradient(angle, dt)
  max_lag = max(1, round(MAX_IDENT_LAG_S / dt))
  scores: list[tuple[int, float, int]] = []

  for lag in range(max_lag + 1):
    idx = np.arange(max(lag, 1), len(angle) - 1)
    source = idx - lag
    contiguous = (a["segment"][idx + 1] == a["segment"][idx]) & (a["segment"][idx] == a["segment"][source])
    valid = base[idx] & base[idx + 1] & base[source] & contiguous
    valid &= (np.abs(np.diff(a["applied_torque"], prepend=a["applied_torque"][0])[source]) > 0.001) | (np.abs(angle_rate[idx]) > 0.5)
    idx = idx[valid]
    source = source[valid]
    if idx.size < 1000:
      continue

    x = np.column_stack((
      angle_rate[idx],
      angle[idx],
      angle[idx] * a["v_ego"][idx] ** 2,
      a["applied_torque"][source],
      a["driver_torque"][idx],
      np.sign(angle_rate[idx]),
    ))
    y = angle_rate[idx + 1]
    block = (np.floor((a["t"][idx] - a["t"][idx[0]]) / 10.0).astype(int) % 5)
    train = block != 0
    test = block == 0
    if train.sum() < 700 or test.sum() < 200:
      continue
    _, prediction = _standardized_lstsq(x[train], y[train], x[test])
    rmse = float(np.sqrt(np.mean((prediction - y[test]) ** 2)))
    scores.append((lag, rmse, int(test.sum())))

  if not scores:
    return {"identifiable": False, "reason": "insufficient clean excitation"}
  best_lag, best_rmse, count = min(scores, key=lambda item: item[1])
  zero_rmse = next((rmse for lag, rmse, _ in scores if lag == 0), math.nan)
  near_best = [lag for lag, rmse, _ in scores if rmse <= best_rmse * 1.002]
  improvement = (zero_rmse - best_rmse) / zero_rmse if zero_rmse > 0 else 0.0
  # A shallow optimum or one pinned to the search boundary is not a measured
  # transport delay. Require a useful held-out improvement, a narrow optimum,
  # and room on both sides of the selected lag before accepting it.
  search_margin = max(round(0.03 / dt), 2)
  identifiable = (improvement >= 0.02 and
                  len(near_best) * dt <= 0.10 and
                  search_margin <= best_lag <= max_lag - search_margin)
  return {
    "identifiable": identifiable,
    "lag_s": best_lag * dt,
    "validation_rmse_deg_s": best_rmse,
    "zero_lag_rmse_deg_s": zero_rmse,
    "relative_improvement": improvement,
    "near_best_min_s": min(near_best) * dt,
    "near_best_max_s": max(near_best) * dt,
    "n_validation": count,
  }


def fit_torque_map(a: dict[str, np.ndarray], base: np.ndarray) -> dict[str, float | int | bool]:
  steady = base & (a["v_ego"] >= MIN_STEADY_SPEED) & (np.abs(a["desired_jerk"]) < 0.10)
  steady &= (np.abs(a["actual_la"]) >= 0.08) & (np.abs(a["actual_la"]) <= 2.5)
  steady &= np.abs(a["p"] + a["i"]) < 0.18
  x_la = a["actual_la"][steady]
  # Torque-control lateral acceleration uses the opposite sign from Hyundai's
  # normalized actuator command at the CarControl boundary.
  y_torque = -a["applied_torque"][steady]
  if x_la.size < 500:
    return {"identifiable": False, "reason": "insufficient steady clean samples", "n": int(x_la.size)}

  keep = np.ones(x_la.size, dtype=bool)
  beta = np.zeros(3)
  for _ in range(4):
    x = np.column_stack((x_la[keep], np.sign(x_la[keep]), np.ones(keep.sum())))
    beta = np.linalg.lstsq(x, y_torque[keep], rcond=None)[0]
    residual = y_torque - (beta[0] * x_la + beta[1] * np.sign(x_la) + beta[2])
    median = np.median(residual[keep])
    mad = np.median(np.abs(residual[keep] - median))
    if mad < 1e-6:
      break
    keep = np.abs(residual - median) <= 4.0 * 1.4826 * mad

  residual = y_torque[keep] - (beta[0] * x_la[keep] + beta[1] * np.sign(x_la[keep]) + beta[2])
  side_slopes: dict[str, float] = {}
  for name, side in (("left", x_la > 0.0), ("right", x_la < 0.0)):
    side &= keep
    if side.sum() >= 150:
      design = np.column_stack((x_la[side], np.ones(side.sum())))
      side_slopes[name] = float(np.linalg.lstsq(design, y_torque[side], rcond=None)[0][0])

  slope = float(beta[0])
  return {
    "identifiable": slope > 0.02,
    "n": int(keep.sum()),
    "torque_per_mps2": slope,
    "implied_lat_accel_factor": 1.0 / slope if slope > 0.02 else math.nan,
    "friction_torque": float(abs(beta[1])),
    "left_right_offset": float(beta[2]),
    "left_torque_per_mps2": side_slopes.get("left", math.nan),
    "right_torque_per_mps2": side_slopes.get("right", math.nan),
    "mae_torque": float(np.mean(np.abs(residual))),
  }


def torque_utilization_metrics(a: dict[str, np.ndarray]) -> dict[str, float | int]:
  mask = a["lat_active"] & np.isfinite(a["requested_torque"]) & np.isfinite(a["applied_torque"])
  if not np.any(mask):
    return {"n": 0}
  requested = np.abs(a["requested_torque"][mask])
  applied = np.abs(a["applied_torque"][mask])
  limited = np.abs(a["requested_torque"][mask] - a["applied_torque"][mask]) > 0.01
  return {
    "n": int(mask.sum()),
    "requested_p95": float(np.percentile(requested, 95)),
    "requested_max": float(np.max(requested)),
    "applied_p95": float(np.percentile(applied, 95)),
    "applied_max": float(np.max(applied)),
    "fraction_applied_above_0p90": float(np.mean(applied >= 0.90)),
    "fraction_applied_above_0p98": float(np.mean(applied >= 0.98)),
    "fraction_request_limited": float(np.mean(limited)),
  }


def angle_rate_quality_metrics(a: dict[str, np.ndarray], base: np.ndarray, dt: float) -> dict[str, float | int | bool]:
  """Validate the CAN steering-rate signal against signed angle differentiation."""
  derived = np.gradient(_moving_average(a["angle"], max(round(0.08 / dt), 3)), dt)
  valid = base & np.isfinite(a["angle_rate_sensor"]) & np.isfinite(derived)
  valid &= np.abs(derived) >= 0.5
  if valid.sum() < 500:
    return {"usable_signed_feedback": False, "reason": "insufficient steering motion", "n": int(valid.sum())}

  sensor = a["angle_rate_sensor"][valid]
  reference = derived[valid]
  signed_corr = float(np.corrcoef(sensor, reference)[0, 1]) if np.std(sensor) > 1e-6 else math.nan
  magnitude_corr = float(np.corrcoef(np.abs(sensor), np.abs(reference))[0, 1]) if np.std(np.abs(sensor)) > 1e-6 else math.nan
  sign_agreement = float(np.mean(np.sign(sensor) == np.sign(reference)))
  negative_fraction = float(np.mean(sensor < 0.0))
  slope = float(np.dot(sensor, reference) / np.dot(sensor, sensor)) if np.dot(sensor, sensor) > 1e-6 else math.nan
  usable = signed_corr >= 0.90 and sign_agreement >= 0.95 and 0.5 <= slope <= 1.5
  return {
    "usable_signed_feedback": usable,
    "n": int(valid.sum()),
    "signed_correlation": signed_corr,
    "magnitude_correlation": magnitude_corr,
    "sign_agreement": sign_agreement,
    "sensor_negative_fraction": negative_fraction,
    "derived_per_sensor_scale": slope,
  }


def realization_integrator_metrics(a: dict[str, np.ndarray], dt: float) -> dict[str, float | int | bool]:
  """Quantify controller state while CAN/driver limits prevent torque realization."""
  valid = a["lat_active"] & np.isfinite(a["requested_torque"]) & np.isfinite(a["applied_torque"])
  valid &= np.isfinite(a["i"]) & np.isfinite(a["desired_la"]) & np.isfinite(a["actual_la"])
  limited = valid & (np.abs(a["requested_torque"] - a["applied_torque"]) > 0.01)
  unrestricted = valid & ~limited
  if limited.sum() < 100:
    return {"identifiable": False, "reason": "insufficient torque-limited samples", "n": int(limited.sum())}

  ends = np.flatnonzero(limited[:-1] & ~limited[1:] & (a["segment"][:-1] == a["segment"][1:])) + 1
  horizon = max(round(0.75 / dt), 1)
  overshoot: list[float] = []
  for index in ends:
    stop = min(index + horizon, len(a["t"]))
    future = np.arange(index, stop)
    future = future[(a["segment"][future] == a["segment"][index]) & valid[future]]
    if future.size < horizon // 2 or abs(a["desired_la"][index]) < 0.10:
      continue
    direction = math.copysign(1.0, a["desired_la"][index])
    # Positive means the vehicle went farther into the turn than requested.
    overshoot.append(float(np.max(direction * (a["actual_la"][future] - a["desired_la"][future]))))

  return {
    "identifiable": True,
    "n": int(limited.sum()),
    "limited_seconds": float(limited.sum() * dt),
    "integrator_abs_median_limited": float(np.median(np.abs(a["i"][limited]))),
    "integrator_abs_p95_limited": float(np.percentile(np.abs(a["i"][limited]), 95)),
    "integrator_abs_median_unrestricted": float(np.median(np.abs(a["i"][unrestricted]))) if np.any(unrestricted) else math.nan,
    "release_events": len(overshoot),
    "post_release_overshoot_median_mps2": float(np.median(overshoot)) if overshoot else math.nan,
    "post_release_overshoot_p95_mps2": float(np.percentile(overshoot, 95)) if overshoot else math.nan,
  }


def lane_geometry_metrics(a: dict[str, np.ndarray], base: np.ndarray, vehicle_width: float) -> dict[str, float | int | bool]:
  valid = base & (a["lane_confidence"] >= 0.60) & np.isfinite(a["lane_center_0"])
  valid &= np.isfinite(a["lane_width_0"]) & (a["lane_width_0"] >= 2.4) & (a["lane_width_0"] <= 5.0)
  if valid.sum() < 250:
    return {"identifiable": False, "reason": "insufficient high-confidence two-lane-line samples", "n": int(valid.sum())}

  # modelV2 coordinates are +y right. A perceived center to the right of the
  # camera means the car is left of center, so this is already +left.
  car_offset_left_positive = a["lane_center_0"][valid]
  planned_valid = valid & np.isfinite(a["planned_path_offset_10"])
  half_width = vehicle_width * 0.5 if math.isfinite(vehicle_width) and vehicle_width > 1.0 else 0.95
  left_margin = -a["left_lane_y_0"][valid] - half_width
  right_margin = a["right_lane_y_0"][valid] - half_width
  return {
    "identifiable": True,
    "n": int(valid.sum()),
    "lane_width_median_m": float(np.median(a["lane_width_0"][valid])),
    "car_offset_left_positive_mean_m": float(np.mean(car_offset_left_positive)),
    "car_offset_left_positive_median_m": float(np.median(car_offset_left_positive)),
    "car_offset_left_positive_p05_m": float(np.percentile(car_offset_left_positive, 5)),
    "car_offset_left_positive_p95_m": float(np.percentile(car_offset_left_positive, 95)),
    "left_tire_margin_p05_m": float(np.percentile(left_margin, 5)),
    "right_tire_margin_p05_m": float(np.percentile(right_margin, 5)),
    "fraction_left_margin_below_0p25": float(np.mean(left_margin < 0.25)),
    "fraction_right_margin_below_0p25": float(np.mean(right_margin < 0.25)),
    "planned_path_offset_left_positive_10m_mean_m": float(np.mean(a["planned_path_offset_10"][planned_valid])) if np.any(planned_valid) else math.nan,
    "planned_path_offset_left_positive_10m_p95_abs_m": float(np.percentile(np.abs(a["planned_path_offset_10"][planned_valid]), 95)) if np.any(planned_valid) else math.nan,
  }


def _dominant_frequency(values: np.ndarray, mask: np.ndarray, segments: np.ndarray, dt: float,
                        low_hz: float = 0.15, high_hz: float = 2.0) -> tuple[float, float]:
  nfft = max(256, round(10.24 / dt))
  nfft = 1 << int(math.floor(math.log2(nfft)))
  spectra: list[np.ndarray] = []
  start = 0
  while start < len(mask):
    if not mask[start]:
      start += 1
      continue
    end = start + 1
    while end < len(mask) and mask[end] and segments[end] == segments[end - 1]:
      end += 1
    for chunk_start in range(start, end - nfft + 1, nfft // 2):
      chunk = values[chunk_start:chunk_start + nfft]
      chunk = chunk - np.mean(chunk)
      spectra.append(np.abs(np.fft.rfft(chunk * np.hanning(nfft))) ** 2)
    start = end

  if not spectra:
    return math.nan, math.nan
  power = np.mean(spectra, axis=0)
  frequencies = np.fft.rfftfreq(nfft, dt)
  band = (frequencies >= low_hz) & (frequencies <= high_hz)
  if not np.any(band):
    return math.nan, math.nan
  frequency = float(frequencies[band][np.argmax(power[band])])
  total = float(np.sum(power[1:]))
  fraction = float(np.sum(power[band]) / total) if total > 0 else math.nan
  return frequency, fraction


def lane_dynamics_metrics(a: dict[str, np.ndarray], base: np.ndarray, dt: float) -> dict[str, float | int | bool]:
  valid = base & (a["lane_confidence"] >= 0.60) & np.isfinite(a["lane_center_0"])
  valid &= np.isfinite(a["planned_path_offset_10"]) & np.isfinite(a["lane_width_0"])
  valid &= (a["lane_width_0"] >= 2.4) & (a["lane_width_0"] <= 5.0) & (np.abs(a["desired_la"]) < 0.15)
  if valid.sum() < 2000:
    return {"identifiable": False, "reason": "insufficient clean straight lane geometry", "n": int(valid.sum())}

  car_offset = a["lane_center_0"]
  path_offset = a["planned_path_offset_10"]
  path_tracking_error = car_offset - path_offset
  corr = float(np.corrcoef(car_offset[valid], path_offset[valid])[0, 1])
  car_frequency, car_band_fraction = _dominant_frequency(car_offset, valid, a["segment"], dt)
  path_frequency, path_band_fraction = _dominant_frequency(path_offset, valid, a["segment"], dt)
  error_frequency, error_band_fraction = _dominant_frequency(path_tracking_error, valid, a["segment"], dt)
  return {
    "identifiable": True,
    "n": int(valid.sum()),
    "car_vs_planned_path_correlation": corr,
    "path_tracking_error_rms_m": float(np.sqrt(np.mean(path_tracking_error[valid] ** 2))),
    "car_offset_dominant_frequency_hz": car_frequency,
    "car_offset_power_fraction_0p15_to_2hz": car_band_fraction,
    "planned_path_dominant_frequency_hz": path_frequency,
    "planned_path_power_fraction_0p15_to_2hz": path_band_fraction,
    "path_tracking_error_dominant_frequency_hz": error_frequency,
    "path_tracking_error_power_fraction_0p15_to_2hz": error_band_fraction,
  }


def _threshold_sign_flips(values: np.ndarray, mask: np.ndarray, threshold: float) -> int:
  state = 0
  flips = 0
  for value, valid in zip(values, mask, strict=True):
    if not valid:
      state = 0
      continue
    new_state = 1 if value > threshold else -1 if value < -threshold else state
    if state and new_state and new_state != state:
      flips += 1
    state = new_state
  return flips


def oscillation_metrics(a: dict[str, np.ndarray], base: np.ndarray, dt: float) -> dict[str, float | int | bool]:
  straight = base & (a["v_ego"] >= 8.0) & (np.abs(a["desired_la"]) < 0.15)
  duration_min = straight.sum() * dt / 60.0
  if straight.sum() < round(20.0 / dt):
    return {"identifiable": False, "reason": "less than 20 seconds of clean straight driving"}

  residual = a["actual_la"] - a["desired_la"]
  flips = _threshold_sign_flips(a["applied_torque"], straight, 0.02)
  error_flips = _threshold_sign_flips(residual, straight, 0.03)

  nfft = max(256, round(10.24 / dt))
  nfft = 1 << int(math.floor(math.log2(nfft)))
  spectra: list[np.ndarray] = []
  start = 0
  while start < len(straight):
    if not straight[start]:
      start += 1
      continue
    end = start + 1
    while end < len(straight) and straight[end] and a["segment"][end] == a["segment"][end - 1]:
      end += 1
    for chunk_start in range(start, end - nfft + 1, nfft // 2):
      chunk = residual[chunk_start:chunk_start + nfft]
      chunk = chunk - np.mean(chunk)
      spectra.append(np.abs(np.fft.rfft(chunk * np.hanning(nfft))) ** 2)
    start = end

  dominant_frequency = math.nan
  band_fraction = math.nan
  if spectra:
    power = np.mean(spectra, axis=0)
    frequencies = np.fft.rfftfreq(nfft, dt)
    band = (frequencies >= 0.15) & (frequencies <= 2.0)
    if np.any(band):
      dominant_frequency = float(frequencies[band][np.argmax(power[band])])
      total = float(np.sum(power[1:]))
      band_fraction = float(np.sum(power[band]) / total) if total > 0 else math.nan

  return {
    "identifiable": True,
    "clean_straight_seconds": straight.sum() * dt,
    "torque_sign_flips_per_min": flips / duration_min,
    "tracking_error_sign_flips_per_min": error_flips / duration_min,
    "tracking_error_rms": float(np.sqrt(np.mean(residual[straight] ** 2))),
    "dominant_error_frequency_hz": dominant_frequency,
    "error_power_fraction_0p15_to_2hz": band_fraction,
  }


def summarize_route(data: RouteData) -> dict[str, Any]:
  a = data.arrays()
  if len(a["t"]) == 0:
    return {"route": data.route, "metadata": data.metadata, "samples": 0, "error": "no torque-controller samples"}
  dt = _sample_dt(a)
  base = clean_mask(a)
  with_lanes = clean_mask(a, include_lane_changes=True)
  live_summary = {}
  for field in ("live_steer_ratio", "live_stiffness", "live_delay", "angle_offset", "roll"):
    valid = np.isfinite(a[field])
    if np.any(valid):
      live_summary[field] = {
        "median": float(np.median(a[field][valid])),
        "p05": float(np.percentile(a[field][valid], 5)),
        "p95": float(np.percentile(a[field][valid], 95)),
      }

  return {
    "route": data.route,
    "metadata": data.metadata,
    "samples": len(a["t"]),
    "sample_dt_s": dt,
    "clean_identification_seconds": base.sum() * dt,
    "driver_override_seconds": (a["lat_active"] & a["steering_pressed"]).sum() * dt,
    "saturated_seconds": (a["lat_active"] & a["saturated"]).sum() * dt,
    "tracking": tracking_contexts(a, base),
    "lane_change_tracking": tracking_stats(a, with_lanes & a["lane_change"]),
    "desired_to_measured_delay": estimate_tracking_delay(a, base, dt),
    "torque_to_motion_delay": estimate_torque_to_motion_delay(a, base, dt),
    "torque_map": fit_torque_map(a, base),
    "torque_utilization": torque_utilization_metrics(a),
    "angle_rate_quality": angle_rate_quality_metrics(a, base, dt),
    "realization_integrator": realization_integrator_metrics(a, dt),
    "oscillation": oscillation_metrics(a, base, dt),
    "lane_geometry": lane_geometry_metrics(a, base, _finite_float(data.metadata.get("vehicle_width"))),
    "lane_dynamics": lane_dynamics_metrics(a, base, dt),
    "live_parameters": live_summary,
  }


def _print_summary(summary: dict[str, Any]) -> None:
  metadata = summary["metadata"]
  print(f"\n=== {summary['route']} ===")
  print(
    f"commit={metadata.get('git_commit', '')[:12]} branch={metadata.get('git_branch', '')} "
    f"car={metadata.get('car_fingerprint', '')} segments={metadata.get('segments', 0)} samples={summary['samples']}"
  )
  if "error" in summary:
    print(summary["error"])
    return
  print(
    f"configured steerRatio={metadata.get('steer_ratio', math.nan):.4f} "
    f"delay={metadata.get('actuator_delay', math.nan):.3f} "
    f"latAccelFactor={metadata.get('lat_accel_factor', math.nan):.4f} "
    f"friction={metadata.get('friction', math.nan):.4f}"
  )
  print(
    f"clean={summary['clean_identification_seconds']:.1f}s "
    f"driver_override={summary['driver_override_seconds']:.1f}s saturated={summary['saturated_seconds']:.1f}s"
  )
  for name, stats in summary["tracking"].items():
    if stats.get("n", 0):
      print(
        f"tracking {name:12s} n={stats['n']:6d} mae={stats['mae']:.4f} bias={stats['bias']:+.4f} "
        f"p95={stats['p95_abs']:.4f} gain={stats['gain_through_origin']:.3f}"
      )
  print("desired_to_measured_delay", summary["desired_to_measured_delay"])
  print("torque_to_motion_delay   ", summary["torque_to_motion_delay"])
  print("torque_map               ", summary["torque_map"])
  print("torque_utilization       ", summary["torque_utilization"])
  print("angle_rate_quality       ", summary["angle_rate_quality"])
  print("realization_integrator   ", summary["realization_integrator"])
  print("oscillation              ", summary["oscillation"])
  print("lane_geometry            ", summary["lane_geometry"])
  print("lane_dynamics            ", summary["lane_dynamics"])
  print("live_parameters          ", summary["live_parameters"])


def main() -> None:
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument("routes", nargs="+", help="Comma route or segment identifiers")
  parser.add_argument("--max-segments", type=int, default=None, help="Limit each route for a quick audit")
  parser.add_argument("--cache-dir", type=Path, help="Cache parsed rlog samples as compressed NumPy files")
  parser.add_argument("--json-out", help="Write machine-readable summaries to this path")
  args = parser.parse_args()

  summaries = []
  for route in args.routes:
    try:
      route_cache = cache_path(args.cache_dir, route) if args.cache_dir is not None and args.max_segments is None else None
      if route_cache is not None and route_cache.exists():
        data = RouteData.load(route_cache)
      else:
        data = read_route(route, max_segments=args.max_segments)
        if route_cache is not None:
          data.save(route_cache)
      summary = summarize_route(data)
    except Exception as error:
      summary = {"route": route, "metadata": {}, "samples": 0, "error": f"{type(error).__name__}: {error}"}
    summaries.append(summary)
    _print_summary(summary)

  if args.json_out:
    with open(args.json_out, "w", encoding="utf-8") as output:
      json.dump(summaries, output, indent=2, allow_nan=True)


if __name__ == "__main__":
  main()
