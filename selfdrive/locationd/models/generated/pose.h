#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5169544621376104769);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5560919447530739345);
void pose_H_mod_fun(double *state, double *out_8932661143090135832);
void pose_f_fun(double *state, double dt, double *out_3609843023403364566);
void pose_F_fun(double *state, double dt, double *out_8950799816554095649);
void pose_h_4(double *state, double *unused, double *out_7061694870208984097);
void pose_H_4(double *state, double *unused, double *out_4465290511533350274);
void pose_h_10(double *state, double *unused, double *out_10860459686481955);
void pose_H_10(double *state, double *unused, double *out_3271917644950253884);
void pose_h_13(double *state, double *unused, double *out_1178992313314753128);
void pose_H_13(double *state, double *unused, double *out_7677564336865683075);
void pose_h_14(double *state, double *unused, double *out_3940331790740833198);
void pose_H_14(double *state, double *unused, double *out_8428531367872834803);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}