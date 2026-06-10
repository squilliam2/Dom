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
void err_fun(double *nom_x, double *delta_x, double *out_2890366190982855796) {
   out_2890366190982855796[0] = delta_x[0] + nom_x[0];
   out_2890366190982855796[1] = delta_x[1] + nom_x[1];
   out_2890366190982855796[2] = delta_x[2] + nom_x[2];
   out_2890366190982855796[3] = delta_x[3] + nom_x[3];
   out_2890366190982855796[4] = delta_x[4] + nom_x[4];
   out_2890366190982855796[5] = delta_x[5] + nom_x[5];
   out_2890366190982855796[6] = delta_x[6] + nom_x[6];
   out_2890366190982855796[7] = delta_x[7] + nom_x[7];
   out_2890366190982855796[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1959709052486962483) {
   out_1959709052486962483[0] = -nom_x[0] + true_x[0];
   out_1959709052486962483[1] = -nom_x[1] + true_x[1];
   out_1959709052486962483[2] = -nom_x[2] + true_x[2];
   out_1959709052486962483[3] = -nom_x[3] + true_x[3];
   out_1959709052486962483[4] = -nom_x[4] + true_x[4];
   out_1959709052486962483[5] = -nom_x[5] + true_x[5];
   out_1959709052486962483[6] = -nom_x[6] + true_x[6];
   out_1959709052486962483[7] = -nom_x[7] + true_x[7];
   out_1959709052486962483[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6359487390859137765) {
   out_6359487390859137765[0] = 1.0;
   out_6359487390859137765[1] = 0.0;
   out_6359487390859137765[2] = 0.0;
   out_6359487390859137765[3] = 0.0;
   out_6359487390859137765[4] = 0.0;
   out_6359487390859137765[5] = 0.0;
   out_6359487390859137765[6] = 0.0;
   out_6359487390859137765[7] = 0.0;
   out_6359487390859137765[8] = 0.0;
   out_6359487390859137765[9] = 0.0;
   out_6359487390859137765[10] = 1.0;
   out_6359487390859137765[11] = 0.0;
   out_6359487390859137765[12] = 0.0;
   out_6359487390859137765[13] = 0.0;
   out_6359487390859137765[14] = 0.0;
   out_6359487390859137765[15] = 0.0;
   out_6359487390859137765[16] = 0.0;
   out_6359487390859137765[17] = 0.0;
   out_6359487390859137765[18] = 0.0;
   out_6359487390859137765[19] = 0.0;
   out_6359487390859137765[20] = 1.0;
   out_6359487390859137765[21] = 0.0;
   out_6359487390859137765[22] = 0.0;
   out_6359487390859137765[23] = 0.0;
   out_6359487390859137765[24] = 0.0;
   out_6359487390859137765[25] = 0.0;
   out_6359487390859137765[26] = 0.0;
   out_6359487390859137765[27] = 0.0;
   out_6359487390859137765[28] = 0.0;
   out_6359487390859137765[29] = 0.0;
   out_6359487390859137765[30] = 1.0;
   out_6359487390859137765[31] = 0.0;
   out_6359487390859137765[32] = 0.0;
   out_6359487390859137765[33] = 0.0;
   out_6359487390859137765[34] = 0.0;
   out_6359487390859137765[35] = 0.0;
   out_6359487390859137765[36] = 0.0;
   out_6359487390859137765[37] = 0.0;
   out_6359487390859137765[38] = 0.0;
   out_6359487390859137765[39] = 0.0;
   out_6359487390859137765[40] = 1.0;
   out_6359487390859137765[41] = 0.0;
   out_6359487390859137765[42] = 0.0;
   out_6359487390859137765[43] = 0.0;
   out_6359487390859137765[44] = 0.0;
   out_6359487390859137765[45] = 0.0;
   out_6359487390859137765[46] = 0.0;
   out_6359487390859137765[47] = 0.0;
   out_6359487390859137765[48] = 0.0;
   out_6359487390859137765[49] = 0.0;
   out_6359487390859137765[50] = 1.0;
   out_6359487390859137765[51] = 0.0;
   out_6359487390859137765[52] = 0.0;
   out_6359487390859137765[53] = 0.0;
   out_6359487390859137765[54] = 0.0;
   out_6359487390859137765[55] = 0.0;
   out_6359487390859137765[56] = 0.0;
   out_6359487390859137765[57] = 0.0;
   out_6359487390859137765[58] = 0.0;
   out_6359487390859137765[59] = 0.0;
   out_6359487390859137765[60] = 1.0;
   out_6359487390859137765[61] = 0.0;
   out_6359487390859137765[62] = 0.0;
   out_6359487390859137765[63] = 0.0;
   out_6359487390859137765[64] = 0.0;
   out_6359487390859137765[65] = 0.0;
   out_6359487390859137765[66] = 0.0;
   out_6359487390859137765[67] = 0.0;
   out_6359487390859137765[68] = 0.0;
   out_6359487390859137765[69] = 0.0;
   out_6359487390859137765[70] = 1.0;
   out_6359487390859137765[71] = 0.0;
   out_6359487390859137765[72] = 0.0;
   out_6359487390859137765[73] = 0.0;
   out_6359487390859137765[74] = 0.0;
   out_6359487390859137765[75] = 0.0;
   out_6359487390859137765[76] = 0.0;
   out_6359487390859137765[77] = 0.0;
   out_6359487390859137765[78] = 0.0;
   out_6359487390859137765[79] = 0.0;
   out_6359487390859137765[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8640471225264056008) {
   out_8640471225264056008[0] = state[0];
   out_8640471225264056008[1] = state[1];
   out_8640471225264056008[2] = state[2];
   out_8640471225264056008[3] = state[3];
   out_8640471225264056008[4] = state[4];
   out_8640471225264056008[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8640471225264056008[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8640471225264056008[7] = state[7];
   out_8640471225264056008[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7019142443099520017) {
   out_7019142443099520017[0] = 1;
   out_7019142443099520017[1] = 0;
   out_7019142443099520017[2] = 0;
   out_7019142443099520017[3] = 0;
   out_7019142443099520017[4] = 0;
   out_7019142443099520017[5] = 0;
   out_7019142443099520017[6] = 0;
   out_7019142443099520017[7] = 0;
   out_7019142443099520017[8] = 0;
   out_7019142443099520017[9] = 0;
   out_7019142443099520017[10] = 1;
   out_7019142443099520017[11] = 0;
   out_7019142443099520017[12] = 0;
   out_7019142443099520017[13] = 0;
   out_7019142443099520017[14] = 0;
   out_7019142443099520017[15] = 0;
   out_7019142443099520017[16] = 0;
   out_7019142443099520017[17] = 0;
   out_7019142443099520017[18] = 0;
   out_7019142443099520017[19] = 0;
   out_7019142443099520017[20] = 1;
   out_7019142443099520017[21] = 0;
   out_7019142443099520017[22] = 0;
   out_7019142443099520017[23] = 0;
   out_7019142443099520017[24] = 0;
   out_7019142443099520017[25] = 0;
   out_7019142443099520017[26] = 0;
   out_7019142443099520017[27] = 0;
   out_7019142443099520017[28] = 0;
   out_7019142443099520017[29] = 0;
   out_7019142443099520017[30] = 1;
   out_7019142443099520017[31] = 0;
   out_7019142443099520017[32] = 0;
   out_7019142443099520017[33] = 0;
   out_7019142443099520017[34] = 0;
   out_7019142443099520017[35] = 0;
   out_7019142443099520017[36] = 0;
   out_7019142443099520017[37] = 0;
   out_7019142443099520017[38] = 0;
   out_7019142443099520017[39] = 0;
   out_7019142443099520017[40] = 1;
   out_7019142443099520017[41] = 0;
   out_7019142443099520017[42] = 0;
   out_7019142443099520017[43] = 0;
   out_7019142443099520017[44] = 0;
   out_7019142443099520017[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7019142443099520017[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7019142443099520017[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7019142443099520017[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7019142443099520017[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7019142443099520017[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7019142443099520017[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7019142443099520017[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7019142443099520017[53] = -9.8100000000000005*dt;
   out_7019142443099520017[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7019142443099520017[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7019142443099520017[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7019142443099520017[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7019142443099520017[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7019142443099520017[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7019142443099520017[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7019142443099520017[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7019142443099520017[62] = 0;
   out_7019142443099520017[63] = 0;
   out_7019142443099520017[64] = 0;
   out_7019142443099520017[65] = 0;
   out_7019142443099520017[66] = 0;
   out_7019142443099520017[67] = 0;
   out_7019142443099520017[68] = 0;
   out_7019142443099520017[69] = 0;
   out_7019142443099520017[70] = 1;
   out_7019142443099520017[71] = 0;
   out_7019142443099520017[72] = 0;
   out_7019142443099520017[73] = 0;
   out_7019142443099520017[74] = 0;
   out_7019142443099520017[75] = 0;
   out_7019142443099520017[76] = 0;
   out_7019142443099520017[77] = 0;
   out_7019142443099520017[78] = 0;
   out_7019142443099520017[79] = 0;
   out_7019142443099520017[80] = 1;
}
void h_25(double *state, double *unused, double *out_1253470904109969861) {
   out_1253470904109969861[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7183564857665749011) {
   out_7183564857665749011[0] = 0;
   out_7183564857665749011[1] = 0;
   out_7183564857665749011[2] = 0;
   out_7183564857665749011[3] = 0;
   out_7183564857665749011[4] = 0;
   out_7183564857665749011[5] = 0;
   out_7183564857665749011[6] = 1;
   out_7183564857665749011[7] = 0;
   out_7183564857665749011[8] = 0;
}
void h_24(double *state, double *unused, double *out_2962653407625604630) {
   out_2962653407625604630[0] = state[4];
   out_2962653407625604630[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5135958713882120408) {
   out_5135958713882120408[0] = 0;
   out_5135958713882120408[1] = 0;
   out_5135958713882120408[2] = 0;
   out_5135958713882120408[3] = 0;
   out_5135958713882120408[4] = 1;
   out_5135958713882120408[5] = 0;
   out_5135958713882120408[6] = 0;
   out_5135958713882120408[7] = 0;
   out_5135958713882120408[8] = 0;
   out_5135958713882120408[9] = 0;
   out_5135958713882120408[10] = 0;
   out_5135958713882120408[11] = 0;
   out_5135958713882120408[12] = 0;
   out_5135958713882120408[13] = 0;
   out_5135958713882120408[14] = 1;
   out_5135958713882120408[15] = 0;
   out_5135958713882120408[16] = 0;
   out_5135958713882120408[17] = 0;
}
void h_30(double *state, double *unused, double *out_2100381110359636395) {
   out_2100381110359636395[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4665231899158500384) {
   out_4665231899158500384[0] = 0;
   out_4665231899158500384[1] = 0;
   out_4665231899158500384[2] = 0;
   out_4665231899158500384[3] = 0;
   out_4665231899158500384[4] = 1;
   out_4665231899158500384[5] = 0;
   out_4665231899158500384[6] = 0;
   out_4665231899158500384[7] = 0;
   out_4665231899158500384[8] = 0;
}
void h_26(double *state, double *unused, double *out_8346832167819809863) {
   out_8346832167819809863[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7521675897169746381) {
   out_7521675897169746381[0] = 0;
   out_7521675897169746381[1] = 0;
   out_7521675897169746381[2] = 0;
   out_7521675897169746381[3] = 0;
   out_7521675897169746381[4] = 0;
   out_7521675897169746381[5] = 0;
   out_7521675897169746381[6] = 0;
   out_7521675897169746381[7] = 1;
   out_7521675897169746381[8] = 0;
}
void h_27(double *state, double *unused, double *out_4290256955554302546) {
   out_4290256955554302546[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6839995210958925295) {
   out_6839995210958925295[0] = 0;
   out_6839995210958925295[1] = 0;
   out_6839995210958925295[2] = 0;
   out_6839995210958925295[3] = 1;
   out_6839995210958925295[4] = 0;
   out_6839995210958925295[5] = 0;
   out_6839995210958925295[6] = 0;
   out_6839995210958925295[7] = 0;
   out_6839995210958925295[8] = 0;
}
void h_29(double *state, double *unused, double *out_6695928353906360745) {
   out_6695928353906360745[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4155000554844108200) {
   out_4155000554844108200[0] = 0;
   out_4155000554844108200[1] = 1;
   out_4155000554844108200[2] = 0;
   out_4155000554844108200[3] = 0;
   out_4155000554844108200[4] = 0;
   out_4155000554844108200[5] = 0;
   out_4155000554844108200[6] = 0;
   out_4155000554844108200[7] = 0;
   out_4155000554844108200[8] = 0;
}
void h_28(double *state, double *unused, double *out_8173563278849107317) {
   out_8173563278849107317[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9209344501795912842) {
   out_9209344501795912842[0] = 1;
   out_9209344501795912842[1] = 0;
   out_9209344501795912842[2] = 0;
   out_9209344501795912842[3] = 0;
   out_9209344501795912842[4] = 0;
   out_9209344501795912842[5] = 0;
   out_9209344501795912842[6] = 0;
   out_9209344501795912842[7] = 0;
   out_9209344501795912842[8] = 0;
}
void h_31(double *state, double *unused, double *out_5517364322240381075) {
   out_5517364322240381075[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6895467794936394905) {
   out_6895467794936394905[0] = 0;
   out_6895467794936394905[1] = 0;
   out_6895467794936394905[2] = 0;
   out_6895467794936394905[3] = 0;
   out_6895467794936394905[4] = 0;
   out_6895467794936394905[5] = 0;
   out_6895467794936394905[6] = 0;
   out_6895467794936394905[7] = 0;
   out_6895467794936394905[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2890366190982855796) {
  err_fun(nom_x, delta_x, out_2890366190982855796);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1959709052486962483) {
  inv_err_fun(nom_x, true_x, out_1959709052486962483);
}
void car_H_mod_fun(double *state, double *out_6359487390859137765) {
  H_mod_fun(state, out_6359487390859137765);
}
void car_f_fun(double *state, double dt, double *out_8640471225264056008) {
  f_fun(state,  dt, out_8640471225264056008);
}
void car_F_fun(double *state, double dt, double *out_7019142443099520017) {
  F_fun(state,  dt, out_7019142443099520017);
}
void car_h_25(double *state, double *unused, double *out_1253470904109969861) {
  h_25(state, unused, out_1253470904109969861);
}
void car_H_25(double *state, double *unused, double *out_7183564857665749011) {
  H_25(state, unused, out_7183564857665749011);
}
void car_h_24(double *state, double *unused, double *out_2962653407625604630) {
  h_24(state, unused, out_2962653407625604630);
}
void car_H_24(double *state, double *unused, double *out_5135958713882120408) {
  H_24(state, unused, out_5135958713882120408);
}
void car_h_30(double *state, double *unused, double *out_2100381110359636395) {
  h_30(state, unused, out_2100381110359636395);
}
void car_H_30(double *state, double *unused, double *out_4665231899158500384) {
  H_30(state, unused, out_4665231899158500384);
}
void car_h_26(double *state, double *unused, double *out_8346832167819809863) {
  h_26(state, unused, out_8346832167819809863);
}
void car_H_26(double *state, double *unused, double *out_7521675897169746381) {
  H_26(state, unused, out_7521675897169746381);
}
void car_h_27(double *state, double *unused, double *out_4290256955554302546) {
  h_27(state, unused, out_4290256955554302546);
}
void car_H_27(double *state, double *unused, double *out_6839995210958925295) {
  H_27(state, unused, out_6839995210958925295);
}
void car_h_29(double *state, double *unused, double *out_6695928353906360745) {
  h_29(state, unused, out_6695928353906360745);
}
void car_H_29(double *state, double *unused, double *out_4155000554844108200) {
  H_29(state, unused, out_4155000554844108200);
}
void car_h_28(double *state, double *unused, double *out_8173563278849107317) {
  h_28(state, unused, out_8173563278849107317);
}
void car_H_28(double *state, double *unused, double *out_9209344501795912842) {
  H_28(state, unused, out_9209344501795912842);
}
void car_h_31(double *state, double *unused, double *out_5517364322240381075) {
  h_31(state, unused, out_5517364322240381075);
}
void car_H_31(double *state, double *unused, double *out_6895467794936394905) {
  H_31(state, unused, out_6895467794936394905);
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
