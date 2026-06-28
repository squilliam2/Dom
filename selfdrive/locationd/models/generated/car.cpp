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
void err_fun(double *nom_x, double *delta_x, double *out_4213074370852160810) {
   out_4213074370852160810[0] = delta_x[0] + nom_x[0];
   out_4213074370852160810[1] = delta_x[1] + nom_x[1];
   out_4213074370852160810[2] = delta_x[2] + nom_x[2];
   out_4213074370852160810[3] = delta_x[3] + nom_x[3];
   out_4213074370852160810[4] = delta_x[4] + nom_x[4];
   out_4213074370852160810[5] = delta_x[5] + nom_x[5];
   out_4213074370852160810[6] = delta_x[6] + nom_x[6];
   out_4213074370852160810[7] = delta_x[7] + nom_x[7];
   out_4213074370852160810[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4007900572103243439) {
   out_4007900572103243439[0] = -nom_x[0] + true_x[0];
   out_4007900572103243439[1] = -nom_x[1] + true_x[1];
   out_4007900572103243439[2] = -nom_x[2] + true_x[2];
   out_4007900572103243439[3] = -nom_x[3] + true_x[3];
   out_4007900572103243439[4] = -nom_x[4] + true_x[4];
   out_4007900572103243439[5] = -nom_x[5] + true_x[5];
   out_4007900572103243439[6] = -nom_x[6] + true_x[6];
   out_4007900572103243439[7] = -nom_x[7] + true_x[7];
   out_4007900572103243439[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8824637158619611629) {
   out_8824637158619611629[0] = 1.0;
   out_8824637158619611629[1] = 0.0;
   out_8824637158619611629[2] = 0.0;
   out_8824637158619611629[3] = 0.0;
   out_8824637158619611629[4] = 0.0;
   out_8824637158619611629[5] = 0.0;
   out_8824637158619611629[6] = 0.0;
   out_8824637158619611629[7] = 0.0;
   out_8824637158619611629[8] = 0.0;
   out_8824637158619611629[9] = 0.0;
   out_8824637158619611629[10] = 1.0;
   out_8824637158619611629[11] = 0.0;
   out_8824637158619611629[12] = 0.0;
   out_8824637158619611629[13] = 0.0;
   out_8824637158619611629[14] = 0.0;
   out_8824637158619611629[15] = 0.0;
   out_8824637158619611629[16] = 0.0;
   out_8824637158619611629[17] = 0.0;
   out_8824637158619611629[18] = 0.0;
   out_8824637158619611629[19] = 0.0;
   out_8824637158619611629[20] = 1.0;
   out_8824637158619611629[21] = 0.0;
   out_8824637158619611629[22] = 0.0;
   out_8824637158619611629[23] = 0.0;
   out_8824637158619611629[24] = 0.0;
   out_8824637158619611629[25] = 0.0;
   out_8824637158619611629[26] = 0.0;
   out_8824637158619611629[27] = 0.0;
   out_8824637158619611629[28] = 0.0;
   out_8824637158619611629[29] = 0.0;
   out_8824637158619611629[30] = 1.0;
   out_8824637158619611629[31] = 0.0;
   out_8824637158619611629[32] = 0.0;
   out_8824637158619611629[33] = 0.0;
   out_8824637158619611629[34] = 0.0;
   out_8824637158619611629[35] = 0.0;
   out_8824637158619611629[36] = 0.0;
   out_8824637158619611629[37] = 0.0;
   out_8824637158619611629[38] = 0.0;
   out_8824637158619611629[39] = 0.0;
   out_8824637158619611629[40] = 1.0;
   out_8824637158619611629[41] = 0.0;
   out_8824637158619611629[42] = 0.0;
   out_8824637158619611629[43] = 0.0;
   out_8824637158619611629[44] = 0.0;
   out_8824637158619611629[45] = 0.0;
   out_8824637158619611629[46] = 0.0;
   out_8824637158619611629[47] = 0.0;
   out_8824637158619611629[48] = 0.0;
   out_8824637158619611629[49] = 0.0;
   out_8824637158619611629[50] = 1.0;
   out_8824637158619611629[51] = 0.0;
   out_8824637158619611629[52] = 0.0;
   out_8824637158619611629[53] = 0.0;
   out_8824637158619611629[54] = 0.0;
   out_8824637158619611629[55] = 0.0;
   out_8824637158619611629[56] = 0.0;
   out_8824637158619611629[57] = 0.0;
   out_8824637158619611629[58] = 0.0;
   out_8824637158619611629[59] = 0.0;
   out_8824637158619611629[60] = 1.0;
   out_8824637158619611629[61] = 0.0;
   out_8824637158619611629[62] = 0.0;
   out_8824637158619611629[63] = 0.0;
   out_8824637158619611629[64] = 0.0;
   out_8824637158619611629[65] = 0.0;
   out_8824637158619611629[66] = 0.0;
   out_8824637158619611629[67] = 0.0;
   out_8824637158619611629[68] = 0.0;
   out_8824637158619611629[69] = 0.0;
   out_8824637158619611629[70] = 1.0;
   out_8824637158619611629[71] = 0.0;
   out_8824637158619611629[72] = 0.0;
   out_8824637158619611629[73] = 0.0;
   out_8824637158619611629[74] = 0.0;
   out_8824637158619611629[75] = 0.0;
   out_8824637158619611629[76] = 0.0;
   out_8824637158619611629[77] = 0.0;
   out_8824637158619611629[78] = 0.0;
   out_8824637158619611629[79] = 0.0;
   out_8824637158619611629[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7248181046558172931) {
   out_7248181046558172931[0] = state[0];
   out_7248181046558172931[1] = state[1];
   out_7248181046558172931[2] = state[2];
   out_7248181046558172931[3] = state[3];
   out_7248181046558172931[4] = state[4];
   out_7248181046558172931[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7248181046558172931[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7248181046558172931[7] = state[7];
   out_7248181046558172931[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1901673215728667839) {
   out_1901673215728667839[0] = 1;
   out_1901673215728667839[1] = 0;
   out_1901673215728667839[2] = 0;
   out_1901673215728667839[3] = 0;
   out_1901673215728667839[4] = 0;
   out_1901673215728667839[5] = 0;
   out_1901673215728667839[6] = 0;
   out_1901673215728667839[7] = 0;
   out_1901673215728667839[8] = 0;
   out_1901673215728667839[9] = 0;
   out_1901673215728667839[10] = 1;
   out_1901673215728667839[11] = 0;
   out_1901673215728667839[12] = 0;
   out_1901673215728667839[13] = 0;
   out_1901673215728667839[14] = 0;
   out_1901673215728667839[15] = 0;
   out_1901673215728667839[16] = 0;
   out_1901673215728667839[17] = 0;
   out_1901673215728667839[18] = 0;
   out_1901673215728667839[19] = 0;
   out_1901673215728667839[20] = 1;
   out_1901673215728667839[21] = 0;
   out_1901673215728667839[22] = 0;
   out_1901673215728667839[23] = 0;
   out_1901673215728667839[24] = 0;
   out_1901673215728667839[25] = 0;
   out_1901673215728667839[26] = 0;
   out_1901673215728667839[27] = 0;
   out_1901673215728667839[28] = 0;
   out_1901673215728667839[29] = 0;
   out_1901673215728667839[30] = 1;
   out_1901673215728667839[31] = 0;
   out_1901673215728667839[32] = 0;
   out_1901673215728667839[33] = 0;
   out_1901673215728667839[34] = 0;
   out_1901673215728667839[35] = 0;
   out_1901673215728667839[36] = 0;
   out_1901673215728667839[37] = 0;
   out_1901673215728667839[38] = 0;
   out_1901673215728667839[39] = 0;
   out_1901673215728667839[40] = 1;
   out_1901673215728667839[41] = 0;
   out_1901673215728667839[42] = 0;
   out_1901673215728667839[43] = 0;
   out_1901673215728667839[44] = 0;
   out_1901673215728667839[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1901673215728667839[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1901673215728667839[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1901673215728667839[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1901673215728667839[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1901673215728667839[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1901673215728667839[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1901673215728667839[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1901673215728667839[53] = -9.8100000000000005*dt;
   out_1901673215728667839[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1901673215728667839[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1901673215728667839[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1901673215728667839[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1901673215728667839[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1901673215728667839[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1901673215728667839[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1901673215728667839[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1901673215728667839[62] = 0;
   out_1901673215728667839[63] = 0;
   out_1901673215728667839[64] = 0;
   out_1901673215728667839[65] = 0;
   out_1901673215728667839[66] = 0;
   out_1901673215728667839[67] = 0;
   out_1901673215728667839[68] = 0;
   out_1901673215728667839[69] = 0;
   out_1901673215728667839[70] = 1;
   out_1901673215728667839[71] = 0;
   out_1901673215728667839[72] = 0;
   out_1901673215728667839[73] = 0;
   out_1901673215728667839[74] = 0;
   out_1901673215728667839[75] = 0;
   out_1901673215728667839[76] = 0;
   out_1901673215728667839[77] = 0;
   out_1901673215728667839[78] = 0;
   out_1901673215728667839[79] = 0;
   out_1901673215728667839[80] = 1;
}
void h_25(double *state, double *unused, double *out_141170775012007602) {
   out_141170775012007602[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4718415089905275147) {
   out_4718415089905275147[0] = 0;
   out_4718415089905275147[1] = 0;
   out_4718415089905275147[2] = 0;
   out_4718415089905275147[3] = 0;
   out_4718415089905275147[4] = 0;
   out_4718415089905275147[5] = 0;
   out_4718415089905275147[6] = 1;
   out_4718415089905275147[7] = 0;
   out_4718415089905275147[8] = 0;
}
void h_24(double *state, double *unused, double *out_6127458511898671622) {
   out_6127458511898671622[0] = state[4];
   out_6127458511898671622[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2541200666298125174) {
   out_2541200666298125174[0] = 0;
   out_2541200666298125174[1] = 0;
   out_2541200666298125174[2] = 0;
   out_2541200666298125174[3] = 0;
   out_2541200666298125174[4] = 1;
   out_2541200666298125174[5] = 0;
   out_2541200666298125174[6] = 0;
   out_2541200666298125174[7] = 0;
   out_2541200666298125174[8] = 0;
   out_2541200666298125174[9] = 0;
   out_2541200666298125174[10] = 0;
   out_2541200666298125174[11] = 0;
   out_2541200666298125174[12] = 0;
   out_2541200666298125174[13] = 0;
   out_2541200666298125174[14] = 1;
   out_2541200666298125174[15] = 0;
   out_2541200666298125174[16] = 0;
   out_2541200666298125174[17] = 0;
}
void h_30(double *state, double *unused, double *out_4296825053779108162) {
   out_4296825053779108162[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2200082131398026520) {
   out_2200082131398026520[0] = 0;
   out_2200082131398026520[1] = 0;
   out_2200082131398026520[2] = 0;
   out_2200082131398026520[3] = 0;
   out_2200082131398026520[4] = 1;
   out_2200082131398026520[5] = 0;
   out_2200082131398026520[6] = 0;
   out_2200082131398026520[7] = 0;
   out_2200082131398026520[8] = 0;
}
void h_26(double *state, double *unused, double *out_5968496148460696103) {
   out_5968496148460696103[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8459918408779331371) {
   out_8459918408779331371[0] = 0;
   out_8459918408779331371[1] = 0;
   out_8459918408779331371[2] = 0;
   out_8459918408779331371[3] = 0;
   out_8459918408779331371[4] = 0;
   out_8459918408779331371[5] = 0;
   out_8459918408779331371[6] = 0;
   out_8459918408779331371[7] = 1;
   out_8459918408779331371[8] = 0;
}
void h_27(double *state, double *unused, double *out_4860502492648838043) {
   out_4860502492648838043[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7025869341876243360) {
   out_7025869341876243360[0] = 0;
   out_7025869341876243360[1] = 0;
   out_7025869341876243360[2] = 0;
   out_7025869341876243360[3] = 1;
   out_7025869341876243360[4] = 0;
   out_7025869341876243360[5] = 0;
   out_7025869341876243360[6] = 0;
   out_7025869341876243360[7] = 0;
   out_7025869341876243360[8] = 0;
}
void h_29(double *state, double *unused, double *out_1910332733701512893) {
   out_1910332733701512893[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8735880075718491161) {
   out_8735880075718491161[0] = 0;
   out_8735880075718491161[1] = 1;
   out_8735880075718491161[2] = 0;
   out_8735880075718491161[3] = 0;
   out_8735880075718491161[4] = 0;
   out_8735880075718491161[5] = 0;
   out_8735880075718491161[6] = 0;
   out_8735880075718491161[7] = 0;
   out_8735880075718491161[8] = 0;
}
void h_28(double *state, double *unused, double *out_4414832447712484906) {
   out_4414832447712484906[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6772249804153164910) {
   out_6772249804153164910[0] = 1;
   out_6772249804153164910[1] = 0;
   out_6772249804153164910[2] = 0;
   out_6772249804153164910[3] = 0;
   out_6772249804153164910[4] = 0;
   out_6772249804153164910[5] = 0;
   out_6772249804153164910[6] = 0;
   out_6772249804153164910[7] = 0;
   out_6772249804153164910[8] = 0;
}
void h_31(double *state, double *unused, double *out_1309460617616875565) {
   out_1309460617616875565[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9086126511012682847) {
   out_9086126511012682847[0] = 0;
   out_9086126511012682847[1] = 0;
   out_9086126511012682847[2] = 0;
   out_9086126511012682847[3] = 0;
   out_9086126511012682847[4] = 0;
   out_9086126511012682847[5] = 0;
   out_9086126511012682847[6] = 0;
   out_9086126511012682847[7] = 0;
   out_9086126511012682847[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4213074370852160810) {
  err_fun(nom_x, delta_x, out_4213074370852160810);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4007900572103243439) {
  inv_err_fun(nom_x, true_x, out_4007900572103243439);
}
void car_H_mod_fun(double *state, double *out_8824637158619611629) {
  H_mod_fun(state, out_8824637158619611629);
}
void car_f_fun(double *state, double dt, double *out_7248181046558172931) {
  f_fun(state,  dt, out_7248181046558172931);
}
void car_F_fun(double *state, double dt, double *out_1901673215728667839) {
  F_fun(state,  dt, out_1901673215728667839);
}
void car_h_25(double *state, double *unused, double *out_141170775012007602) {
  h_25(state, unused, out_141170775012007602);
}
void car_H_25(double *state, double *unused, double *out_4718415089905275147) {
  H_25(state, unused, out_4718415089905275147);
}
void car_h_24(double *state, double *unused, double *out_6127458511898671622) {
  h_24(state, unused, out_6127458511898671622);
}
void car_H_24(double *state, double *unused, double *out_2541200666298125174) {
  H_24(state, unused, out_2541200666298125174);
}
void car_h_30(double *state, double *unused, double *out_4296825053779108162) {
  h_30(state, unused, out_4296825053779108162);
}
void car_H_30(double *state, double *unused, double *out_2200082131398026520) {
  H_30(state, unused, out_2200082131398026520);
}
void car_h_26(double *state, double *unused, double *out_5968496148460696103) {
  h_26(state, unused, out_5968496148460696103);
}
void car_H_26(double *state, double *unused, double *out_8459918408779331371) {
  H_26(state, unused, out_8459918408779331371);
}
void car_h_27(double *state, double *unused, double *out_4860502492648838043) {
  h_27(state, unused, out_4860502492648838043);
}
void car_H_27(double *state, double *unused, double *out_7025869341876243360) {
  H_27(state, unused, out_7025869341876243360);
}
void car_h_29(double *state, double *unused, double *out_1910332733701512893) {
  h_29(state, unused, out_1910332733701512893);
}
void car_H_29(double *state, double *unused, double *out_8735880075718491161) {
  H_29(state, unused, out_8735880075718491161);
}
void car_h_28(double *state, double *unused, double *out_4414832447712484906) {
  h_28(state, unused, out_4414832447712484906);
}
void car_H_28(double *state, double *unused, double *out_6772249804153164910) {
  H_28(state, unused, out_6772249804153164910);
}
void car_h_31(double *state, double *unused, double *out_1309460617616875565) {
  h_31(state, unused, out_1309460617616875565);
}
void car_H_31(double *state, double *unused, double *out_9086126511012682847) {
  H_31(state, unused, out_9086126511012682847);
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
