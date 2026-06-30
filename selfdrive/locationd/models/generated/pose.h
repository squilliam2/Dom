#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1773490464841058211);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3370820179269337821);
void pose_H_mod_fun(double *state, double *out_8103172798179963867);
void pose_f_fun(double *state, double dt, double *out_4130745264458481066);
void pose_F_fun(double *state, double dt, double *out_8817991526926240656);
void pose_h_4(double *state, double *unused, double *out_7394028133800952799);
void pose_H_4(double *state, double *unused, double *out_6283474072273667006);
void pose_h_10(double *state, double *unused, double *out_1632777674839787006);
void pose_H_10(double *state, double *unused, double *out_761013637887660448);
void pose_h_13(double *state, double *unused, double *out_4603793361074312483);
void pose_H_13(double *state, double *unused, double *out_8950996176103551809);
void pose_h_14(double *state, double *unused, double *out_5241449068668224266);
void pose_H_14(double *state, double *unused, double *out_3200685639978294710);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}