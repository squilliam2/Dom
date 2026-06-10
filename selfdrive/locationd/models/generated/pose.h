#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5925269994359157710);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5867765456190971358);
void pose_H_mod_fun(double *state, double *out_4243397435317467221);
void pose_f_fun(double *state, double dt, double *out_5333365637221194880);
void pose_F_fun(double *state, double dt, double *out_8848460606148442442);
void pose_h_4(double *state, double *unused, double *out_2926038800219696097);
void pose_H_4(double *state, double *unused, double *out_9050828253353003660);
void pose_h_10(double *state, double *unused, double *out_3754295376293318230);
void pose_H_10(double *state, double *unused, double *out_2912584995031240051);
void pose_h_13(double *state, double *unused, double *out_4089270074398195787);
void pose_H_13(double *state, double *unused, double *out_5838554428020670859);
void pose_h_14(double *state, double *unused, double *out_9176020735288104700);
void pose_H_14(double *state, double *unused, double *out_5087587397013519131);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}