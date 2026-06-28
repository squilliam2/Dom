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
void car_err_fun(double *nom_x, double *delta_x, double *out_4213074370852160810);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4007900572103243439);
void car_H_mod_fun(double *state, double *out_8824637158619611629);
void car_f_fun(double *state, double dt, double *out_7248181046558172931);
void car_F_fun(double *state, double dt, double *out_1901673215728667839);
void car_h_25(double *state, double *unused, double *out_141170775012007602);
void car_H_25(double *state, double *unused, double *out_4718415089905275147);
void car_h_24(double *state, double *unused, double *out_6127458511898671622);
void car_H_24(double *state, double *unused, double *out_2541200666298125174);
void car_h_30(double *state, double *unused, double *out_4296825053779108162);
void car_H_30(double *state, double *unused, double *out_2200082131398026520);
void car_h_26(double *state, double *unused, double *out_5968496148460696103);
void car_H_26(double *state, double *unused, double *out_8459918408779331371);
void car_h_27(double *state, double *unused, double *out_4860502492648838043);
void car_H_27(double *state, double *unused, double *out_7025869341876243360);
void car_h_29(double *state, double *unused, double *out_1910332733701512893);
void car_H_29(double *state, double *unused, double *out_8735880075718491161);
void car_h_28(double *state, double *unused, double *out_4414832447712484906);
void car_H_28(double *state, double *unused, double *out_6772249804153164910);
void car_h_31(double *state, double *unused, double *out_1309460617616875565);
void car_H_31(double *state, double *unused, double *out_9086126511012682847);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}