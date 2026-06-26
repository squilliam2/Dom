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
void err_fun(double *nom_x, double *delta_x, double *out_2541993810890450617) {
   out_2541993810890450617[0] = delta_x[0] + nom_x[0];
   out_2541993810890450617[1] = delta_x[1] + nom_x[1];
   out_2541993810890450617[2] = delta_x[2] + nom_x[2];
   out_2541993810890450617[3] = delta_x[3] + nom_x[3];
   out_2541993810890450617[4] = delta_x[4] + nom_x[4];
   out_2541993810890450617[5] = delta_x[5] + nom_x[5];
   out_2541993810890450617[6] = delta_x[6] + nom_x[6];
   out_2541993810890450617[7] = delta_x[7] + nom_x[7];
   out_2541993810890450617[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4007732744251149414) {
   out_4007732744251149414[0] = -nom_x[0] + true_x[0];
   out_4007732744251149414[1] = -nom_x[1] + true_x[1];
   out_4007732744251149414[2] = -nom_x[2] + true_x[2];
   out_4007732744251149414[3] = -nom_x[3] + true_x[3];
   out_4007732744251149414[4] = -nom_x[4] + true_x[4];
   out_4007732744251149414[5] = -nom_x[5] + true_x[5];
   out_4007732744251149414[6] = -nom_x[6] + true_x[6];
   out_4007732744251149414[7] = -nom_x[7] + true_x[7];
   out_4007732744251149414[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6685865118100003284) {
   out_6685865118100003284[0] = 1.0;
   out_6685865118100003284[1] = 0.0;
   out_6685865118100003284[2] = 0.0;
   out_6685865118100003284[3] = 0.0;
   out_6685865118100003284[4] = 0.0;
   out_6685865118100003284[5] = 0.0;
   out_6685865118100003284[6] = 0.0;
   out_6685865118100003284[7] = 0.0;
   out_6685865118100003284[8] = 0.0;
   out_6685865118100003284[9] = 0.0;
   out_6685865118100003284[10] = 1.0;
   out_6685865118100003284[11] = 0.0;
   out_6685865118100003284[12] = 0.0;
   out_6685865118100003284[13] = 0.0;
   out_6685865118100003284[14] = 0.0;
   out_6685865118100003284[15] = 0.0;
   out_6685865118100003284[16] = 0.0;
   out_6685865118100003284[17] = 0.0;
   out_6685865118100003284[18] = 0.0;
   out_6685865118100003284[19] = 0.0;
   out_6685865118100003284[20] = 1.0;
   out_6685865118100003284[21] = 0.0;
   out_6685865118100003284[22] = 0.0;
   out_6685865118100003284[23] = 0.0;
   out_6685865118100003284[24] = 0.0;
   out_6685865118100003284[25] = 0.0;
   out_6685865118100003284[26] = 0.0;
   out_6685865118100003284[27] = 0.0;
   out_6685865118100003284[28] = 0.0;
   out_6685865118100003284[29] = 0.0;
   out_6685865118100003284[30] = 1.0;
   out_6685865118100003284[31] = 0.0;
   out_6685865118100003284[32] = 0.0;
   out_6685865118100003284[33] = 0.0;
   out_6685865118100003284[34] = 0.0;
   out_6685865118100003284[35] = 0.0;
   out_6685865118100003284[36] = 0.0;
   out_6685865118100003284[37] = 0.0;
   out_6685865118100003284[38] = 0.0;
   out_6685865118100003284[39] = 0.0;
   out_6685865118100003284[40] = 1.0;
   out_6685865118100003284[41] = 0.0;
   out_6685865118100003284[42] = 0.0;
   out_6685865118100003284[43] = 0.0;
   out_6685865118100003284[44] = 0.0;
   out_6685865118100003284[45] = 0.0;
   out_6685865118100003284[46] = 0.0;
   out_6685865118100003284[47] = 0.0;
   out_6685865118100003284[48] = 0.0;
   out_6685865118100003284[49] = 0.0;
   out_6685865118100003284[50] = 1.0;
   out_6685865118100003284[51] = 0.0;
   out_6685865118100003284[52] = 0.0;
   out_6685865118100003284[53] = 0.0;
   out_6685865118100003284[54] = 0.0;
   out_6685865118100003284[55] = 0.0;
   out_6685865118100003284[56] = 0.0;
   out_6685865118100003284[57] = 0.0;
   out_6685865118100003284[58] = 0.0;
   out_6685865118100003284[59] = 0.0;
   out_6685865118100003284[60] = 1.0;
   out_6685865118100003284[61] = 0.0;
   out_6685865118100003284[62] = 0.0;
   out_6685865118100003284[63] = 0.0;
   out_6685865118100003284[64] = 0.0;
   out_6685865118100003284[65] = 0.0;
   out_6685865118100003284[66] = 0.0;
   out_6685865118100003284[67] = 0.0;
   out_6685865118100003284[68] = 0.0;
   out_6685865118100003284[69] = 0.0;
   out_6685865118100003284[70] = 1.0;
   out_6685865118100003284[71] = 0.0;
   out_6685865118100003284[72] = 0.0;
   out_6685865118100003284[73] = 0.0;
   out_6685865118100003284[74] = 0.0;
   out_6685865118100003284[75] = 0.0;
   out_6685865118100003284[76] = 0.0;
   out_6685865118100003284[77] = 0.0;
   out_6685865118100003284[78] = 0.0;
   out_6685865118100003284[79] = 0.0;
   out_6685865118100003284[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6974049569071864212) {
   out_6974049569071864212[0] = state[0];
   out_6974049569071864212[1] = state[1];
   out_6974049569071864212[2] = state[2];
   out_6974049569071864212[3] = state[3];
   out_6974049569071864212[4] = state[4];
   out_6974049569071864212[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6974049569071864212[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6974049569071864212[7] = state[7];
   out_6974049569071864212[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7385013454295441423) {
   out_7385013454295441423[0] = 1;
   out_7385013454295441423[1] = 0;
   out_7385013454295441423[2] = 0;
   out_7385013454295441423[3] = 0;
   out_7385013454295441423[4] = 0;
   out_7385013454295441423[5] = 0;
   out_7385013454295441423[6] = 0;
   out_7385013454295441423[7] = 0;
   out_7385013454295441423[8] = 0;
   out_7385013454295441423[9] = 0;
   out_7385013454295441423[10] = 1;
   out_7385013454295441423[11] = 0;
   out_7385013454295441423[12] = 0;
   out_7385013454295441423[13] = 0;
   out_7385013454295441423[14] = 0;
   out_7385013454295441423[15] = 0;
   out_7385013454295441423[16] = 0;
   out_7385013454295441423[17] = 0;
   out_7385013454295441423[18] = 0;
   out_7385013454295441423[19] = 0;
   out_7385013454295441423[20] = 1;
   out_7385013454295441423[21] = 0;
   out_7385013454295441423[22] = 0;
   out_7385013454295441423[23] = 0;
   out_7385013454295441423[24] = 0;
   out_7385013454295441423[25] = 0;
   out_7385013454295441423[26] = 0;
   out_7385013454295441423[27] = 0;
   out_7385013454295441423[28] = 0;
   out_7385013454295441423[29] = 0;
   out_7385013454295441423[30] = 1;
   out_7385013454295441423[31] = 0;
   out_7385013454295441423[32] = 0;
   out_7385013454295441423[33] = 0;
   out_7385013454295441423[34] = 0;
   out_7385013454295441423[35] = 0;
   out_7385013454295441423[36] = 0;
   out_7385013454295441423[37] = 0;
   out_7385013454295441423[38] = 0;
   out_7385013454295441423[39] = 0;
   out_7385013454295441423[40] = 1;
   out_7385013454295441423[41] = 0;
   out_7385013454295441423[42] = 0;
   out_7385013454295441423[43] = 0;
   out_7385013454295441423[44] = 0;
   out_7385013454295441423[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7385013454295441423[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7385013454295441423[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7385013454295441423[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7385013454295441423[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7385013454295441423[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7385013454295441423[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7385013454295441423[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7385013454295441423[53] = -9.8100000000000005*dt;
   out_7385013454295441423[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7385013454295441423[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7385013454295441423[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7385013454295441423[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7385013454295441423[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7385013454295441423[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7385013454295441423[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7385013454295441423[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7385013454295441423[62] = 0;
   out_7385013454295441423[63] = 0;
   out_7385013454295441423[64] = 0;
   out_7385013454295441423[65] = 0;
   out_7385013454295441423[66] = 0;
   out_7385013454295441423[67] = 0;
   out_7385013454295441423[68] = 0;
   out_7385013454295441423[69] = 0;
   out_7385013454295441423[70] = 1;
   out_7385013454295441423[71] = 0;
   out_7385013454295441423[72] = 0;
   out_7385013454295441423[73] = 0;
   out_7385013454295441423[74] = 0;
   out_7385013454295441423[75] = 0;
   out_7385013454295441423[76] = 0;
   out_7385013454295441423[77] = 0;
   out_7385013454295441423[78] = 0;
   out_7385013454295441423[79] = 0;
   out_7385013454295441423[80] = 1;
}
void h_25(double *state, double *unused, double *out_8051554989951709251) {
   out_8051554989951709251[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2507323107812233953) {
   out_2507323107812233953[0] = 0;
   out_2507323107812233953[1] = 0;
   out_2507323107812233953[2] = 0;
   out_2507323107812233953[3] = 0;
   out_2507323107812233953[4] = 0;
   out_2507323107812233953[5] = 0;
   out_2507323107812233953[6] = 1;
   out_2507323107812233953[7] = 0;
   out_2507323107812233953[8] = 0;
}
void h_24(double *state, double *unused, double *out_3112249856335132889) {
   out_3112249856335132889[0] = state[4];
   out_3112249856335132889[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4679972706817733519) {
   out_4679972706817733519[0] = 0;
   out_4679972706817733519[1] = 0;
   out_4679972706817733519[2] = 0;
   out_4679972706817733519[3] = 0;
   out_4679972706817733519[4] = 1;
   out_4679972706817733519[5] = 0;
   out_4679972706817733519[6] = 0;
   out_4679972706817733519[7] = 0;
   out_4679972706817733519[8] = 0;
   out_4679972706817733519[9] = 0;
   out_4679972706817733519[10] = 0;
   out_4679972706817733519[11] = 0;
   out_4679972706817733519[12] = 0;
   out_4679972706817733519[13] = 0;
   out_4679972706817733519[14] = 1;
   out_4679972706817733519[15] = 0;
   out_4679972706817733519[16] = 0;
   out_4679972706817733519[17] = 0;
}
void h_30(double *state, double *unused, double *out_432221354858015888) {
   out_432221354858015888[0] = state[4];
}
void H_30(double *state, double *unused, double *out_11009850695014674) {
   out_11009850695014674[0] = 0;
   out_11009850695014674[1] = 0;
   out_11009850695014674[2] = 0;
   out_11009850695014674[3] = 0;
   out_11009850695014674[4] = 1;
   out_11009850695014674[5] = 0;
   out_11009850695014674[6] = 0;
   out_11009850695014674[7] = 0;
   out_11009850695014674[8] = 0;
}
void h_26(double *state, double *unused, double *out_8837878174502242541) {
   out_8837878174502242541[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6248826426686290177) {
   out_6248826426686290177[0] = 0;
   out_6248826426686290177[1] = 0;
   out_6248826426686290177[2] = 0;
   out_6248826426686290177[3] = 0;
   out_6248826426686290177[4] = 0;
   out_6248826426686290177[5] = 0;
   out_6248826426686290177[6] = 0;
   out_6248826426686290177[7] = 1;
   out_6248826426686290177[8] = 0;
}
void h_27(double *state, double *unused, double *out_5014768938507376566) {
   out_5014768938507376566[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2234603921878957891) {
   out_2234603921878957891[0] = 0;
   out_2234603921878957891[1] = 0;
   out_2234603921878957891[2] = 0;
   out_2234603921878957891[3] = 1;
   out_2234603921878957891[4] = 0;
   out_2234603921878957891[5] = 0;
   out_2234603921878957891[6] = 0;
   out_2234603921878957891[7] = 0;
   out_2234603921878957891[8] = 0;
}
void h_29(double *state, double *unused, double *out_5550702484448125865) {
   out_5550702484448125865[0] = state[1];
}
void H_29(double *state, double *unused, double *out_521241195009406858) {
   out_521241195009406858[0] = 0;
   out_521241195009406858[1] = 1;
   out_521241195009406858[2] = 0;
   out_521241195009406858[3] = 0;
   out_521241195009406858[4] = 0;
   out_521241195009406858[5] = 0;
   out_521241195009406858[6] = 0;
   out_521241195009406858[7] = 0;
   out_521241195009406858[8] = 0;
}
void h_28(double *state, double *unused, double *out_8430301867541329405) {
   out_8430301867541329405[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4561157822060123716) {
   out_4561157822060123716[0] = 1;
   out_4561157822060123716[1] = 0;
   out_4561157822060123716[2] = 0;
   out_4561157822060123716[3] = 0;
   out_4561157822060123716[4] = 0;
   out_4561157822060123716[5] = 0;
   out_4561157822060123716[6] = 0;
   out_4561157822060123716[7] = 0;
   out_4561157822060123716[8] = 0;
}
void h_31(double *state, double *unused, double *out_3624353857407491429) {
   out_3624353857407491429[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6875034528919641653) {
   out_6875034528919641653[0] = 0;
   out_6875034528919641653[1] = 0;
   out_6875034528919641653[2] = 0;
   out_6875034528919641653[3] = 0;
   out_6875034528919641653[4] = 0;
   out_6875034528919641653[5] = 0;
   out_6875034528919641653[6] = 0;
   out_6875034528919641653[7] = 0;
   out_6875034528919641653[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2541993810890450617) {
  err_fun(nom_x, delta_x, out_2541993810890450617);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4007732744251149414) {
  inv_err_fun(nom_x, true_x, out_4007732744251149414);
}
void car_H_mod_fun(double *state, double *out_6685865118100003284) {
  H_mod_fun(state, out_6685865118100003284);
}
void car_f_fun(double *state, double dt, double *out_6974049569071864212) {
  f_fun(state,  dt, out_6974049569071864212);
}
void car_F_fun(double *state, double dt, double *out_7385013454295441423) {
  F_fun(state,  dt, out_7385013454295441423);
}
void car_h_25(double *state, double *unused, double *out_8051554989951709251) {
  h_25(state, unused, out_8051554989951709251);
}
void car_H_25(double *state, double *unused, double *out_2507323107812233953) {
  H_25(state, unused, out_2507323107812233953);
}
void car_h_24(double *state, double *unused, double *out_3112249856335132889) {
  h_24(state, unused, out_3112249856335132889);
}
void car_H_24(double *state, double *unused, double *out_4679972706817733519) {
  H_24(state, unused, out_4679972706817733519);
}
void car_h_30(double *state, double *unused, double *out_432221354858015888) {
  h_30(state, unused, out_432221354858015888);
}
void car_H_30(double *state, double *unused, double *out_11009850695014674) {
  H_30(state, unused, out_11009850695014674);
}
void car_h_26(double *state, double *unused, double *out_8837878174502242541) {
  h_26(state, unused, out_8837878174502242541);
}
void car_H_26(double *state, double *unused, double *out_6248826426686290177) {
  H_26(state, unused, out_6248826426686290177);
}
void car_h_27(double *state, double *unused, double *out_5014768938507376566) {
  h_27(state, unused, out_5014768938507376566);
}
void car_H_27(double *state, double *unused, double *out_2234603921878957891) {
  H_27(state, unused, out_2234603921878957891);
}
void car_h_29(double *state, double *unused, double *out_5550702484448125865) {
  h_29(state, unused, out_5550702484448125865);
}
void car_H_29(double *state, double *unused, double *out_521241195009406858) {
  H_29(state, unused, out_521241195009406858);
}
void car_h_28(double *state, double *unused, double *out_8430301867541329405) {
  h_28(state, unused, out_8430301867541329405);
}
void car_H_28(double *state, double *unused, double *out_4561157822060123716) {
  H_28(state, unused, out_4561157822060123716);
}
void car_h_31(double *state, double *unused, double *out_3624353857407491429) {
  h_31(state, unused, out_3624353857407491429);
}
void car_H_31(double *state, double *unused, double *out_6875034528919641653) {
  H_31(state, unused, out_6875034528919641653);
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
