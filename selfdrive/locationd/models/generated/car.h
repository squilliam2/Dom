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
void car_err_fun(double *nom_x, double *delta_x, double *out_2092251631667009235);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2300837471234553583);
void car_H_mod_fun(double *state, double *out_4027971756970364591);
void car_f_fun(double *state, double dt, double *out_6249326857146976875);
void car_F_fun(double *state, double dt, double *out_1875491097223459739);
void car_h_25(double *state, double *unused, double *out_5658454479721392301);
void car_H_25(double *state, double *unused, double *out_8931663582155029431);
void car_h_24(double *state, double *unused, double *out_8388151047956984123);
void car_H_24(double *state, double *unused, double *out_8535018277801169936);
void car_h_30(double *state, double *unused, double *out_2021004951467369951);
void car_H_30(double *state, double *unused, double *out_6996747533047273558);
void car_h_26(double *state, double *unused, double *out_853261150391228214);
void car_H_26(double *state, double *unused, double *out_5190160263280973207);
void car_h_27(double *state, double *unused, double *out_9074727769370462317);
void car_H_27(double *state, double *unused, double *out_9171510844847698469);
void car_h_29(double *state, double *unused, double *out_5628340221843964391);
void car_H_29(double *state, double *unused, double *out_6486516188732881374);
void car_h_28(double *state, double *unused, double *out_4073054501709616672);
void car_H_28(double *state, double *unused, double *out_6877828867907139668);
void car_h_31(double *state, double *unused, double *out_508659560249742002);
void car_H_31(double *state, double *unused, double *out_4563952161047621731);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}