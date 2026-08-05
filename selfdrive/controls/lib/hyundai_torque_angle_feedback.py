import math

import numpy as np


# Median of the independently identifiable torque-to-steering-motion delays in
# the Sonata Hybrid rlogs (0.119 s, 0.180 s, and 0.249 s). The correction cap
# is just below the raw-data 99th percentile (0.129 m/s^2 with Kp=0.6), which
# rejects derivative outliers without changing normal feedback samples.
SONATA_RESPONSE_DELAY_S = 0.18
SONATA_MAX_RATE_CORRECTION = 0.12  # m/s^2
SONATA_RATE_BRAKE_ERROR_BAND = 0.12  # m/s^2
SONATA_MIN_FEEDBACK_SPEED = 3.0    # m/s
SONATA_FULL_FEEDBACK_SPEED = 8.0   # m/s
SONATA_MAX_BACKCALC_STEP = 0.006   # m/s^2 per control cycle


class HyundaiTorqueAngleFeedback:
  """Bounded angle-feedback additions for a torque-command steering interface.

  The EPS still receives torque only. Steering angle is converted to measured
  lateral acceleration by LatControlTorque, then this class uses its signed
  rate to add phase lead and uses realized actuator torque for anti-windup.
  """

  def __init__(self, dt: float):
    self.dt = dt
    self.last_requested_torque = 0.0
    self.request_valid = False

  def reset(self) -> None:
    self.last_requested_torque = 0.0
    self.request_valid = False

  @staticmethod
  def relative_rate(desired_lateral_accel_rate: float, measured_lateral_accel_rate: float) -> float:
    if not math.isfinite(desired_lateral_accel_rate) or not math.isfinite(measured_lateral_accel_rate):
      return 0.0
    return desired_lateral_accel_rate - measured_lateral_accel_rate

  def rate_correction(self, tracking_error: float, desired_lateral_accel_rate: float, measured_lateral_accel_rate: float,
                      proportional_gain: float, v_ego: float, steering_pressed: bool) -> float:
    if steering_pressed or not all(math.isfinite(value) for value in (tracking_error, proportional_gain, v_ego)):
      return 0.0

    speed_scale = float(np.interp(v_ego, [SONATA_MIN_FEEDBACK_SPEED, SONATA_FULL_FEEDBACK_SPEED], [0.0, 1.0]))
    # e(t + tau) ~= e(t) + tau * e_dot(t). Multiplying the predictive part by
    # Kp yields a conventional derivative term with Kd = Kp * tau.
    relative_rate = self.relative_rate(desired_lateral_accel_rate, measured_lateral_accel_rate)
    correction = proportional_gain * SONATA_RESPONSE_DELAY_S * relative_rate
    predicted_error = tracking_error + SONATA_RESPONSE_DELAY_S * relative_rate
    correction_opposes_error = correction * tracking_error < 0.0
    crosses_target = predicted_error * tracking_error <= 0.0
    near_target = abs(tracking_error) <= SONATA_RATE_BRAKE_ERROR_BAND
    if correction_opposes_error and not (crosses_target or near_target):
      correction = 0.0
    return float(np.clip(correction * speed_scale, -SONATA_MAX_RATE_CORRECTION, SONATA_MAX_RATE_CORRECTION))

  def integrator_backcalculation(self, applied_actuator_torque: float, lateral_accel_from_torque,
                                 torque_params, proportional_gain: float, integral_gain: float,
                                 steering_pressed: bool) -> float:
    if (not self.request_valid or steering_pressed or
        not all(math.isfinite(value) for value in (applied_actuator_torque, proportional_gain, integral_gain)) or
        proportional_gain <= 0.0 or integral_gain <= 0.0):
      return 0.0

    # LatControlTorque's internal torque sign is opposite CarControl.torque.
    realized_lateral_accel = float(lateral_accel_from_torque(-applied_actuator_torque, torque_params))
    requested_lateral_accel = float(lateral_accel_from_torque(self.last_requested_torque, torque_params))
    if not math.isfinite(realized_lateral_accel) or not math.isfinite(requested_lateral_accel):
      return 0.0

    # Tracking anti-windup: Tt = Kp / Ki. This drives the integral toward the
    # actuator-realizable command without changing panda or Hyundai limits.
    tracking_time = proportional_gain / integral_gain
    correction = self.dt / max(tracking_time, self.dt) * (realized_lateral_accel - requested_lateral_accel)
    return float(np.clip(correction, -SONATA_MAX_BACKCALC_STEP, SONATA_MAX_BACKCALC_STEP))

  def remember_requested_torque(self, requested_torque: float) -> None:
    if math.isfinite(requested_torque):
      self.last_requested_torque = requested_torque
      self.request_valid = True
    else:
      self.reset()
