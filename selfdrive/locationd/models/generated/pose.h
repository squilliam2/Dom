#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2550502777521953992);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2991013798952875835);
void pose_H_mod_fun(double *state, double *out_3992538829710935120);
void pose_f_fun(double *state, double dt, double *out_8224128290291442758);
void pose_F_fun(double *state, double dt, double *out_4173313334813114557);
void pose_h_4(double *state, double *unused, double *out_8461717180408587044);
void pose_H_4(double *state, double *unused, double *out_2172840103804638259);
void pose_h_10(double *state, double *unused, double *out_2633265206766799101);
void pose_H_10(double *state, double *unused, double *out_3904041767468690216);
void pose_h_13(double *state, double *unused, double *out_3680645971147336893);
void pose_H_13(double *state, double *unused, double *out_5385113929136971060);
void pose_h_14(double *state, double *unused, double *out_5848550976228580590);
void pose_H_14(double *state, double *unused, double *out_909948328490734037);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}