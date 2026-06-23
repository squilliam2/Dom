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
void car_err_fun(double *nom_x, double *delta_x, double *out_1099503832950344155);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1857055699068035744);
void car_H_mod_fun(double *state, double *out_6364761287714699355);
void car_f_fun(double *state, double dt, double *out_8704640073878126620);
void car_F_fun(double *state, double dt, double *out_2231700017024740017);
void car_h_25(double *state, double *unused, double *out_4358124578925276600);
void car_H_25(double *state, double *unused, double *out_2841780637725207678);
void car_h_24(double *state, double *unused, double *out_8493679030338339311);
void car_H_24(double *state, double *unused, double *out_716144961077115458);
void car_h_30(double *state, double *unused, double *out_3523148071828772585);
void car_H_30(double *state, double *unused, double *out_4074909703766409077);
void car_h_26(double *state, double *unused, double *out_1478525195832073060);
void car_H_26(double *state, double *unused, double *out_6583283956599263902);
void car_h_27(double *state, double *unused, double *out_643548688735569045);
void car_H_27(double *state, double *unused, double *out_1900146391965984166);
void car_h_29(double *state, double *unused, double *out_4280998216989591395);
void car_H_29(double *state, double *unused, double *out_4585141048080801261);
void car_h_28(double *state, double *unused, double *out_8338420483271271720);
void car_H_28(double *state, double *unused, double *out_497257968988729313);
void car_h_31(double *state, double *unused, double *out_7305850569280761561);
void car_H_31(double *state, double *unused, double *out_2811134675848247250);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}