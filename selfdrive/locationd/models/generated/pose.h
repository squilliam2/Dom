#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3370172615713873468);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3634672358247053874);
void pose_H_mod_fun(double *state, double *out_4326808709061064235);
void pose_f_fun(double *state, double dt, double *out_4276772873746558675);
void pose_F_fun(double *state, double dt, double *out_4500717382901464499);
void pose_h_4(double *state, double *unused, double *out_5593213153040418665);
void pose_H_4(double *state, double *unused, double *out_8098615918904971807);
void pose_h_10(double *state, double *unused, double *out_665779804057694470);
void pose_H_10(double *state, double *unused, double *out_1520950660944493368);
void pose_h_13(double *state, double *unused, double *out_1559309075612614656);
void pose_H_13(double *state, double *unused, double *out_8663217838586815911);
void pose_h_14(double *state, double *unused, double *out_3210315045012193153);
void pose_H_14(double *state, double *unused, double *out_5015827486609599511);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}