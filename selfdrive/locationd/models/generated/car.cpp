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
void err_fun(double *nom_x, double *delta_x, double *out_7681400738027994255) {
   out_7681400738027994255[0] = delta_x[0] + nom_x[0];
   out_7681400738027994255[1] = delta_x[1] + nom_x[1];
   out_7681400738027994255[2] = delta_x[2] + nom_x[2];
   out_7681400738027994255[3] = delta_x[3] + nom_x[3];
   out_7681400738027994255[4] = delta_x[4] + nom_x[4];
   out_7681400738027994255[5] = delta_x[5] + nom_x[5];
   out_7681400738027994255[6] = delta_x[6] + nom_x[6];
   out_7681400738027994255[7] = delta_x[7] + nom_x[7];
   out_7681400738027994255[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5789638956557325357) {
   out_5789638956557325357[0] = -nom_x[0] + true_x[0];
   out_5789638956557325357[1] = -nom_x[1] + true_x[1];
   out_5789638956557325357[2] = -nom_x[2] + true_x[2];
   out_5789638956557325357[3] = -nom_x[3] + true_x[3];
   out_5789638956557325357[4] = -nom_x[4] + true_x[4];
   out_5789638956557325357[5] = -nom_x[5] + true_x[5];
   out_5789638956557325357[6] = -nom_x[6] + true_x[6];
   out_5789638956557325357[7] = -nom_x[7] + true_x[7];
   out_5789638956557325357[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_770586316396255671) {
   out_770586316396255671[0] = 1.0;
   out_770586316396255671[1] = 0.0;
   out_770586316396255671[2] = 0.0;
   out_770586316396255671[3] = 0.0;
   out_770586316396255671[4] = 0.0;
   out_770586316396255671[5] = 0.0;
   out_770586316396255671[6] = 0.0;
   out_770586316396255671[7] = 0.0;
   out_770586316396255671[8] = 0.0;
   out_770586316396255671[9] = 0.0;
   out_770586316396255671[10] = 1.0;
   out_770586316396255671[11] = 0.0;
   out_770586316396255671[12] = 0.0;
   out_770586316396255671[13] = 0.0;
   out_770586316396255671[14] = 0.0;
   out_770586316396255671[15] = 0.0;
   out_770586316396255671[16] = 0.0;
   out_770586316396255671[17] = 0.0;
   out_770586316396255671[18] = 0.0;
   out_770586316396255671[19] = 0.0;
   out_770586316396255671[20] = 1.0;
   out_770586316396255671[21] = 0.0;
   out_770586316396255671[22] = 0.0;
   out_770586316396255671[23] = 0.0;
   out_770586316396255671[24] = 0.0;
   out_770586316396255671[25] = 0.0;
   out_770586316396255671[26] = 0.0;
   out_770586316396255671[27] = 0.0;
   out_770586316396255671[28] = 0.0;
   out_770586316396255671[29] = 0.0;
   out_770586316396255671[30] = 1.0;
   out_770586316396255671[31] = 0.0;
   out_770586316396255671[32] = 0.0;
   out_770586316396255671[33] = 0.0;
   out_770586316396255671[34] = 0.0;
   out_770586316396255671[35] = 0.0;
   out_770586316396255671[36] = 0.0;
   out_770586316396255671[37] = 0.0;
   out_770586316396255671[38] = 0.0;
   out_770586316396255671[39] = 0.0;
   out_770586316396255671[40] = 1.0;
   out_770586316396255671[41] = 0.0;
   out_770586316396255671[42] = 0.0;
   out_770586316396255671[43] = 0.0;
   out_770586316396255671[44] = 0.0;
   out_770586316396255671[45] = 0.0;
   out_770586316396255671[46] = 0.0;
   out_770586316396255671[47] = 0.0;
   out_770586316396255671[48] = 0.0;
   out_770586316396255671[49] = 0.0;
   out_770586316396255671[50] = 1.0;
   out_770586316396255671[51] = 0.0;
   out_770586316396255671[52] = 0.0;
   out_770586316396255671[53] = 0.0;
   out_770586316396255671[54] = 0.0;
   out_770586316396255671[55] = 0.0;
   out_770586316396255671[56] = 0.0;
   out_770586316396255671[57] = 0.0;
   out_770586316396255671[58] = 0.0;
   out_770586316396255671[59] = 0.0;
   out_770586316396255671[60] = 1.0;
   out_770586316396255671[61] = 0.0;
   out_770586316396255671[62] = 0.0;
   out_770586316396255671[63] = 0.0;
   out_770586316396255671[64] = 0.0;
   out_770586316396255671[65] = 0.0;
   out_770586316396255671[66] = 0.0;
   out_770586316396255671[67] = 0.0;
   out_770586316396255671[68] = 0.0;
   out_770586316396255671[69] = 0.0;
   out_770586316396255671[70] = 1.0;
   out_770586316396255671[71] = 0.0;
   out_770586316396255671[72] = 0.0;
   out_770586316396255671[73] = 0.0;
   out_770586316396255671[74] = 0.0;
   out_770586316396255671[75] = 0.0;
   out_770586316396255671[76] = 0.0;
   out_770586316396255671[77] = 0.0;
   out_770586316396255671[78] = 0.0;
   out_770586316396255671[79] = 0.0;
   out_770586316396255671[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5606339599600049351) {
   out_5606339599600049351[0] = state[0];
   out_5606339599600049351[1] = state[1];
   out_5606339599600049351[2] = state[2];
   out_5606339599600049351[3] = state[3];
   out_5606339599600049351[4] = state[4];
   out_5606339599600049351[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5606339599600049351[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5606339599600049351[7] = state[7];
   out_5606339599600049351[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7025079641144486959) {
   out_7025079641144486959[0] = 1;
   out_7025079641144486959[1] = 0;
   out_7025079641144486959[2] = 0;
   out_7025079641144486959[3] = 0;
   out_7025079641144486959[4] = 0;
   out_7025079641144486959[5] = 0;
   out_7025079641144486959[6] = 0;
   out_7025079641144486959[7] = 0;
   out_7025079641144486959[8] = 0;
   out_7025079641144486959[9] = 0;
   out_7025079641144486959[10] = 1;
   out_7025079641144486959[11] = 0;
   out_7025079641144486959[12] = 0;
   out_7025079641144486959[13] = 0;
   out_7025079641144486959[14] = 0;
   out_7025079641144486959[15] = 0;
   out_7025079641144486959[16] = 0;
   out_7025079641144486959[17] = 0;
   out_7025079641144486959[18] = 0;
   out_7025079641144486959[19] = 0;
   out_7025079641144486959[20] = 1;
   out_7025079641144486959[21] = 0;
   out_7025079641144486959[22] = 0;
   out_7025079641144486959[23] = 0;
   out_7025079641144486959[24] = 0;
   out_7025079641144486959[25] = 0;
   out_7025079641144486959[26] = 0;
   out_7025079641144486959[27] = 0;
   out_7025079641144486959[28] = 0;
   out_7025079641144486959[29] = 0;
   out_7025079641144486959[30] = 1;
   out_7025079641144486959[31] = 0;
   out_7025079641144486959[32] = 0;
   out_7025079641144486959[33] = 0;
   out_7025079641144486959[34] = 0;
   out_7025079641144486959[35] = 0;
   out_7025079641144486959[36] = 0;
   out_7025079641144486959[37] = 0;
   out_7025079641144486959[38] = 0;
   out_7025079641144486959[39] = 0;
   out_7025079641144486959[40] = 1;
   out_7025079641144486959[41] = 0;
   out_7025079641144486959[42] = 0;
   out_7025079641144486959[43] = 0;
   out_7025079641144486959[44] = 0;
   out_7025079641144486959[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7025079641144486959[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7025079641144486959[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7025079641144486959[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7025079641144486959[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7025079641144486959[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7025079641144486959[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7025079641144486959[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7025079641144486959[53] = -9.8100000000000005*dt;
   out_7025079641144486959[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7025079641144486959[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7025079641144486959[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7025079641144486959[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7025079641144486959[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7025079641144486959[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7025079641144486959[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7025079641144486959[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7025079641144486959[62] = 0;
   out_7025079641144486959[63] = 0;
   out_7025079641144486959[64] = 0;
   out_7025079641144486959[65] = 0;
   out_7025079641144486959[66] = 0;
   out_7025079641144486959[67] = 0;
   out_7025079641144486959[68] = 0;
   out_7025079641144486959[69] = 0;
   out_7025079641144486959[70] = 1;
   out_7025079641144486959[71] = 0;
   out_7025079641144486959[72] = 0;
   out_7025079641144486959[73] = 0;
   out_7025079641144486959[74] = 0;
   out_7025079641144486959[75] = 0;
   out_7025079641144486959[76] = 0;
   out_7025079641144486959[77] = 0;
   out_7025079641144486959[78] = 0;
   out_7025079641144486959[79] = 0;
   out_7025079641144486959[80] = 1;
}
void h_25(double *state, double *unused, double *out_4577152348291642136) {
   out_4577152348291642136[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5674278141580920511) {
   out_5674278141580920511[0] = 0;
   out_5674278141580920511[1] = 0;
   out_5674278141580920511[2] = 0;
   out_5674278141580920511[3] = 0;
   out_5674278141580920511[4] = 0;
   out_5674278141580920511[5] = 0;
   out_5674278141580920511[6] = 1;
   out_5674278141580920511[7] = 0;
   out_5674278141580920511[8] = 0;
}
void h_24(double *state, double *unused, double *out_2260271043136596652) {
   out_2260271043136596652[0] = state[4];
   out_2260271043136596652[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7498971649215618511) {
   out_7498971649215618511[0] = 0;
   out_7498971649215618511[1] = 0;
   out_7498971649215618511[2] = 0;
   out_7498971649215618511[3] = 0;
   out_7498971649215618511[4] = 1;
   out_7498971649215618511[5] = 0;
   out_7498971649215618511[6] = 0;
   out_7498971649215618511[7] = 0;
   out_7498971649215618511[8] = 0;
   out_7498971649215618511[9] = 0;
   out_7498971649215618511[10] = 0;
   out_7498971649215618511[11] = 0;
   out_7498971649215618511[12] = 0;
   out_7498971649215618511[13] = 0;
   out_7498971649215618511[14] = 1;
   out_7498971649215618511[15] = 0;
   out_7498971649215618511[16] = 0;
   out_7498971649215618511[17] = 0;
}
void h_30(double *state, double *unused, double *out_715468871863140484) {
   out_715468871863140484[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8192611100088169138) {
   out_8192611100088169138[0] = 0;
   out_8192611100088169138[1] = 0;
   out_8192611100088169138[2] = 0;
   out_8192611100088169138[3] = 0;
   out_8192611100088169138[4] = 1;
   out_8192611100088169138[5] = 0;
   out_8192611100088169138[6] = 0;
   out_8192611100088169138[7] = 0;
   out_8192611100088169138[8] = 0;
}
void h_26(double *state, double *unused, double *out_8710731789405934690) {
   out_8710731789405934690[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1932774822706864287) {
   out_1932774822706864287[0] = 0;
   out_1932774822706864287[1] = 0;
   out_1932774822706864287[2] = 0;
   out_1932774822706864287[3] = 0;
   out_1932774822706864287[4] = 0;
   out_1932774822706864287[5] = 0;
   out_1932774822706864287[6] = 0;
   out_1932774822706864287[7] = 1;
   out_1932774822706864287[8] = 0;
}
void h_27(double *state, double *unused, double *out_5953042931828939605) {
   out_5953042931828939605[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6017847788287744227) {
   out_6017847788287744227[0] = 0;
   out_6017847788287744227[1] = 0;
   out_6017847788287744227[2] = 0;
   out_6017847788287744227[3] = 1;
   out_6017847788287744227[4] = 0;
   out_6017847788287744227[5] = 0;
   out_6017847788287744227[6] = 0;
   out_6017847788287744227[7] = 0;
   out_6017847788287744227[8] = 0;
}
void h_29(double *state, double *unused, double *out_5677848869544433716) {
   out_5677848869544433716[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8702842444402561322) {
   out_8702842444402561322[0] = 0;
   out_8702842444402561322[1] = 1;
   out_8702842444402561322[2] = 0;
   out_8702842444402561322[3] = 0;
   out_8702842444402561322[4] = 0;
   out_8702842444402561322[5] = 0;
   out_8702842444402561322[6] = 0;
   out_8702842444402561322[7] = 0;
   out_8702842444402561322[8] = 0;
}
void h_28(double *state, double *unused, double *out_8557448252637637256) {
   out_8557448252637637256[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3620443427333030748) {
   out_3620443427333030748[0] = 1;
   out_3620443427333030748[1] = 0;
   out_3620443427333030748[2] = 0;
   out_3620443427333030748[3] = 0;
   out_3620443427333030748[4] = 0;
   out_3620443427333030748[5] = 0;
   out_3620443427333030748[6] = 0;
   out_3620443427333030748[7] = 0;
   out_3620443427333030748[8] = 0;
}
void h_31(double *state, double *unused, double *out_1336580678379106237) {
   out_1336580678379106237[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1306566720473512811) {
   out_1306566720473512811[0] = 0;
   out_1306566720473512811[1] = 0;
   out_1306566720473512811[2] = 0;
   out_1306566720473512811[3] = 0;
   out_1306566720473512811[4] = 0;
   out_1306566720473512811[5] = 0;
   out_1306566720473512811[6] = 0;
   out_1306566720473512811[7] = 0;
   out_1306566720473512811[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7681400738027994255) {
  err_fun(nom_x, delta_x, out_7681400738027994255);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5789638956557325357) {
  inv_err_fun(nom_x, true_x, out_5789638956557325357);
}
void car_H_mod_fun(double *state, double *out_770586316396255671) {
  H_mod_fun(state, out_770586316396255671);
}
void car_f_fun(double *state, double dt, double *out_5606339599600049351) {
  f_fun(state,  dt, out_5606339599600049351);
}
void car_F_fun(double *state, double dt, double *out_7025079641144486959) {
  F_fun(state,  dt, out_7025079641144486959);
}
void car_h_25(double *state, double *unused, double *out_4577152348291642136) {
  h_25(state, unused, out_4577152348291642136);
}
void car_H_25(double *state, double *unused, double *out_5674278141580920511) {
  H_25(state, unused, out_5674278141580920511);
}
void car_h_24(double *state, double *unused, double *out_2260271043136596652) {
  h_24(state, unused, out_2260271043136596652);
}
void car_H_24(double *state, double *unused, double *out_7498971649215618511) {
  H_24(state, unused, out_7498971649215618511);
}
void car_h_30(double *state, double *unused, double *out_715468871863140484) {
  h_30(state, unused, out_715468871863140484);
}
void car_H_30(double *state, double *unused, double *out_8192611100088169138) {
  H_30(state, unused, out_8192611100088169138);
}
void car_h_26(double *state, double *unused, double *out_8710731789405934690) {
  h_26(state, unused, out_8710731789405934690);
}
void car_H_26(double *state, double *unused, double *out_1932774822706864287) {
  H_26(state, unused, out_1932774822706864287);
}
void car_h_27(double *state, double *unused, double *out_5953042931828939605) {
  h_27(state, unused, out_5953042931828939605);
}
void car_H_27(double *state, double *unused, double *out_6017847788287744227) {
  H_27(state, unused, out_6017847788287744227);
}
void car_h_29(double *state, double *unused, double *out_5677848869544433716) {
  h_29(state, unused, out_5677848869544433716);
}
void car_H_29(double *state, double *unused, double *out_8702842444402561322) {
  H_29(state, unused, out_8702842444402561322);
}
void car_h_28(double *state, double *unused, double *out_8557448252637637256) {
  h_28(state, unused, out_8557448252637637256);
}
void car_H_28(double *state, double *unused, double *out_3620443427333030748) {
  H_28(state, unused, out_3620443427333030748);
}
void car_h_31(double *state, double *unused, double *out_1336580678379106237) {
  h_31(state, unused, out_1336580678379106237);
}
void car_H_31(double *state, double *unused, double *out_1306566720473512811) {
  H_31(state, unused, out_1306566720473512811);
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
