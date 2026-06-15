#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6990659364596708462);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1561026677999837058);
void pose_H_mod_fun(double *state, double *out_308647198819961252);
void pose_f_fun(double *state, double dt, double *out_7010110275742074957);
void pose_F_fun(double *state, double dt, double *out_321710036859700647);
void pose_h_4(double *state, double *unused, double *out_8984471206441981160);
void pose_H_4(double *state, double *unused, double *out_1511051527086335609);
void pose_h_10(double *state, double *unused, double *out_1160903693658888330);
void pose_H_10(double *state, double *unused, double *out_8626357209504260991);
void pose_h_13(double *state, double *unused, double *out_8776526610688936203);
void pose_H_13(double *state, double *unused, double *out_6099579681230365320);
void pose_h_14(double *state, double *unused, double *out_3918582584245710569);
void pose_H_14(double *state, double *unused, double *out_2452189329253148920);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}