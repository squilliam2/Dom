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
void car_err_fun(double *nom_x, double *delta_x, double *out_92735882134146519);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3460935513230882787);
void car_H_mod_fun(double *state, double *out_1422739628250006049);
void car_f_fun(double *state, double dt, double *out_1170289062789918948);
void car_F_fun(double *state, double dt, double *out_3493049086978441612);
void car_h_25(double *state, double *unused, double *out_7013925099015375635);
void car_H_25(double *state, double *unused, double *out_4945720278239497726);
void car_h_24(double *state, double *unused, double *out_1176701170289761958);
void car_H_24(double *state, double *unused, double *out_199210951272988692);
void car_h_30(double *state, double *unused, double *out_3376475570761353285);
void car_H_30(double *state, double *unused, double *out_6584333453978437135);
void car_h_26(double *state, double *unused, double *out_6352431583079506005);
void car_H_26(double *state, double *unused, double *out_1204216959365441502);
void car_h_27(double *state, double *unused, double *out_8181668900091517372);
void car_H_27(double *state, double *unused, double *out_8759096765778862046);
void car_h_29(double *state, double *unused, double *out_1625197696899492360);
void car_H_29(double *state, double *unused, double *out_7974284581061138537);
void car_h_28(double *state, double *unused, double *out_7452523070348180861);
void car_H_28(double *state, double *unused, double *out_2891885563991607963);
void car_h_31(double *state, double *unused, double *out_5836194589039397969);
void car_H_31(double *state, double *unused, double *out_4976366240116458154);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}