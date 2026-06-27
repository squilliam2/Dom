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
void car_err_fun(double *nom_x, double *delta_x, double *out_9063299258885678089);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5249330638840185569);
void car_H_mod_fun(double *state, double *out_6730506552132857878);
void car_f_fun(double *state, double dt, double *out_4022133726006847666);
void car_F_fun(double *state, double dt, double *out_1291922867413743277);
void car_h_25(double *state, double *unused, double *out_7640527507174277193);
void car_H_25(double *state, double *unused, double *out_3207525902143366201);
void car_h_24(double *state, double *unused, double *out_7298880785486689687);
void car_H_24(double *state, double *unused, double *out_350399696658956935);
void car_h_30(double *state, double *unused, double *out_7182326145015715531);
void car_H_30(double *state, double *unused, double *out_689192943636117574);
void car_h_26(double *state, double *unused, double *out_2037436081900067994);
void car_H_26(double *state, double *unused, double *out_6949029221017422425);
void car_h_27(double *state, double *unused, double *out_6184030537079166109);
void car_H_27(double *state, double *unused, double *out_1534401127547825643);
void car_h_29(double *state, double *unused, double *out_783284627601866385);
void car_H_29(double *state, double *unused, double *out_178961599321725390);
void car_h_28(double *state, double *unused, double *out_1182357269418320464);
void car_H_28(double *state, double *unused, double *out_5261360616391255964);
void car_h_31(double *state, double *unused, double *out_3042951309714601982);
void car_H_31(double *state, double *unused, double *out_3176879940266405773);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}