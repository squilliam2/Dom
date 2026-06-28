#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6408835186344628642);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4488020327469491521);
void pose_H_mod_fun(double *state, double *out_8565439984289443181);
void pose_f_fun(double *state, double dt, double *out_4570281413344882742);
void pose_F_fun(double *state, double dt, double *out_3886745905040610692);
void pose_h_4(double *state, double *unused, double *out_1874588168802752989);
void pose_H_4(double *state, double *unused, double *out_6745741258383146320);
void pose_h_10(double *state, double *unused, double *out_904127136794521345);
void pose_H_10(double *state, double *unused, double *out_138933893569938853);
void pose_h_13(double *state, double *unused, double *out_5867467314771514899);
void pose_H_13(double *state, double *unused, double *out_8488728989994072495);
void pose_h_14(double *state, double *unused, double *out_6345221351211143880);
void pose_H_14(double *state, double *unused, double *out_3662952826087774024);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}