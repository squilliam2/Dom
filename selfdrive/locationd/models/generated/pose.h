#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3190087603797747831);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_509645540564194226);
void pose_H_mod_fun(double *state, double *out_5916418097484803312);
void pose_f_fun(double *state, double dt, double *out_1884549682660320153);
void pose_F_fun(double *state, double dt, double *out_2096520336867054981);
void pose_h_4(double *state, double *unused, double *out_2454407190288685983);
void pose_H_4(double *state, double *unused, double *out_6670579099539515919);
void pose_h_10(double *state, double *unused, double *out_8369687601978266142);
void pose_H_10(double *state, double *unused, double *out_7187578973007118545);
void pose_h_13(double *state, double *unused, double *out_23418844804759200);
void pose_H_13(double *state, double *unused, double *out_4165533765853334768);
void pose_h_14(double *state, double *unused, double *out_3766794879461642001);
void pose_H_14(double *state, double *unused, double *out_7812924117830551168);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}