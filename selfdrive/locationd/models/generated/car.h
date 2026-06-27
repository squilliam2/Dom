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
void car_err_fun(double *nom_x, double *delta_x, double *out_7469803269040701934);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5146487777305957172);
void car_H_mod_fun(double *state, double *out_6489034200722373172);
void car_f_fun(double *state, double dt, double *out_2115535381215445196);
void car_F_fun(double *state, double dt, double *out_697532477187400649);
void car_h_25(double *state, double *unused, double *out_5124614186779649716);
void car_H_25(double *state, double *unused, double *out_2704154025189864065);
void car_h_24(double *state, double *unused, double *out_2288772113706282518);
void car_H_24(double *state, double *unused, double *out_4876803624195363631);
void car_h_30(double *state, double *unused, double *out_3032926190730655359);
void car_H_30(double *state, double *unused, double *out_185821066682615438);
void car_h_26(double *state, double *unused, double *out_7090256083799836565);
void car_H_26(double *state, double *unused, double *out_600371944570936536);
void car_h_27(double *state, double *unused, double *out_6474868053290145758);
void car_H_27(double *state, double *unused, double *out_2037773004501327779);
void car_h_29(double *state, double *unused, double *out_8675656061811612194);
void car_H_29(double *state, double *unused, double *out_324410277631776746);
void car_h_28(double *state, double *unused, double *out_2417538160220964552);
void car_H_28(double *state, double *unused, double *out_4757988739437753828);
void car_h_31(double *state, double *unused, double *out_6551294660579550964);
void car_H_31(double *state, double *unused, double *out_2673508063312903637);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}