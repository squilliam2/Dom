#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_9063299258885678089) {
   out_9063299258885678089[0] = delta_x[0] + nom_x[0];
   out_9063299258885678089[1] = delta_x[1] + nom_x[1];
   out_9063299258885678089[2] = delta_x[2] + nom_x[2];
   out_9063299258885678089[3] = delta_x[3] + nom_x[3];
   out_9063299258885678089[4] = delta_x[4] + nom_x[4];
   out_9063299258885678089[5] = delta_x[5] + nom_x[5];
   out_9063299258885678089[6] = delta_x[6] + nom_x[6];
   out_9063299258885678089[7] = delta_x[7] + nom_x[7];
   out_9063299258885678089[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5249330638840185569) {
   out_5249330638840185569[0] = -nom_x[0] + true_x[0];
   out_5249330638840185569[1] = -nom_x[1] + true_x[1];
   out_5249330638840185569[2] = -nom_x[2] + true_x[2];
   out_5249330638840185569[3] = -nom_x[3] + true_x[3];
   out_5249330638840185569[4] = -nom_x[4] + true_x[4];
   out_5249330638840185569[5] = -nom_x[5] + true_x[5];
   out_5249330638840185569[6] = -nom_x[6] + true_x[6];
   out_5249330638840185569[7] = -nom_x[7] + true_x[7];
   out_5249330638840185569[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6730506552132857878) {
   out_6730506552132857878[0] = 1.0;
   out_6730506552132857878[1] = 0.0;
   out_6730506552132857878[2] = 0.0;
   out_6730506552132857878[3] = 0.0;
   out_6730506552132857878[4] = 0.0;
   out_6730506552132857878[5] = 0.0;
   out_6730506552132857878[6] = 0.0;
   out_6730506552132857878[7] = 0.0;
   out_6730506552132857878[8] = 0.0;
   out_6730506552132857878[9] = 0.0;
   out_6730506552132857878[10] = 1.0;
   out_6730506552132857878[11] = 0.0;
   out_6730506552132857878[12] = 0.0;
   out_6730506552132857878[13] = 0.0;
   out_6730506552132857878[14] = 0.0;
   out_6730506552132857878[15] = 0.0;
   out_6730506552132857878[16] = 0.0;
   out_6730506552132857878[17] = 0.0;
   out_6730506552132857878[18] = 0.0;
   out_6730506552132857878[19] = 0.0;
   out_6730506552132857878[20] = 1.0;
   out_6730506552132857878[21] = 0.0;
   out_6730506552132857878[22] = 0.0;
   out_6730506552132857878[23] = 0.0;
   out_6730506552132857878[24] = 0.0;
   out_6730506552132857878[25] = 0.0;
   out_6730506552132857878[26] = 0.0;
   out_6730506552132857878[27] = 0.0;
   out_6730506552132857878[28] = 0.0;
   out_6730506552132857878[29] = 0.0;
   out_6730506552132857878[30] = 1.0;
   out_6730506552132857878[31] = 0.0;
   out_6730506552132857878[32] = 0.0;
   out_6730506552132857878[33] = 0.0;
   out_6730506552132857878[34] = 0.0;
   out_6730506552132857878[35] = 0.0;
   out_6730506552132857878[36] = 0.0;
   out_6730506552132857878[37] = 0.0;
   out_6730506552132857878[38] = 0.0;
   out_6730506552132857878[39] = 0.0;
   out_6730506552132857878[40] = 1.0;
   out_6730506552132857878[41] = 0.0;
   out_6730506552132857878[42] = 0.0;
   out_6730506552132857878[43] = 0.0;
   out_6730506552132857878[44] = 0.0;
   out_6730506552132857878[45] = 0.0;
   out_6730506552132857878[46] = 0.0;
   out_6730506552132857878[47] = 0.0;
   out_6730506552132857878[48] = 0.0;
   out_6730506552132857878[49] = 0.0;
   out_6730506552132857878[50] = 1.0;
   out_6730506552132857878[51] = 0.0;
   out_6730506552132857878[52] = 0.0;
   out_6730506552132857878[53] = 0.0;
   out_6730506552132857878[54] = 0.0;
   out_6730506552132857878[55] = 0.0;
   out_6730506552132857878[56] = 0.0;
   out_6730506552132857878[57] = 0.0;
   out_6730506552132857878[58] = 0.0;
   out_6730506552132857878[59] = 0.0;
   out_6730506552132857878[60] = 1.0;
   out_6730506552132857878[61] = 0.0;
   out_6730506552132857878[62] = 0.0;
   out_6730506552132857878[63] = 0.0;
   out_6730506552132857878[64] = 0.0;
   out_6730506552132857878[65] = 0.0;
   out_6730506552132857878[66] = 0.0;
   out_6730506552132857878[67] = 0.0;
   out_6730506552132857878[68] = 0.0;
   out_6730506552132857878[69] = 0.0;
   out_6730506552132857878[70] = 1.0;
   out_6730506552132857878[71] = 0.0;
   out_6730506552132857878[72] = 0.0;
   out_6730506552132857878[73] = 0.0;
   out_6730506552132857878[74] = 0.0;
   out_6730506552132857878[75] = 0.0;
   out_6730506552132857878[76] = 0.0;
   out_6730506552132857878[77] = 0.0;
   out_6730506552132857878[78] = 0.0;
   out_6730506552132857878[79] = 0.0;
   out_6730506552132857878[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4022133726006847666) {
   out_4022133726006847666[0] = state[0];
   out_4022133726006847666[1] = state[1];
   out_4022133726006847666[2] = state[2];
   out_4022133726006847666[3] = state[3];
   out_4022133726006847666[4] = state[4];
   out_4022133726006847666[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4022133726006847666[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4022133726006847666[7] = state[7];
   out_4022133726006847666[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1291922867413743277) {
   out_1291922867413743277[0] = 1;
   out_1291922867413743277[1] = 0;
   out_1291922867413743277[2] = 0;
   out_1291922867413743277[3] = 0;
   out_1291922867413743277[4] = 0;
   out_1291922867413743277[5] = 0;
   out_1291922867413743277[6] = 0;
   out_1291922867413743277[7] = 0;
   out_1291922867413743277[8] = 0;
   out_1291922867413743277[9] = 0;
   out_1291922867413743277[10] = 1;
   out_1291922867413743277[11] = 0;
   out_1291922867413743277[12] = 0;
   out_1291922867413743277[13] = 0;
   out_1291922867413743277[14] = 0;
   out_1291922867413743277[15] = 0;
   out_1291922867413743277[16] = 0;
   out_1291922867413743277[17] = 0;
   out_1291922867413743277[18] = 0;
   out_1291922867413743277[19] = 0;
   out_1291922867413743277[20] = 1;
   out_1291922867413743277[21] = 0;
   out_1291922867413743277[22] = 0;
   out_1291922867413743277[23] = 0;
   out_1291922867413743277[24] = 0;
   out_1291922867413743277[25] = 0;
   out_1291922867413743277[26] = 0;
   out_1291922867413743277[27] = 0;
   out_1291922867413743277[28] = 0;
   out_1291922867413743277[29] = 0;
   out_1291922867413743277[30] = 1;
   out_1291922867413743277[31] = 0;
   out_1291922867413743277[32] = 0;
   out_1291922867413743277[33] = 0;
   out_1291922867413743277[34] = 0;
   out_1291922867413743277[35] = 0;
   out_1291922867413743277[36] = 0;
   out_1291922867413743277[37] = 0;
   out_1291922867413743277[38] = 0;
   out_1291922867413743277[39] = 0;
   out_1291922867413743277[40] = 1;
   out_1291922867413743277[41] = 0;
   out_1291922867413743277[42] = 0;
   out_1291922867413743277[43] = 0;
   out_1291922867413743277[44] = 0;
   out_1291922867413743277[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1291922867413743277[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1291922867413743277[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1291922867413743277[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1291922867413743277[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1291922867413743277[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1291922867413743277[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1291922867413743277[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1291922867413743277[53] = -9.8100000000000005*dt;
   out_1291922867413743277[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1291922867413743277[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1291922867413743277[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1291922867413743277[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1291922867413743277[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1291922867413743277[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1291922867413743277[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1291922867413743277[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1291922867413743277[62] = 0;
   out_1291922867413743277[63] = 0;
   out_1291922867413743277[64] = 0;
   out_1291922867413743277[65] = 0;
   out_1291922867413743277[66] = 0;
   out_1291922867413743277[67] = 0;
   out_1291922867413743277[68] = 0;
   out_1291922867413743277[69] = 0;
   out_1291922867413743277[70] = 1;
   out_1291922867413743277[71] = 0;
   out_1291922867413743277[72] = 0;
   out_1291922867413743277[73] = 0;
   out_1291922867413743277[74] = 0;
   out_1291922867413743277[75] = 0;
   out_1291922867413743277[76] = 0;
   out_1291922867413743277[77] = 0;
   out_1291922867413743277[78] = 0;
   out_1291922867413743277[79] = 0;
   out_1291922867413743277[80] = 1;
}
void h_25(double *state, double *unused, double *out_7640527507174277193) {
   out_7640527507174277193[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3207525902143366201) {
   out_3207525902143366201[0] = 0;
   out_3207525902143366201[1] = 0;
   out_3207525902143366201[2] = 0;
   out_3207525902143366201[3] = 0;
   out_3207525902143366201[4] = 0;
   out_3207525902143366201[5] = 0;
   out_3207525902143366201[6] = 1;
   out_3207525902143366201[7] = 0;
   out_3207525902143366201[8] = 0;
}
void h_24(double *state, double *unused, double *out_7298880785486689687) {
   out_7298880785486689687[0] = state[4];
   out_7298880785486689687[1] = state[5];
}
void H_24(double *state, double *unused, double *out_350399696658956935) {
   out_350399696658956935[0] = 0;
   out_350399696658956935[1] = 0;
   out_350399696658956935[2] = 0;
   out_350399696658956935[3] = 0;
   out_350399696658956935[4] = 1;
   out_350399696658956935[5] = 0;
   out_350399696658956935[6] = 0;
   out_350399696658956935[7] = 0;
   out_350399696658956935[8] = 0;
   out_350399696658956935[9] = 0;
   out_350399696658956935[10] = 0;
   out_350399696658956935[11] = 0;
   out_350399696658956935[12] = 0;
   out_350399696658956935[13] = 0;
   out_350399696658956935[14] = 1;
   out_350399696658956935[15] = 0;
   out_350399696658956935[16] = 0;
   out_350399696658956935[17] = 0;
}
void h_30(double *state, double *unused, double *out_7182326145015715531) {
   out_7182326145015715531[0] = state[4];
}
void H_30(double *state, double *unused, double *out_689192943636117574) {
   out_689192943636117574[0] = 0;
   out_689192943636117574[1] = 0;
   out_689192943636117574[2] = 0;
   out_689192943636117574[3] = 0;
   out_689192943636117574[4] = 1;
   out_689192943636117574[5] = 0;
   out_689192943636117574[6] = 0;
   out_689192943636117574[7] = 0;
   out_689192943636117574[8] = 0;
}
void h_26(double *state, double *unused, double *out_2037436081900067994) {
   out_2037436081900067994[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6949029221017422425) {
   out_6949029221017422425[0] = 0;
   out_6949029221017422425[1] = 0;
   out_6949029221017422425[2] = 0;
   out_6949029221017422425[3] = 0;
   out_6949029221017422425[4] = 0;
   out_6949029221017422425[5] = 0;
   out_6949029221017422425[6] = 0;
   out_6949029221017422425[7] = 1;
   out_6949029221017422425[8] = 0;
}
void h_27(double *state, double *unused, double *out_6184030537079166109) {
   out_6184030537079166109[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1534401127547825643) {
   out_1534401127547825643[0] = 0;
   out_1534401127547825643[1] = 0;
   out_1534401127547825643[2] = 0;
   out_1534401127547825643[3] = 1;
   out_1534401127547825643[4] = 0;
   out_1534401127547825643[5] = 0;
   out_1534401127547825643[6] = 0;
   out_1534401127547825643[7] = 0;
   out_1534401127547825643[8] = 0;
}
void h_29(double *state, double *unused, double *out_783284627601866385) {
   out_783284627601866385[0] = state[1];
}
void H_29(double *state, double *unused, double *out_178961599321725390) {
   out_178961599321725390[0] = 0;
   out_178961599321725390[1] = 1;
   out_178961599321725390[2] = 0;
   out_178961599321725390[3] = 0;
   out_178961599321725390[4] = 0;
   out_178961599321725390[5] = 0;
   out_178961599321725390[6] = 0;
   out_178961599321725390[7] = 0;
   out_178961599321725390[8] = 0;
}
void h_28(double *state, double *unused, double *out_1182357269418320464) {
   out_1182357269418320464[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5261360616391255964) {
   out_5261360616391255964[0] = 1;
   out_5261360616391255964[1] = 0;
   out_5261360616391255964[2] = 0;
   out_5261360616391255964[3] = 0;
   out_5261360616391255964[4] = 0;
   out_5261360616391255964[5] = 0;
   out_5261360616391255964[6] = 0;
   out_5261360616391255964[7] = 0;
   out_5261360616391255964[8] = 0;
}
void h_31(double *state, double *unused, double *out_3042951309714601982) {
   out_3042951309714601982[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3176879940266405773) {
   out_3176879940266405773[0] = 0;
   out_3176879940266405773[1] = 0;
   out_3176879940266405773[2] = 0;
   out_3176879940266405773[3] = 0;
   out_3176879940266405773[4] = 0;
   out_3176879940266405773[5] = 0;
   out_3176879940266405773[6] = 0;
   out_3176879940266405773[7] = 0;
   out_3176879940266405773[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_9063299258885678089) {
  err_fun(nom_x, delta_x, out_9063299258885678089);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5249330638840185569) {
  inv_err_fun(nom_x, true_x, out_5249330638840185569);
}
void car_H_mod_fun(double *state, double *out_6730506552132857878) {
  H_mod_fun(state, out_6730506552132857878);
}
void car_f_fun(double *state, double dt, double *out_4022133726006847666) {
  f_fun(state,  dt, out_4022133726006847666);
}
void car_F_fun(double *state, double dt, double *out_1291922867413743277) {
  F_fun(state,  dt, out_1291922867413743277);
}
void car_h_25(double *state, double *unused, double *out_7640527507174277193) {
  h_25(state, unused, out_7640527507174277193);
}
void car_H_25(double *state, double *unused, double *out_3207525902143366201) {
  H_25(state, unused, out_3207525902143366201);
}
void car_h_24(double *state, double *unused, double *out_7298880785486689687) {
  h_24(state, unused, out_7298880785486689687);
}
void car_H_24(double *state, double *unused, double *out_350399696658956935) {
  H_24(state, unused, out_350399696658956935);
}
void car_h_30(double *state, double *unused, double *out_7182326145015715531) {
  h_30(state, unused, out_7182326145015715531);
}
void car_H_30(double *state, double *unused, double *out_689192943636117574) {
  H_30(state, unused, out_689192943636117574);
}
void car_h_26(double *state, double *unused, double *out_2037436081900067994) {
  h_26(state, unused, out_2037436081900067994);
}
void car_H_26(double *state, double *unused, double *out_6949029221017422425) {
  H_26(state, unused, out_6949029221017422425);
}
void car_h_27(double *state, double *unused, double *out_6184030537079166109) {
  h_27(state, unused, out_6184030537079166109);
}
void car_H_27(double *state, double *unused, double *out_1534401127547825643) {
  H_27(state, unused, out_1534401127547825643);
}
void car_h_29(double *state, double *unused, double *out_783284627601866385) {
  h_29(state, unused, out_783284627601866385);
}
void car_H_29(double *state, double *unused, double *out_178961599321725390) {
  H_29(state, unused, out_178961599321725390);
}
void car_h_28(double *state, double *unused, double *out_1182357269418320464) {
  h_28(state, unused, out_1182357269418320464);
}
void car_H_28(double *state, double *unused, double *out_5261360616391255964) {
  H_28(state, unused, out_5261360616391255964);
}
void car_h_31(double *state, double *unused, double *out_3042951309714601982) {
  h_31(state, unused, out_3042951309714601982);
}
void car_H_31(double *state, double *unused, double *out_3176879940266405773) {
  H_31(state, unused, out_3176879940266405773);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
