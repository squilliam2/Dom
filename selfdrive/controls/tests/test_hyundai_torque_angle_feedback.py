import pytest

from openpilot.selfdrive.controls.lib.hyundai_torque_angle_feedback import (
  HyundaiTorqueAngleFeedback,
  SONATA_MAX_BACKCALC_STEP,
  SONATA_MAX_RATE_CORRECTION,
)


def test_rate_feedback_tracks_relative_angle_motion():
  feedback = HyundaiTorqueAngleFeedback(0.01)

  turn_in = feedback.rate_correction(0.4, 0.8, 0.2, 0.6, 20.0, False)
  unwind = feedback.rate_correction(-0.4, -0.8, -0.2, 0.6, 20.0, False)
  overshoot_brake = feedback.rate_correction(0.05, 0.0, 0.8, 0.6, 20.0, False)

  assert turn_in > 0.0
  assert unwind < 0.0
  assert overshoot_brake < 0.0
  assert abs(turn_in) <= SONATA_MAX_RATE_CORRECTION


def test_rate_feedback_is_bounded_and_gated():
  feedback = HyundaiTorqueAngleFeedback(0.01)

  assert feedback.rate_correction(1.0, 10.0, -10.0, 0.9, 20.0, False) == pytest.approx(SONATA_MAX_RATE_CORRECTION)
  assert feedback.rate_correction(1.0, 1.0, 0.0, 0.6, 2.0, False) == 0.0
  assert feedback.rate_correction(1.0, 1.0, 0.0, 0.6, 20.0, True) == 0.0


def test_rate_feedback_does_not_brake_far_from_target():
  feedback = HyundaiTorqueAngleFeedback(0.01)

  far_from_target = feedback.rate_correction(0.5, 0.1, 0.8, 0.6, 20.0, False)
  predicted_overshoot = feedback.rate_correction(0.05, 0.0, 0.8, 0.6, 20.0, False)

  assert far_from_target == 0.0
  assert predicted_overshoot < 0.0


def test_applied_torque_backcalculation_unwinds_unrealized_request():
  feedback = HyundaiTorqueAngleFeedback(0.01)
  lateral_accel_from_torque = lambda torque, _params: 2.0 * torque

  assert feedback.integrator_backcalculation(-0.4, lateral_accel_from_torque, None, 0.6, 0.35, False) == 0.0

  feedback.remember_requested_torque(0.8)
  correction = feedback.integrator_backcalculation(-0.4, lateral_accel_from_torque, None, 0.6, 0.35, False)
  expected = 0.01 / (0.6 / 0.35) * (0.8 - 1.6)
  assert correction == pytest.approx(expected)
  assert correction < 0.0


def test_applied_torque_backcalculation_is_bounded_and_resettable():
  feedback = HyundaiTorqueAngleFeedback(0.01)
  lateral_accel_from_torque = lambda torque, _params: torque
  feedback.remember_requested_torque(100.0)

  assert feedback.integrator_backcalculation(0.0, lateral_accel_from_torque, None, 0.1, 1.0, False) == -SONATA_MAX_BACKCALC_STEP
  assert feedback.integrator_backcalculation(0.0, lateral_accel_from_torque, None, 0.1, 1.0, True) == 0.0

  feedback.reset()
  assert feedback.integrator_backcalculation(0.0, lateral_accel_from_torque, None, 0.1, 1.0, False) == 0.0
