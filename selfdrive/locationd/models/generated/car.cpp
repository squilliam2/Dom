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
void err_fun(double *nom_x, double *delta_x, double *out_2092251631667009235) {
   out_2092251631667009235[0] = delta_x[0] + nom_x[0];
   out_2092251631667009235[1] = delta_x[1] + nom_x[1];
   out_2092251631667009235[2] = delta_x[2] + nom_x[2];
   out_2092251631667009235[3] = delta_x[3] + nom_x[3];
   out_2092251631667009235[4] = delta_x[4] + nom_x[4];
   out_2092251631667009235[5] = delta_x[5] + nom_x[5];
   out_2092251631667009235[6] = delta_x[6] + nom_x[6];
   out_2092251631667009235[7] = delta_x[7] + nom_x[7];
   out_2092251631667009235[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2300837471234553583) {
   out_2300837471234553583[0] = -nom_x[0] + true_x[0];
   out_2300837471234553583[1] = -nom_x[1] + true_x[1];
   out_2300837471234553583[2] = -nom_x[2] + true_x[2];
   out_2300837471234553583[3] = -nom_x[3] + true_x[3];
   out_2300837471234553583[4] = -nom_x[4] + true_x[4];
   out_2300837471234553583[5] = -nom_x[5] + true_x[5];
   out_2300837471234553583[6] = -nom_x[6] + true_x[6];
   out_2300837471234553583[7] = -nom_x[7] + true_x[7];
   out_2300837471234553583[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4027971756970364591) {
   out_4027971756970364591[0] = 1.0;
   out_4027971756970364591[1] = 0.0;
   out_4027971756970364591[2] = 0.0;
   out_4027971756970364591[3] = 0.0;
   out_4027971756970364591[4] = 0.0;
   out_4027971756970364591[5] = 0.0;
   out_4027971756970364591[6] = 0.0;
   out_4027971756970364591[7] = 0.0;
   out_4027971756970364591[8] = 0.0;
   out_4027971756970364591[9] = 0.0;
   out_4027971756970364591[10] = 1.0;
   out_4027971756970364591[11] = 0.0;
   out_4027971756970364591[12] = 0.0;
   out_4027971756970364591[13] = 0.0;
   out_4027971756970364591[14] = 0.0;
   out_4027971756970364591[15] = 0.0;
   out_4027971756970364591[16] = 0.0;
   out_4027971756970364591[17] = 0.0;
   out_4027971756970364591[18] = 0.0;
   out_4027971756970364591[19] = 0.0;
   out_4027971756970364591[20] = 1.0;
   out_4027971756970364591[21] = 0.0;
   out_4027971756970364591[22] = 0.0;
   out_4027971756970364591[23] = 0.0;
   out_4027971756970364591[24] = 0.0;
   out_4027971756970364591[25] = 0.0;
   out_4027971756970364591[26] = 0.0;
   out_4027971756970364591[27] = 0.0;
   out_4027971756970364591[28] = 0.0;
   out_4027971756970364591[29] = 0.0;
   out_4027971756970364591[30] = 1.0;
   out_4027971756970364591[31] = 0.0;
   out_4027971756970364591[32] = 0.0;
   out_4027971756970364591[33] = 0.0;
   out_4027971756970364591[34] = 0.0;
   out_4027971756970364591[35] = 0.0;
   out_4027971756970364591[36] = 0.0;
   out_4027971756970364591[37] = 0.0;
   out_4027971756970364591[38] = 0.0;
   out_4027971756970364591[39] = 0.0;
   out_4027971756970364591[40] = 1.0;
   out_4027971756970364591[41] = 0.0;
   out_4027971756970364591[42] = 0.0;
   out_4027971756970364591[43] = 0.0;
   out_4027971756970364591[44] = 0.0;
   out_4027971756970364591[45] = 0.0;
   out_4027971756970364591[46] = 0.0;
   out_4027971756970364591[47] = 0.0;
   out_4027971756970364591[48] = 0.0;
   out_4027971756970364591[49] = 0.0;
   out_4027971756970364591[50] = 1.0;
   out_4027971756970364591[51] = 0.0;
   out_4027971756970364591[52] = 0.0;
   out_4027971756970364591[53] = 0.0;
   out_4027971756970364591[54] = 0.0;
   out_4027971756970364591[55] = 0.0;
   out_4027971756970364591[56] = 0.0;
   out_4027971756970364591[57] = 0.0;
   out_4027971756970364591[58] = 0.0;
   out_4027971756970364591[59] = 0.0;
   out_4027971756970364591[60] = 1.0;
   out_4027971756970364591[61] = 0.0;
   out_4027971756970364591[62] = 0.0;
   out_4027971756970364591[63] = 0.0;
   out_4027971756970364591[64] = 0.0;
   out_4027971756970364591[65] = 0.0;
   out_4027971756970364591[66] = 0.0;
   out_4027971756970364591[67] = 0.0;
   out_4027971756970364591[68] = 0.0;
   out_4027971756970364591[69] = 0.0;
   out_4027971756970364591[70] = 1.0;
   out_4027971756970364591[71] = 0.0;
   out_4027971756970364591[72] = 0.0;
   out_4027971756970364591[73] = 0.0;
   out_4027971756970364591[74] = 0.0;
   out_4027971756970364591[75] = 0.0;
   out_4027971756970364591[76] = 0.0;
   out_4027971756970364591[77] = 0.0;
   out_4027971756970364591[78] = 0.0;
   out_4027971756970364591[79] = 0.0;
   out_4027971756970364591[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6249326857146976875) {
   out_6249326857146976875[0] = state[0];
   out_6249326857146976875[1] = state[1];
   out_6249326857146976875[2] = state[2];
   out_6249326857146976875[3] = state[3];
   out_6249326857146976875[4] = state[4];
   out_6249326857146976875[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6249326857146976875[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6249326857146976875[7] = state[7];
   out_6249326857146976875[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1875491097223459739) {
   out_1875491097223459739[0] = 1;
   out_1875491097223459739[1] = 0;
   out_1875491097223459739[2] = 0;
   out_1875491097223459739[3] = 0;
   out_1875491097223459739[4] = 0;
   out_1875491097223459739[5] = 0;
   out_1875491097223459739[6] = 0;
   out_1875491097223459739[7] = 0;
   out_1875491097223459739[8] = 0;
   out_1875491097223459739[9] = 0;
   out_1875491097223459739[10] = 1;
   out_1875491097223459739[11] = 0;
   out_1875491097223459739[12] = 0;
   out_1875491097223459739[13] = 0;
   out_1875491097223459739[14] = 0;
   out_1875491097223459739[15] = 0;
   out_1875491097223459739[16] = 0;
   out_1875491097223459739[17] = 0;
   out_1875491097223459739[18] = 0;
   out_1875491097223459739[19] = 0;
   out_1875491097223459739[20] = 1;
   out_1875491097223459739[21] = 0;
   out_1875491097223459739[22] = 0;
   out_1875491097223459739[23] = 0;
   out_1875491097223459739[24] = 0;
   out_1875491097223459739[25] = 0;
   out_1875491097223459739[26] = 0;
   out_1875491097223459739[27] = 0;
   out_1875491097223459739[28] = 0;
   out_1875491097223459739[29] = 0;
   out_1875491097223459739[30] = 1;
   out_1875491097223459739[31] = 0;
   out_1875491097223459739[32] = 0;
   out_1875491097223459739[33] = 0;
   out_1875491097223459739[34] = 0;
   out_1875491097223459739[35] = 0;
   out_1875491097223459739[36] = 0;
   out_1875491097223459739[37] = 0;
   out_1875491097223459739[38] = 0;
   out_1875491097223459739[39] = 0;
   out_1875491097223459739[40] = 1;
   out_1875491097223459739[41] = 0;
   out_1875491097223459739[42] = 0;
   out_1875491097223459739[43] = 0;
   out_1875491097223459739[44] = 0;
   out_1875491097223459739[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1875491097223459739[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1875491097223459739[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1875491097223459739[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1875491097223459739[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1875491097223459739[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1875491097223459739[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1875491097223459739[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1875491097223459739[53] = -9.8100000000000005*dt;
   out_1875491097223459739[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1875491097223459739[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1875491097223459739[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1875491097223459739[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1875491097223459739[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1875491097223459739[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1875491097223459739[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1875491097223459739[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1875491097223459739[62] = 0;
   out_1875491097223459739[63] = 0;
   out_1875491097223459739[64] = 0;
   out_1875491097223459739[65] = 0;
   out_1875491097223459739[66] = 0;
   out_1875491097223459739[67] = 0;
   out_1875491097223459739[68] = 0;
   out_1875491097223459739[69] = 0;
   out_1875491097223459739[70] = 1;
   out_1875491097223459739[71] = 0;
   out_1875491097223459739[72] = 0;
   out_1875491097223459739[73] = 0;
   out_1875491097223459739[74] = 0;
   out_1875491097223459739[75] = 0;
   out_1875491097223459739[76] = 0;
   out_1875491097223459739[77] = 0;
   out_1875491097223459739[78] = 0;
   out_1875491097223459739[79] = 0;
   out_1875491097223459739[80] = 1;
}
void h_25(double *state, double *unused, double *out_5658454479721392301) {
   out_5658454479721392301[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8931663582155029431) {
   out_8931663582155029431[0] = 0;
   out_8931663582155029431[1] = 0;
   out_8931663582155029431[2] = 0;
   out_8931663582155029431[3] = 0;
   out_8931663582155029431[4] = 0;
   out_8931663582155029431[5] = 0;
   out_8931663582155029431[6] = 1;
   out_8931663582155029431[7] = 0;
   out_8931663582155029431[8] = 0;
}
void h_24(double *state, double *unused, double *out_8388151047956984123) {
   out_8388151047956984123[0] = state[4];
   out_8388151047956984123[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8535018277801169936) {
   out_8535018277801169936[0] = 0;
   out_8535018277801169936[1] = 0;
   out_8535018277801169936[2] = 0;
   out_8535018277801169936[3] = 0;
   out_8535018277801169936[4] = 1;
   out_8535018277801169936[5] = 0;
   out_8535018277801169936[6] = 0;
   out_8535018277801169936[7] = 0;
   out_8535018277801169936[8] = 0;
   out_8535018277801169936[9] = 0;
   out_8535018277801169936[10] = 0;
   out_8535018277801169936[11] = 0;
   out_8535018277801169936[12] = 0;
   out_8535018277801169936[13] = 0;
   out_8535018277801169936[14] = 1;
   out_8535018277801169936[15] = 0;
   out_8535018277801169936[16] = 0;
   out_8535018277801169936[17] = 0;
}
void h_30(double *state, double *unused, double *out_2021004951467369951) {
   out_2021004951467369951[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6996747533047273558) {
   out_6996747533047273558[0] = 0;
   out_6996747533047273558[1] = 0;
   out_6996747533047273558[2] = 0;
   out_6996747533047273558[3] = 0;
   out_6996747533047273558[4] = 1;
   out_6996747533047273558[5] = 0;
   out_6996747533047273558[6] = 0;
   out_6996747533047273558[7] = 0;
   out_6996747533047273558[8] = 0;
}
void h_26(double *state, double *unused, double *out_853261150391228214) {
   out_853261150391228214[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5190160263280973207) {
   out_5190160263280973207[0] = 0;
   out_5190160263280973207[1] = 0;
   out_5190160263280973207[2] = 0;
   out_5190160263280973207[3] = 0;
   out_5190160263280973207[4] = 0;
   out_5190160263280973207[5] = 0;
   out_5190160263280973207[6] = 0;
   out_5190160263280973207[7] = 1;
   out_5190160263280973207[8] = 0;
}
void h_27(double *state, double *unused, double *out_9074727769370462317) {
   out_9074727769370462317[0] = state[3];
}
void H_27(double *state, double *unused, double *out_9171510844847698469) {
   out_9171510844847698469[0] = 0;
   out_9171510844847698469[1] = 0;
   out_9171510844847698469[2] = 0;
   out_9171510844847698469[3] = 1;
   out_9171510844847698469[4] = 0;
   out_9171510844847698469[5] = 0;
   out_9171510844847698469[6] = 0;
   out_9171510844847698469[7] = 0;
   out_9171510844847698469[8] = 0;
}
void h_29(double *state, double *unused, double *out_5628340221843964391) {
   out_5628340221843964391[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6486516188732881374) {
   out_6486516188732881374[0] = 0;
   out_6486516188732881374[1] = 1;
   out_6486516188732881374[2] = 0;
   out_6486516188732881374[3] = 0;
   out_6486516188732881374[4] = 0;
   out_6486516188732881374[5] = 0;
   out_6486516188732881374[6] = 0;
   out_6486516188732881374[7] = 0;
   out_6486516188732881374[8] = 0;
}
void h_28(double *state, double *unused, double *out_4073054501709616672) {
   out_4073054501709616672[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6877828867907139668) {
   out_6877828867907139668[0] = 1;
   out_6877828867907139668[1] = 0;
   out_6877828867907139668[2] = 0;
   out_6877828867907139668[3] = 0;
   out_6877828867907139668[4] = 0;
   out_6877828867907139668[5] = 0;
   out_6877828867907139668[6] = 0;
   out_6877828867907139668[7] = 0;
   out_6877828867907139668[8] = 0;
}
void h_31(double *state, double *unused, double *out_508659560249742002) {
   out_508659560249742002[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4563952161047621731) {
   out_4563952161047621731[0] = 0;
   out_4563952161047621731[1] = 0;
   out_4563952161047621731[2] = 0;
   out_4563952161047621731[3] = 0;
   out_4563952161047621731[4] = 0;
   out_4563952161047621731[5] = 0;
   out_4563952161047621731[6] = 0;
   out_4563952161047621731[7] = 0;
   out_4563952161047621731[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2092251631667009235) {
  err_fun(nom_x, delta_x, out_2092251631667009235);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2300837471234553583) {
  inv_err_fun(nom_x, true_x, out_2300837471234553583);
}
void car_H_mod_fun(double *state, double *out_4027971756970364591) {
  H_mod_fun(state, out_4027971756970364591);
}
void car_f_fun(double *state, double dt, double *out_6249326857146976875) {
  f_fun(state,  dt, out_6249326857146976875);
}
void car_F_fun(double *state, double dt, double *out_1875491097223459739) {
  F_fun(state,  dt, out_1875491097223459739);
}
void car_h_25(double *state, double *unused, double *out_5658454479721392301) {
  h_25(state, unused, out_5658454479721392301);
}
void car_H_25(double *state, double *unused, double *out_8931663582155029431) {
  H_25(state, unused, out_8931663582155029431);
}
void car_h_24(double *state, double *unused, double *out_8388151047956984123) {
  h_24(state, unused, out_8388151047956984123);
}
void car_H_24(double *state, double *unused, double *out_8535018277801169936) {
  H_24(state, unused, out_8535018277801169936);
}
void car_h_30(double *state, double *unused, double *out_2021004951467369951) {
  h_30(state, unused, out_2021004951467369951);
}
void car_H_30(double *state, double *unused, double *out_6996747533047273558) {
  H_30(state, unused, out_6996747533047273558);
}
void car_h_26(double *state, double *unused, double *out_853261150391228214) {
  h_26(state, unused, out_853261150391228214);
}
void car_H_26(double *state, double *unused, double *out_5190160263280973207) {
  H_26(state, unused, out_5190160263280973207);
}
void car_h_27(double *state, double *unused, double *out_9074727769370462317) {
  h_27(state, unused, out_9074727769370462317);
}
void car_H_27(double *state, double *unused, double *out_9171510844847698469) {
  H_27(state, unused, out_9171510844847698469);
}
void car_h_29(double *state, double *unused, double *out_5628340221843964391) {
  h_29(state, unused, out_5628340221843964391);
}
void car_H_29(double *state, double *unused, double *out_6486516188732881374) {
  H_29(state, unused, out_6486516188732881374);
}
void car_h_28(double *state, double *unused, double *out_4073054501709616672) {
  h_28(state, unused, out_4073054501709616672);
}
void car_H_28(double *state, double *unused, double *out_6877828867907139668) {
  H_28(state, unused, out_6877828867907139668);
}
void car_h_31(double *state, double *unused, double *out_508659560249742002) {
  h_31(state, unused, out_508659560249742002);
}
void car_H_31(double *state, double *unused, double *out_4563952161047621731) {
  H_31(state, unused, out_4563952161047621731);
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
