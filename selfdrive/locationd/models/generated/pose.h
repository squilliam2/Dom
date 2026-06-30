#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7150506142011136089);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4307514453378045812);
void pose_H_mod_fun(double *state, double *out_526209948270695177);
void pose_f_fun(double *state, double dt, double *out_826153410981652937);
void pose_F_fun(double *state, double dt, double *out_2504584572758712159);
void pose_h_4(double *state, double *unused, double *out_7442480903303367172);
void pose_H_4(double *state, double *unused, double *out_3800432027061644430);
void pose_h_10(double *state, double *unused, double *out_8932011361837519248);
void pose_H_10(double *state, double *unused, double *out_4464178208942290131);
void pose_h_13(double *state, double *unused, double *out_6459110219088517442);
void pose_H_13(double *state, double *unused, double *out_588158201729311629);
void pose_h_14(double *state, double *unused, double *out_7025019117935111535);
void pose_H_14(double *state, double *unused, double *out_162808829277840099);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}