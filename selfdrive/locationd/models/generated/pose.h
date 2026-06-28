#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3697966966174848325);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6121892126530152725);
void pose_H_mod_fun(double *state, double *out_1116503706765055069);
void pose_f_fun(double *state, double dt, double *out_2317659772838150308);
void pose_F_fun(double *state, double dt, double *out_6164130103148092652);
void pose_h_4(double *state, double *unused, double *out_2811574505702470007);
void pose_H_4(double *state, double *unused, double *out_8385878700886675205);
void pose_h_10(double *state, double *unused, double *out_5534858922172779190);
void pose_H_10(double *state, double *unused, double *out_3607384786905077425);
void pose_h_13(double *state, double *unused, double *out_7690213453916874753);
void pose_H_13(double *state, double *unused, double *out_6848591547490543610);
void pose_h_14(double *state, double *unused, double *out_1351222622664013473);
void pose_H_14(double *state, double *unused, double *out_5303090268591302909);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}