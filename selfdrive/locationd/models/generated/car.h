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
void car_err_fun(double *nom_x, double *delta_x, double *out_7681400738027994255);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5789638956557325357);
void car_H_mod_fun(double *state, double *out_770586316396255671);
void car_f_fun(double *state, double dt, double *out_5606339599600049351);
void car_F_fun(double *state, double dt, double *out_7025079641144486959);
void car_h_25(double *state, double *unused, double *out_4577152348291642136);
void car_H_25(double *state, double *unused, double *out_5674278141580920511);
void car_h_24(double *state, double *unused, double *out_2260271043136596652);
void car_H_24(double *state, double *unused, double *out_7498971649215618511);
void car_h_30(double *state, double *unused, double *out_715468871863140484);
void car_H_30(double *state, double *unused, double *out_8192611100088169138);
void car_h_26(double *state, double *unused, double *out_8710731789405934690);
void car_H_26(double *state, double *unused, double *out_1932774822706864287);
void car_h_27(double *state, double *unused, double *out_5953042931828939605);
void car_H_27(double *state, double *unused, double *out_6017847788287744227);
void car_h_29(double *state, double *unused, double *out_5677848869544433716);
void car_H_29(double *state, double *unused, double *out_8702842444402561322);
void car_h_28(double *state, double *unused, double *out_8557448252637637256);
void car_H_28(double *state, double *unused, double *out_3620443427333030748);
void car_h_31(double *state, double *unused, double *out_1336580678379106237);
void car_H_31(double *state, double *unused, double *out_1306566720473512811);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}