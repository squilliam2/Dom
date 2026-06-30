#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_287802830867790833);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1374850324761980275);
void car_H_mod_fun(double *state, double *out_6646352482882938111);
void car_f_fun(double *state, double dt, double *out_2311726086880249539);
void car_F_fun(double *state, double dt, double *out_1431608970589135594);
void car_h_25(double *state, double *unused, double *out_4297991490361286945);
void car_H_25(double *state, double *unused, double *out_7005560747898744396);
void car_h_24(double *state, double *unused, double *out_806466490562007731);
void car_H_24(double *state, double *unused, double *out_4832911148893244830);
void car_h_30(double *state, double *unused, double *out_7377917356997913735);
void car_H_30(double *state, double *unused, double *out_8922850367303558593);
void car_h_26(double *state, double *unused, double *out_5726959480825607318);
void car_H_26(double *state, double *unused, double *out_3264057429024688172);
void car_h_27(double *state, double *unused, double *out_703681777299558700);
void car_H_27(double *state, double *unused, double *out_7349130394605568112);
void car_h_29(double *state, double *unused, double *out_4341131305553581050);
void car_H_29(double *state, double *unused, double *out_8412619022989166409);
void car_h_28(double *state, double *unused, double *out_8946752832143995776);
void car_H_28(double *state, double *unused, double *out_4951726033650854633);
void car_h_31(double *state, double *unused, double *out_3465273766459385496);
void car_H_31(double *state, double *unused, double *out_2637849326791336696);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}