#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_2541993810890450617);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4007732744251149414);
void car_H_mod_fun(double *state, double *out_6685865118100003284);
void car_f_fun(double *state, double dt, double *out_6974049569071864212);
void car_F_fun(double *state, double dt, double *out_7385013454295441423);
void car_h_25(double *state, double *unused, double *out_8051554989951709251);
void car_H_25(double *state, double *unused, double *out_2507323107812233953);
void car_h_24(double *state, double *unused, double *out_3112249856335132889);
void car_H_24(double *state, double *unused, double *out_4679972706817733519);
void car_h_30(double *state, double *unused, double *out_432221354858015888);
void car_H_30(double *state, double *unused, double *out_11009850695014674);
void car_h_26(double *state, double *unused, double *out_8837878174502242541);
void car_H_26(double *state, double *unused, double *out_6248826426686290177);
void car_h_27(double *state, double *unused, double *out_5014768938507376566);
void car_H_27(double *state, double *unused, double *out_2234603921878957891);
void car_h_29(double *state, double *unused, double *out_5550702484448125865);
void car_H_29(double *state, double *unused, double *out_521241195009406858);
void car_h_28(double *state, double *unused, double *out_8430301867541329405);
void car_H_28(double *state, double *unused, double *out_4561157822060123716);
void car_h_31(double *state, double *unused, double *out_3624353857407491429);
void car_H_31(double *state, double *unused, double *out_6875034528919641653);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}