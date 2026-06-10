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
void car_err_fun(double *nom_x, double *delta_x, double *out_2890366190982855796);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1959709052486962483);
void car_H_mod_fun(double *state, double *out_6359487390859137765);
void car_f_fun(double *state, double dt, double *out_8640471225264056008);
void car_F_fun(double *state, double dt, double *out_7019142443099520017);
void car_h_25(double *state, double *unused, double *out_1253470904109969861);
void car_H_25(double *state, double *unused, double *out_7183564857665749011);
void car_h_24(double *state, double *unused, double *out_2962653407625604630);
void car_H_24(double *state, double *unused, double *out_5135958713882120408);
void car_h_30(double *state, double *unused, double *out_2100381110359636395);
void car_H_30(double *state, double *unused, double *out_4665231899158500384);
void car_h_26(double *state, double *unused, double *out_8346832167819809863);
void car_H_26(double *state, double *unused, double *out_7521675897169746381);
void car_h_27(double *state, double *unused, double *out_4290256955554302546);
void car_H_27(double *state, double *unused, double *out_6839995210958925295);
void car_h_29(double *state, double *unused, double *out_6695928353906360745);
void car_H_29(double *state, double *unused, double *out_4155000554844108200);
void car_h_28(double *state, double *unused, double *out_8173563278849107317);
void car_H_28(double *state, double *unused, double *out_9209344501795912842);
void car_h_31(double *state, double *unused, double *out_5517364322240381075);
void car_H_31(double *state, double *unused, double *out_6895467794936394905);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}