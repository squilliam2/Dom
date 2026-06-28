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
void err_fun(double *nom_x, double *delta_x, double *out_8558441916270761648) {
   out_8558441916270761648[0] = delta_x[0] + nom_x[0];
   out_8558441916270761648[1] = delta_x[1] + nom_x[1];
   out_8558441916270761648[2] = delta_x[2] + nom_x[2];
   out_8558441916270761648[3] = delta_x[3] + nom_x[3];
   out_8558441916270761648[4] = delta_x[4] + nom_x[4];
   out_8558441916270761648[5] = delta_x[5] + nom_x[5];
   out_8558441916270761648[6] = delta_x[6] + nom_x[6];
   out_8558441916270761648[7] = delta_x[7] + nom_x[7];
   out_8558441916270761648[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9137456234820429023) {
   out_9137456234820429023[0] = -nom_x[0] + true_x[0];
   out_9137456234820429023[1] = -nom_x[1] + true_x[1];
   out_9137456234820429023[2] = -nom_x[2] + true_x[2];
   out_9137456234820429023[3] = -nom_x[3] + true_x[3];
   out_9137456234820429023[4] = -nom_x[4] + true_x[4];
   out_9137456234820429023[5] = -nom_x[5] + true_x[5];
   out_9137456234820429023[6] = -nom_x[6] + true_x[6];
   out_9137456234820429023[7] = -nom_x[7] + true_x[7];
   out_9137456234820429023[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7685081031100061070) {
   out_7685081031100061070[0] = 1.0;
   out_7685081031100061070[1] = 0.0;
   out_7685081031100061070[2] = 0.0;
   out_7685081031100061070[3] = 0.0;
   out_7685081031100061070[4] = 0.0;
   out_7685081031100061070[5] = 0.0;
   out_7685081031100061070[6] = 0.0;
   out_7685081031100061070[7] = 0.0;
   out_7685081031100061070[8] = 0.0;
   out_7685081031100061070[9] = 0.0;
   out_7685081031100061070[10] = 1.0;
   out_7685081031100061070[11] = 0.0;
   out_7685081031100061070[12] = 0.0;
   out_7685081031100061070[13] = 0.0;
   out_7685081031100061070[14] = 0.0;
   out_7685081031100061070[15] = 0.0;
   out_7685081031100061070[16] = 0.0;
   out_7685081031100061070[17] = 0.0;
   out_7685081031100061070[18] = 0.0;
   out_7685081031100061070[19] = 0.0;
   out_7685081031100061070[20] = 1.0;
   out_7685081031100061070[21] = 0.0;
   out_7685081031100061070[22] = 0.0;
   out_7685081031100061070[23] = 0.0;
   out_7685081031100061070[24] = 0.0;
   out_7685081031100061070[25] = 0.0;
   out_7685081031100061070[26] = 0.0;
   out_7685081031100061070[27] = 0.0;
   out_7685081031100061070[28] = 0.0;
   out_7685081031100061070[29] = 0.0;
   out_7685081031100061070[30] = 1.0;
   out_7685081031100061070[31] = 0.0;
   out_7685081031100061070[32] = 0.0;
   out_7685081031100061070[33] = 0.0;
   out_7685081031100061070[34] = 0.0;
   out_7685081031100061070[35] = 0.0;
   out_7685081031100061070[36] = 0.0;
   out_7685081031100061070[37] = 0.0;
   out_7685081031100061070[38] = 0.0;
   out_7685081031100061070[39] = 0.0;
   out_7685081031100061070[40] = 1.0;
   out_7685081031100061070[41] = 0.0;
   out_7685081031100061070[42] = 0.0;
   out_7685081031100061070[43] = 0.0;
   out_7685081031100061070[44] = 0.0;
   out_7685081031100061070[45] = 0.0;
   out_7685081031100061070[46] = 0.0;
   out_7685081031100061070[47] = 0.0;
   out_7685081031100061070[48] = 0.0;
   out_7685081031100061070[49] = 0.0;
   out_7685081031100061070[50] = 1.0;
   out_7685081031100061070[51] = 0.0;
   out_7685081031100061070[52] = 0.0;
   out_7685081031100061070[53] = 0.0;
   out_7685081031100061070[54] = 0.0;
   out_7685081031100061070[55] = 0.0;
   out_7685081031100061070[56] = 0.0;
   out_7685081031100061070[57] = 0.0;
   out_7685081031100061070[58] = 0.0;
   out_7685081031100061070[59] = 0.0;
   out_7685081031100061070[60] = 1.0;
   out_7685081031100061070[61] = 0.0;
   out_7685081031100061070[62] = 0.0;
   out_7685081031100061070[63] = 0.0;
   out_7685081031100061070[64] = 0.0;
   out_7685081031100061070[65] = 0.0;
   out_7685081031100061070[66] = 0.0;
   out_7685081031100061070[67] = 0.0;
   out_7685081031100061070[68] = 0.0;
   out_7685081031100061070[69] = 0.0;
   out_7685081031100061070[70] = 1.0;
   out_7685081031100061070[71] = 0.0;
   out_7685081031100061070[72] = 0.0;
   out_7685081031100061070[73] = 0.0;
   out_7685081031100061070[74] = 0.0;
   out_7685081031100061070[75] = 0.0;
   out_7685081031100061070[76] = 0.0;
   out_7685081031100061070[77] = 0.0;
   out_7685081031100061070[78] = 0.0;
   out_7685081031100061070[79] = 0.0;
   out_7685081031100061070[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6817432226726583046) {
   out_6817432226726583046[0] = state[0];
   out_6817432226726583046[1] = state[1];
   out_6817432226726583046[2] = state[2];
   out_6817432226726583046[3] = state[3];
   out_6817432226726583046[4] = state[4];
   out_6817432226726583046[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6817432226726583046[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6817432226726583046[7] = state[7];
   out_6817432226726583046[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5439972572798473920) {
   out_5439972572798473920[0] = 1;
   out_5439972572798473920[1] = 0;
   out_5439972572798473920[2] = 0;
   out_5439972572798473920[3] = 0;
   out_5439972572798473920[4] = 0;
   out_5439972572798473920[5] = 0;
   out_5439972572798473920[6] = 0;
   out_5439972572798473920[7] = 0;
   out_5439972572798473920[8] = 0;
   out_5439972572798473920[9] = 0;
   out_5439972572798473920[10] = 1;
   out_5439972572798473920[11] = 0;
   out_5439972572798473920[12] = 0;
   out_5439972572798473920[13] = 0;
   out_5439972572798473920[14] = 0;
   out_5439972572798473920[15] = 0;
   out_5439972572798473920[16] = 0;
   out_5439972572798473920[17] = 0;
   out_5439972572798473920[18] = 0;
   out_5439972572798473920[19] = 0;
   out_5439972572798473920[20] = 1;
   out_5439972572798473920[21] = 0;
   out_5439972572798473920[22] = 0;
   out_5439972572798473920[23] = 0;
   out_5439972572798473920[24] = 0;
   out_5439972572798473920[25] = 0;
   out_5439972572798473920[26] = 0;
   out_5439972572798473920[27] = 0;
   out_5439972572798473920[28] = 0;
   out_5439972572798473920[29] = 0;
   out_5439972572798473920[30] = 1;
   out_5439972572798473920[31] = 0;
   out_5439972572798473920[32] = 0;
   out_5439972572798473920[33] = 0;
   out_5439972572798473920[34] = 0;
   out_5439972572798473920[35] = 0;
   out_5439972572798473920[36] = 0;
   out_5439972572798473920[37] = 0;
   out_5439972572798473920[38] = 0;
   out_5439972572798473920[39] = 0;
   out_5439972572798473920[40] = 1;
   out_5439972572798473920[41] = 0;
   out_5439972572798473920[42] = 0;
   out_5439972572798473920[43] = 0;
   out_5439972572798473920[44] = 0;
   out_5439972572798473920[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5439972572798473920[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5439972572798473920[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5439972572798473920[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5439972572798473920[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5439972572798473920[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5439972572798473920[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5439972572798473920[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5439972572798473920[53] = -9.8100000000000005*dt;
   out_5439972572798473920[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5439972572798473920[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5439972572798473920[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5439972572798473920[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5439972572798473920[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5439972572798473920[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5439972572798473920[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5439972572798473920[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5439972572798473920[62] = 0;
   out_5439972572798473920[63] = 0;
   out_5439972572798473920[64] = 0;
   out_5439972572798473920[65] = 0;
   out_5439972572798473920[66] = 0;
   out_5439972572798473920[67] = 0;
   out_5439972572798473920[68] = 0;
   out_5439972572798473920[69] = 0;
   out_5439972572798473920[70] = 1;
   out_5439972572798473920[71] = 0;
   out_5439972572798473920[72] = 0;
   out_5439972572798473920[73] = 0;
   out_5439972572798473920[74] = 0;
   out_5439972572798473920[75] = 0;
   out_5439972572798473920[76] = 0;
   out_5439972572798473920[77] = 0;
   out_5439972572798473920[78] = 0;
   out_5439972572798473920[79] = 0;
   out_5439972572798473920[80] = 1;
}
void h_25(double *state, double *unused, double *out_8501500738727009471) {
   out_8501500738727009471[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8190415473300357782) {
   out_8190415473300357782[0] = 0;
   out_8190415473300357782[1] = 0;
   out_8190415473300357782[2] = 0;
   out_8190415473300357782[3] = 0;
   out_8190415473300357782[4] = 0;
   out_8190415473300357782[5] = 0;
   out_8190415473300357782[6] = 1;
   out_8190415473300357782[7] = 0;
   out_8190415473300357782[8] = 0;
}
void h_24(double *state, double *unused, double *out_7993481566605781117) {
   out_7993481566605781117[0] = state[4];
   out_7993481566605781117[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5146098263296009590) {
   out_5146098263296009590[0] = 0;
   out_5146098263296009590[1] = 0;
   out_5146098263296009590[2] = 0;
   out_5146098263296009590[3] = 0;
   out_5146098263296009590[4] = 1;
   out_5146098263296009590[5] = 0;
   out_5146098263296009590[6] = 0;
   out_5146098263296009590[7] = 0;
   out_5146098263296009590[8] = 0;
   out_5146098263296009590[9] = 0;
   out_5146098263296009590[10] = 0;
   out_5146098263296009590[11] = 0;
   out_5146098263296009590[12] = 0;
   out_5146098263296009590[13] = 0;
   out_5146098263296009590[14] = 1;
   out_5146098263296009590[15] = 0;
   out_5146098263296009590[16] = 0;
   out_5146098263296009590[17] = 0;
}
void h_30(double *state, double *unused, double *out_8776694801011515360) {
   out_8776694801011515360[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8061076526157117712) {
   out_8061076526157117712[0] = 0;
   out_8061076526157117712[1] = 0;
   out_8061076526157117712[2] = 0;
   out_8061076526157117712[3] = 0;
   out_8061076526157117712[4] = 1;
   out_8061076526157117712[5] = 0;
   out_8061076526157117712[6] = 0;
   out_8061076526157117712[7] = 0;
   out_8061076526157117712[8] = 0;
}
void h_26(double *state, double *unused, double *out_7296766696437168400) {
   out_7296766696437168400[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4448912154426301558) {
   out_4448912154426301558[0] = 0;
   out_4448912154426301558[1] = 0;
   out_4448912154426301558[2] = 0;
   out_4448912154426301558[3] = 0;
   out_4448912154426301558[4] = 0;
   out_4448912154426301558[5] = 0;
   out_4448912154426301558[6] = 0;
   out_4448912154426301558[7] = 1;
   out_4448912154426301558[8] = 0;
}
void h_27(double *state, double *unused, double *out_7237333786733854977) {
   out_7237333786733854977[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5886313214356692801) {
   out_5886313214356692801[0] = 0;
   out_5886313214356692801[1] = 0;
   out_5886313214356692801[2] = 0;
   out_5886313214356692801[3] = 1;
   out_5886313214356692801[4] = 0;
   out_5886313214356692801[5] = 0;
   out_5886313214356692801[6] = 0;
   out_5886313214356692801[7] = 0;
   out_5886313214356692801[8] = 0;
}
void h_29(double *state, double *unused, double *out_1081886590893194848) {
   out_1081886590893194848[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8571307870471509896) {
   out_8571307870471509896[0] = 0;
   out_8571307870471509896[1] = 1;
   out_8571307870471509896[2] = 0;
   out_8571307870471509896[3] = 0;
   out_8571307870471509896[4] = 0;
   out_8571307870471509896[5] = 0;
   out_8571307870471509896[6] = 0;
   out_8571307870471509896[7] = 0;
   out_8571307870471509896[8] = 0;
}
void h_28(double *state, double *unused, double *out_6634017902057377460) {
   out_6634017902057377460[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6136580759052468019) {
   out_6136580759052468019[0] = 1;
   out_6136580759052468019[1] = 0;
   out_6136580759052468019[2] = 0;
   out_6136580759052468019[3] = 0;
   out_6136580759052468019[4] = 0;
   out_6136580759052468019[5] = 0;
   out_6136580759052468019[6] = 0;
   out_6136580759052468019[7] = 0;
   out_6136580759052468019[8] = 0;
}
void h_31(double *state, double *unused, double *out_8658687407078138616) {
   out_8658687407078138616[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8221061435177318210) {
   out_8221061435177318210[0] = 0;
   out_8221061435177318210[1] = 0;
   out_8221061435177318210[2] = 0;
   out_8221061435177318210[3] = 0;
   out_8221061435177318210[4] = 0;
   out_8221061435177318210[5] = 0;
   out_8221061435177318210[6] = 0;
   out_8221061435177318210[7] = 0;
   out_8221061435177318210[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8558441916270761648) {
  err_fun(nom_x, delta_x, out_8558441916270761648);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9137456234820429023) {
  inv_err_fun(nom_x, true_x, out_9137456234820429023);
}
void car_H_mod_fun(double *state, double *out_7685081031100061070) {
  H_mod_fun(state, out_7685081031100061070);
}
void car_f_fun(double *state, double dt, double *out_6817432226726583046) {
  f_fun(state,  dt, out_6817432226726583046);
}
void car_F_fun(double *state, double dt, double *out_5439972572798473920) {
  F_fun(state,  dt, out_5439972572798473920);
}
void car_h_25(double *state, double *unused, double *out_8501500738727009471) {
  h_25(state, unused, out_8501500738727009471);
}
void car_H_25(double *state, double *unused, double *out_8190415473300357782) {
  H_25(state, unused, out_8190415473300357782);
}
void car_h_24(double *state, double *unused, double *out_7993481566605781117) {
  h_24(state, unused, out_7993481566605781117);
}
void car_H_24(double *state, double *unused, double *out_5146098263296009590) {
  H_24(state, unused, out_5146098263296009590);
}
void car_h_30(double *state, double *unused, double *out_8776694801011515360) {
  h_30(state, unused, out_8776694801011515360);
}
void car_H_30(double *state, double *unused, double *out_8061076526157117712) {
  H_30(state, unused, out_8061076526157117712);
}
void car_h_26(double *state, double *unused, double *out_7296766696437168400) {
  h_26(state, unused, out_7296766696437168400);
}
void car_H_26(double *state, double *unused, double *out_4448912154426301558) {
  H_26(state, unused, out_4448912154426301558);
}
void car_h_27(double *state, double *unused, double *out_7237333786733854977) {
  h_27(state, unused, out_7237333786733854977);
}
void car_H_27(double *state, double *unused, double *out_5886313214356692801) {
  H_27(state, unused, out_5886313214356692801);
}
void car_h_29(double *state, double *unused, double *out_1081886590893194848) {
  h_29(state, unused, out_1081886590893194848);
}
void car_H_29(double *state, double *unused, double *out_8571307870471509896) {
  H_29(state, unused, out_8571307870471509896);
}
void car_h_28(double *state, double *unused, double *out_6634017902057377460) {
  h_28(state, unused, out_6634017902057377460);
}
void car_H_28(double *state, double *unused, double *out_6136580759052468019) {
  H_28(state, unused, out_6136580759052468019);
}
void car_h_31(double *state, double *unused, double *out_8658687407078138616) {
  h_31(state, unused, out_8658687407078138616);
}
void car_H_31(double *state, double *unused, double *out_8221061435177318210) {
  H_31(state, unused, out_8221061435177318210);
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
