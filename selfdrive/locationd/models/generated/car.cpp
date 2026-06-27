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
void err_fun(double *nom_x, double *delta_x, double *out_7469803269040701934) {
   out_7469803269040701934[0] = delta_x[0] + nom_x[0];
   out_7469803269040701934[1] = delta_x[1] + nom_x[1];
   out_7469803269040701934[2] = delta_x[2] + nom_x[2];
   out_7469803269040701934[3] = delta_x[3] + nom_x[3];
   out_7469803269040701934[4] = delta_x[4] + nom_x[4];
   out_7469803269040701934[5] = delta_x[5] + nom_x[5];
   out_7469803269040701934[6] = delta_x[6] + nom_x[6];
   out_7469803269040701934[7] = delta_x[7] + nom_x[7];
   out_7469803269040701934[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5146487777305957172) {
   out_5146487777305957172[0] = -nom_x[0] + true_x[0];
   out_5146487777305957172[1] = -nom_x[1] + true_x[1];
   out_5146487777305957172[2] = -nom_x[2] + true_x[2];
   out_5146487777305957172[3] = -nom_x[3] + true_x[3];
   out_5146487777305957172[4] = -nom_x[4] + true_x[4];
   out_5146487777305957172[5] = -nom_x[5] + true_x[5];
   out_5146487777305957172[6] = -nom_x[6] + true_x[6];
   out_5146487777305957172[7] = -nom_x[7] + true_x[7];
   out_5146487777305957172[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6489034200722373172) {
   out_6489034200722373172[0] = 1.0;
   out_6489034200722373172[1] = 0.0;
   out_6489034200722373172[2] = 0.0;
   out_6489034200722373172[3] = 0.0;
   out_6489034200722373172[4] = 0.0;
   out_6489034200722373172[5] = 0.0;
   out_6489034200722373172[6] = 0.0;
   out_6489034200722373172[7] = 0.0;
   out_6489034200722373172[8] = 0.0;
   out_6489034200722373172[9] = 0.0;
   out_6489034200722373172[10] = 1.0;
   out_6489034200722373172[11] = 0.0;
   out_6489034200722373172[12] = 0.0;
   out_6489034200722373172[13] = 0.0;
   out_6489034200722373172[14] = 0.0;
   out_6489034200722373172[15] = 0.0;
   out_6489034200722373172[16] = 0.0;
   out_6489034200722373172[17] = 0.0;
   out_6489034200722373172[18] = 0.0;
   out_6489034200722373172[19] = 0.0;
   out_6489034200722373172[20] = 1.0;
   out_6489034200722373172[21] = 0.0;
   out_6489034200722373172[22] = 0.0;
   out_6489034200722373172[23] = 0.0;
   out_6489034200722373172[24] = 0.0;
   out_6489034200722373172[25] = 0.0;
   out_6489034200722373172[26] = 0.0;
   out_6489034200722373172[27] = 0.0;
   out_6489034200722373172[28] = 0.0;
   out_6489034200722373172[29] = 0.0;
   out_6489034200722373172[30] = 1.0;
   out_6489034200722373172[31] = 0.0;
   out_6489034200722373172[32] = 0.0;
   out_6489034200722373172[33] = 0.0;
   out_6489034200722373172[34] = 0.0;
   out_6489034200722373172[35] = 0.0;
   out_6489034200722373172[36] = 0.0;
   out_6489034200722373172[37] = 0.0;
   out_6489034200722373172[38] = 0.0;
   out_6489034200722373172[39] = 0.0;
   out_6489034200722373172[40] = 1.0;
   out_6489034200722373172[41] = 0.0;
   out_6489034200722373172[42] = 0.0;
   out_6489034200722373172[43] = 0.0;
   out_6489034200722373172[44] = 0.0;
   out_6489034200722373172[45] = 0.0;
   out_6489034200722373172[46] = 0.0;
   out_6489034200722373172[47] = 0.0;
   out_6489034200722373172[48] = 0.0;
   out_6489034200722373172[49] = 0.0;
   out_6489034200722373172[50] = 1.0;
   out_6489034200722373172[51] = 0.0;
   out_6489034200722373172[52] = 0.0;
   out_6489034200722373172[53] = 0.0;
   out_6489034200722373172[54] = 0.0;
   out_6489034200722373172[55] = 0.0;
   out_6489034200722373172[56] = 0.0;
   out_6489034200722373172[57] = 0.0;
   out_6489034200722373172[58] = 0.0;
   out_6489034200722373172[59] = 0.0;
   out_6489034200722373172[60] = 1.0;
   out_6489034200722373172[61] = 0.0;
   out_6489034200722373172[62] = 0.0;
   out_6489034200722373172[63] = 0.0;
   out_6489034200722373172[64] = 0.0;
   out_6489034200722373172[65] = 0.0;
   out_6489034200722373172[66] = 0.0;
   out_6489034200722373172[67] = 0.0;
   out_6489034200722373172[68] = 0.0;
   out_6489034200722373172[69] = 0.0;
   out_6489034200722373172[70] = 1.0;
   out_6489034200722373172[71] = 0.0;
   out_6489034200722373172[72] = 0.0;
   out_6489034200722373172[73] = 0.0;
   out_6489034200722373172[74] = 0.0;
   out_6489034200722373172[75] = 0.0;
   out_6489034200722373172[76] = 0.0;
   out_6489034200722373172[77] = 0.0;
   out_6489034200722373172[78] = 0.0;
   out_6489034200722373172[79] = 0.0;
   out_6489034200722373172[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2115535381215445196) {
   out_2115535381215445196[0] = state[0];
   out_2115535381215445196[1] = state[1];
   out_2115535381215445196[2] = state[2];
   out_2115535381215445196[3] = state[3];
   out_2115535381215445196[4] = state[4];
   out_2115535381215445196[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2115535381215445196[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2115535381215445196[7] = state[7];
   out_2115535381215445196[8] = state[8];
}
void F_fun(double *state, double dt, double *out_697532477187400649) {
   out_697532477187400649[0] = 1;
   out_697532477187400649[1] = 0;
   out_697532477187400649[2] = 0;
   out_697532477187400649[3] = 0;
   out_697532477187400649[4] = 0;
   out_697532477187400649[5] = 0;
   out_697532477187400649[6] = 0;
   out_697532477187400649[7] = 0;
   out_697532477187400649[8] = 0;
   out_697532477187400649[9] = 0;
   out_697532477187400649[10] = 1;
   out_697532477187400649[11] = 0;
   out_697532477187400649[12] = 0;
   out_697532477187400649[13] = 0;
   out_697532477187400649[14] = 0;
   out_697532477187400649[15] = 0;
   out_697532477187400649[16] = 0;
   out_697532477187400649[17] = 0;
   out_697532477187400649[18] = 0;
   out_697532477187400649[19] = 0;
   out_697532477187400649[20] = 1;
   out_697532477187400649[21] = 0;
   out_697532477187400649[22] = 0;
   out_697532477187400649[23] = 0;
   out_697532477187400649[24] = 0;
   out_697532477187400649[25] = 0;
   out_697532477187400649[26] = 0;
   out_697532477187400649[27] = 0;
   out_697532477187400649[28] = 0;
   out_697532477187400649[29] = 0;
   out_697532477187400649[30] = 1;
   out_697532477187400649[31] = 0;
   out_697532477187400649[32] = 0;
   out_697532477187400649[33] = 0;
   out_697532477187400649[34] = 0;
   out_697532477187400649[35] = 0;
   out_697532477187400649[36] = 0;
   out_697532477187400649[37] = 0;
   out_697532477187400649[38] = 0;
   out_697532477187400649[39] = 0;
   out_697532477187400649[40] = 1;
   out_697532477187400649[41] = 0;
   out_697532477187400649[42] = 0;
   out_697532477187400649[43] = 0;
   out_697532477187400649[44] = 0;
   out_697532477187400649[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_697532477187400649[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_697532477187400649[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_697532477187400649[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_697532477187400649[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_697532477187400649[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_697532477187400649[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_697532477187400649[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_697532477187400649[53] = -9.8100000000000005*dt;
   out_697532477187400649[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_697532477187400649[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_697532477187400649[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_697532477187400649[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_697532477187400649[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_697532477187400649[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_697532477187400649[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_697532477187400649[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_697532477187400649[62] = 0;
   out_697532477187400649[63] = 0;
   out_697532477187400649[64] = 0;
   out_697532477187400649[65] = 0;
   out_697532477187400649[66] = 0;
   out_697532477187400649[67] = 0;
   out_697532477187400649[68] = 0;
   out_697532477187400649[69] = 0;
   out_697532477187400649[70] = 1;
   out_697532477187400649[71] = 0;
   out_697532477187400649[72] = 0;
   out_697532477187400649[73] = 0;
   out_697532477187400649[74] = 0;
   out_697532477187400649[75] = 0;
   out_697532477187400649[76] = 0;
   out_697532477187400649[77] = 0;
   out_697532477187400649[78] = 0;
   out_697532477187400649[79] = 0;
   out_697532477187400649[80] = 1;
}
void h_25(double *state, double *unused, double *out_5124614186779649716) {
   out_5124614186779649716[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2704154025189864065) {
   out_2704154025189864065[0] = 0;
   out_2704154025189864065[1] = 0;
   out_2704154025189864065[2] = 0;
   out_2704154025189864065[3] = 0;
   out_2704154025189864065[4] = 0;
   out_2704154025189864065[5] = 0;
   out_2704154025189864065[6] = 1;
   out_2704154025189864065[7] = 0;
   out_2704154025189864065[8] = 0;
}
void h_24(double *state, double *unused, double *out_2288772113706282518) {
   out_2288772113706282518[0] = state[4];
   out_2288772113706282518[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4876803624195363631) {
   out_4876803624195363631[0] = 0;
   out_4876803624195363631[1] = 0;
   out_4876803624195363631[2] = 0;
   out_4876803624195363631[3] = 0;
   out_4876803624195363631[4] = 1;
   out_4876803624195363631[5] = 0;
   out_4876803624195363631[6] = 0;
   out_4876803624195363631[7] = 0;
   out_4876803624195363631[8] = 0;
   out_4876803624195363631[9] = 0;
   out_4876803624195363631[10] = 0;
   out_4876803624195363631[11] = 0;
   out_4876803624195363631[12] = 0;
   out_4876803624195363631[13] = 0;
   out_4876803624195363631[14] = 1;
   out_4876803624195363631[15] = 0;
   out_4876803624195363631[16] = 0;
   out_4876803624195363631[17] = 0;
}
void h_30(double *state, double *unused, double *out_3032926190730655359) {
   out_3032926190730655359[0] = state[4];
}
void H_30(double *state, double *unused, double *out_185821066682615438) {
   out_185821066682615438[0] = 0;
   out_185821066682615438[1] = 0;
   out_185821066682615438[2] = 0;
   out_185821066682615438[3] = 0;
   out_185821066682615438[4] = 1;
   out_185821066682615438[5] = 0;
   out_185821066682615438[6] = 0;
   out_185821066682615438[7] = 0;
   out_185821066682615438[8] = 0;
}
void h_26(double *state, double *unused, double *out_7090256083799836565) {
   out_7090256083799836565[0] = state[7];
}
void H_26(double *state, double *unused, double *out_600371944570936536) {
   out_600371944570936536[0] = 0;
   out_600371944570936536[1] = 0;
   out_600371944570936536[2] = 0;
   out_600371944570936536[3] = 0;
   out_600371944570936536[4] = 0;
   out_600371944570936536[5] = 0;
   out_600371944570936536[6] = 0;
   out_600371944570936536[7] = 1;
   out_600371944570936536[8] = 0;
}
void h_27(double *state, double *unused, double *out_6474868053290145758) {
   out_6474868053290145758[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2037773004501327779) {
   out_2037773004501327779[0] = 0;
   out_2037773004501327779[1] = 0;
   out_2037773004501327779[2] = 0;
   out_2037773004501327779[3] = 1;
   out_2037773004501327779[4] = 0;
   out_2037773004501327779[5] = 0;
   out_2037773004501327779[6] = 0;
   out_2037773004501327779[7] = 0;
   out_2037773004501327779[8] = 0;
}
void h_29(double *state, double *unused, double *out_8675656061811612194) {
   out_8675656061811612194[0] = state[1];
}
void H_29(double *state, double *unused, double *out_324410277631776746) {
   out_324410277631776746[0] = 0;
   out_324410277631776746[1] = 1;
   out_324410277631776746[2] = 0;
   out_324410277631776746[3] = 0;
   out_324410277631776746[4] = 0;
   out_324410277631776746[5] = 0;
   out_324410277631776746[6] = 0;
   out_324410277631776746[7] = 0;
   out_324410277631776746[8] = 0;
}
void h_28(double *state, double *unused, double *out_2417538160220964552) {
   out_2417538160220964552[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4757988739437753828) {
   out_4757988739437753828[0] = 1;
   out_4757988739437753828[1] = 0;
   out_4757988739437753828[2] = 0;
   out_4757988739437753828[3] = 0;
   out_4757988739437753828[4] = 0;
   out_4757988739437753828[5] = 0;
   out_4757988739437753828[6] = 0;
   out_4757988739437753828[7] = 0;
   out_4757988739437753828[8] = 0;
}
void h_31(double *state, double *unused, double *out_6551294660579550964) {
   out_6551294660579550964[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2673508063312903637) {
   out_2673508063312903637[0] = 0;
   out_2673508063312903637[1] = 0;
   out_2673508063312903637[2] = 0;
   out_2673508063312903637[3] = 0;
   out_2673508063312903637[4] = 0;
   out_2673508063312903637[5] = 0;
   out_2673508063312903637[6] = 0;
   out_2673508063312903637[7] = 0;
   out_2673508063312903637[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7469803269040701934) {
  err_fun(nom_x, delta_x, out_7469803269040701934);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5146487777305957172) {
  inv_err_fun(nom_x, true_x, out_5146487777305957172);
}
void car_H_mod_fun(double *state, double *out_6489034200722373172) {
  H_mod_fun(state, out_6489034200722373172);
}
void car_f_fun(double *state, double dt, double *out_2115535381215445196) {
  f_fun(state,  dt, out_2115535381215445196);
}
void car_F_fun(double *state, double dt, double *out_697532477187400649) {
  F_fun(state,  dt, out_697532477187400649);
}
void car_h_25(double *state, double *unused, double *out_5124614186779649716) {
  h_25(state, unused, out_5124614186779649716);
}
void car_H_25(double *state, double *unused, double *out_2704154025189864065) {
  H_25(state, unused, out_2704154025189864065);
}
void car_h_24(double *state, double *unused, double *out_2288772113706282518) {
  h_24(state, unused, out_2288772113706282518);
}
void car_H_24(double *state, double *unused, double *out_4876803624195363631) {
  H_24(state, unused, out_4876803624195363631);
}
void car_h_30(double *state, double *unused, double *out_3032926190730655359) {
  h_30(state, unused, out_3032926190730655359);
}
void car_H_30(double *state, double *unused, double *out_185821066682615438) {
  H_30(state, unused, out_185821066682615438);
}
void car_h_26(double *state, double *unused, double *out_7090256083799836565) {
  h_26(state, unused, out_7090256083799836565);
}
void car_H_26(double *state, double *unused, double *out_600371944570936536) {
  H_26(state, unused, out_600371944570936536);
}
void car_h_27(double *state, double *unused, double *out_6474868053290145758) {
  h_27(state, unused, out_6474868053290145758);
}
void car_H_27(double *state, double *unused, double *out_2037773004501327779) {
  H_27(state, unused, out_2037773004501327779);
}
void car_h_29(double *state, double *unused, double *out_8675656061811612194) {
  h_29(state, unused, out_8675656061811612194);
}
void car_H_29(double *state, double *unused, double *out_324410277631776746) {
  H_29(state, unused, out_324410277631776746);
}
void car_h_28(double *state, double *unused, double *out_2417538160220964552) {
  h_28(state, unused, out_2417538160220964552);
}
void car_H_28(double *state, double *unused, double *out_4757988739437753828) {
  H_28(state, unused, out_4757988739437753828);
}
void car_h_31(double *state, double *unused, double *out_6551294660579550964) {
  h_31(state, unused, out_6551294660579550964);
}
void car_H_31(double *state, double *unused, double *out_2673508063312903637) {
  H_31(state, unused, out_2673508063312903637);
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
