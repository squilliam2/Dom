#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5169544621376104769) {
   out_5169544621376104769[0] = delta_x[0] + nom_x[0];
   out_5169544621376104769[1] = delta_x[1] + nom_x[1];
   out_5169544621376104769[2] = delta_x[2] + nom_x[2];
   out_5169544621376104769[3] = delta_x[3] + nom_x[3];
   out_5169544621376104769[4] = delta_x[4] + nom_x[4];
   out_5169544621376104769[5] = delta_x[5] + nom_x[5];
   out_5169544621376104769[6] = delta_x[6] + nom_x[6];
   out_5169544621376104769[7] = delta_x[7] + nom_x[7];
   out_5169544621376104769[8] = delta_x[8] + nom_x[8];
   out_5169544621376104769[9] = delta_x[9] + nom_x[9];
   out_5169544621376104769[10] = delta_x[10] + nom_x[10];
   out_5169544621376104769[11] = delta_x[11] + nom_x[11];
   out_5169544621376104769[12] = delta_x[12] + nom_x[12];
   out_5169544621376104769[13] = delta_x[13] + nom_x[13];
   out_5169544621376104769[14] = delta_x[14] + nom_x[14];
   out_5169544621376104769[15] = delta_x[15] + nom_x[15];
   out_5169544621376104769[16] = delta_x[16] + nom_x[16];
   out_5169544621376104769[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5560919447530739345) {
   out_5560919447530739345[0] = -nom_x[0] + true_x[0];
   out_5560919447530739345[1] = -nom_x[1] + true_x[1];
   out_5560919447530739345[2] = -nom_x[2] + true_x[2];
   out_5560919447530739345[3] = -nom_x[3] + true_x[3];
   out_5560919447530739345[4] = -nom_x[4] + true_x[4];
   out_5560919447530739345[5] = -nom_x[5] + true_x[5];
   out_5560919447530739345[6] = -nom_x[6] + true_x[6];
   out_5560919447530739345[7] = -nom_x[7] + true_x[7];
   out_5560919447530739345[8] = -nom_x[8] + true_x[8];
   out_5560919447530739345[9] = -nom_x[9] + true_x[9];
   out_5560919447530739345[10] = -nom_x[10] + true_x[10];
   out_5560919447530739345[11] = -nom_x[11] + true_x[11];
   out_5560919447530739345[12] = -nom_x[12] + true_x[12];
   out_5560919447530739345[13] = -nom_x[13] + true_x[13];
   out_5560919447530739345[14] = -nom_x[14] + true_x[14];
   out_5560919447530739345[15] = -nom_x[15] + true_x[15];
   out_5560919447530739345[16] = -nom_x[16] + true_x[16];
   out_5560919447530739345[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8932661143090135832) {
   out_8932661143090135832[0] = 1.0;
   out_8932661143090135832[1] = 0.0;
   out_8932661143090135832[2] = 0.0;
   out_8932661143090135832[3] = 0.0;
   out_8932661143090135832[4] = 0.0;
   out_8932661143090135832[5] = 0.0;
   out_8932661143090135832[6] = 0.0;
   out_8932661143090135832[7] = 0.0;
   out_8932661143090135832[8] = 0.0;
   out_8932661143090135832[9] = 0.0;
   out_8932661143090135832[10] = 0.0;
   out_8932661143090135832[11] = 0.0;
   out_8932661143090135832[12] = 0.0;
   out_8932661143090135832[13] = 0.0;
   out_8932661143090135832[14] = 0.0;
   out_8932661143090135832[15] = 0.0;
   out_8932661143090135832[16] = 0.0;
   out_8932661143090135832[17] = 0.0;
   out_8932661143090135832[18] = 0.0;
   out_8932661143090135832[19] = 1.0;
   out_8932661143090135832[20] = 0.0;
   out_8932661143090135832[21] = 0.0;
   out_8932661143090135832[22] = 0.0;
   out_8932661143090135832[23] = 0.0;
   out_8932661143090135832[24] = 0.0;
   out_8932661143090135832[25] = 0.0;
   out_8932661143090135832[26] = 0.0;
   out_8932661143090135832[27] = 0.0;
   out_8932661143090135832[28] = 0.0;
   out_8932661143090135832[29] = 0.0;
   out_8932661143090135832[30] = 0.0;
   out_8932661143090135832[31] = 0.0;
   out_8932661143090135832[32] = 0.0;
   out_8932661143090135832[33] = 0.0;
   out_8932661143090135832[34] = 0.0;
   out_8932661143090135832[35] = 0.0;
   out_8932661143090135832[36] = 0.0;
   out_8932661143090135832[37] = 0.0;
   out_8932661143090135832[38] = 1.0;
   out_8932661143090135832[39] = 0.0;
   out_8932661143090135832[40] = 0.0;
   out_8932661143090135832[41] = 0.0;
   out_8932661143090135832[42] = 0.0;
   out_8932661143090135832[43] = 0.0;
   out_8932661143090135832[44] = 0.0;
   out_8932661143090135832[45] = 0.0;
   out_8932661143090135832[46] = 0.0;
   out_8932661143090135832[47] = 0.0;
   out_8932661143090135832[48] = 0.0;
   out_8932661143090135832[49] = 0.0;
   out_8932661143090135832[50] = 0.0;
   out_8932661143090135832[51] = 0.0;
   out_8932661143090135832[52] = 0.0;
   out_8932661143090135832[53] = 0.0;
   out_8932661143090135832[54] = 0.0;
   out_8932661143090135832[55] = 0.0;
   out_8932661143090135832[56] = 0.0;
   out_8932661143090135832[57] = 1.0;
   out_8932661143090135832[58] = 0.0;
   out_8932661143090135832[59] = 0.0;
   out_8932661143090135832[60] = 0.0;
   out_8932661143090135832[61] = 0.0;
   out_8932661143090135832[62] = 0.0;
   out_8932661143090135832[63] = 0.0;
   out_8932661143090135832[64] = 0.0;
   out_8932661143090135832[65] = 0.0;
   out_8932661143090135832[66] = 0.0;
   out_8932661143090135832[67] = 0.0;
   out_8932661143090135832[68] = 0.0;
   out_8932661143090135832[69] = 0.0;
   out_8932661143090135832[70] = 0.0;
   out_8932661143090135832[71] = 0.0;
   out_8932661143090135832[72] = 0.0;
   out_8932661143090135832[73] = 0.0;
   out_8932661143090135832[74] = 0.0;
   out_8932661143090135832[75] = 0.0;
   out_8932661143090135832[76] = 1.0;
   out_8932661143090135832[77] = 0.0;
   out_8932661143090135832[78] = 0.0;
   out_8932661143090135832[79] = 0.0;
   out_8932661143090135832[80] = 0.0;
   out_8932661143090135832[81] = 0.0;
   out_8932661143090135832[82] = 0.0;
   out_8932661143090135832[83] = 0.0;
   out_8932661143090135832[84] = 0.0;
   out_8932661143090135832[85] = 0.0;
   out_8932661143090135832[86] = 0.0;
   out_8932661143090135832[87] = 0.0;
   out_8932661143090135832[88] = 0.0;
   out_8932661143090135832[89] = 0.0;
   out_8932661143090135832[90] = 0.0;
   out_8932661143090135832[91] = 0.0;
   out_8932661143090135832[92] = 0.0;
   out_8932661143090135832[93] = 0.0;
   out_8932661143090135832[94] = 0.0;
   out_8932661143090135832[95] = 1.0;
   out_8932661143090135832[96] = 0.0;
   out_8932661143090135832[97] = 0.0;
   out_8932661143090135832[98] = 0.0;
   out_8932661143090135832[99] = 0.0;
   out_8932661143090135832[100] = 0.0;
   out_8932661143090135832[101] = 0.0;
   out_8932661143090135832[102] = 0.0;
   out_8932661143090135832[103] = 0.0;
   out_8932661143090135832[104] = 0.0;
   out_8932661143090135832[105] = 0.0;
   out_8932661143090135832[106] = 0.0;
   out_8932661143090135832[107] = 0.0;
   out_8932661143090135832[108] = 0.0;
   out_8932661143090135832[109] = 0.0;
   out_8932661143090135832[110] = 0.0;
   out_8932661143090135832[111] = 0.0;
   out_8932661143090135832[112] = 0.0;
   out_8932661143090135832[113] = 0.0;
   out_8932661143090135832[114] = 1.0;
   out_8932661143090135832[115] = 0.0;
   out_8932661143090135832[116] = 0.0;
   out_8932661143090135832[117] = 0.0;
   out_8932661143090135832[118] = 0.0;
   out_8932661143090135832[119] = 0.0;
   out_8932661143090135832[120] = 0.0;
   out_8932661143090135832[121] = 0.0;
   out_8932661143090135832[122] = 0.0;
   out_8932661143090135832[123] = 0.0;
   out_8932661143090135832[124] = 0.0;
   out_8932661143090135832[125] = 0.0;
   out_8932661143090135832[126] = 0.0;
   out_8932661143090135832[127] = 0.0;
   out_8932661143090135832[128] = 0.0;
   out_8932661143090135832[129] = 0.0;
   out_8932661143090135832[130] = 0.0;
   out_8932661143090135832[131] = 0.0;
   out_8932661143090135832[132] = 0.0;
   out_8932661143090135832[133] = 1.0;
   out_8932661143090135832[134] = 0.0;
   out_8932661143090135832[135] = 0.0;
   out_8932661143090135832[136] = 0.0;
   out_8932661143090135832[137] = 0.0;
   out_8932661143090135832[138] = 0.0;
   out_8932661143090135832[139] = 0.0;
   out_8932661143090135832[140] = 0.0;
   out_8932661143090135832[141] = 0.0;
   out_8932661143090135832[142] = 0.0;
   out_8932661143090135832[143] = 0.0;
   out_8932661143090135832[144] = 0.0;
   out_8932661143090135832[145] = 0.0;
   out_8932661143090135832[146] = 0.0;
   out_8932661143090135832[147] = 0.0;
   out_8932661143090135832[148] = 0.0;
   out_8932661143090135832[149] = 0.0;
   out_8932661143090135832[150] = 0.0;
   out_8932661143090135832[151] = 0.0;
   out_8932661143090135832[152] = 1.0;
   out_8932661143090135832[153] = 0.0;
   out_8932661143090135832[154] = 0.0;
   out_8932661143090135832[155] = 0.0;
   out_8932661143090135832[156] = 0.0;
   out_8932661143090135832[157] = 0.0;
   out_8932661143090135832[158] = 0.0;
   out_8932661143090135832[159] = 0.0;
   out_8932661143090135832[160] = 0.0;
   out_8932661143090135832[161] = 0.0;
   out_8932661143090135832[162] = 0.0;
   out_8932661143090135832[163] = 0.0;
   out_8932661143090135832[164] = 0.0;
   out_8932661143090135832[165] = 0.0;
   out_8932661143090135832[166] = 0.0;
   out_8932661143090135832[167] = 0.0;
   out_8932661143090135832[168] = 0.0;
   out_8932661143090135832[169] = 0.0;
   out_8932661143090135832[170] = 0.0;
   out_8932661143090135832[171] = 1.0;
   out_8932661143090135832[172] = 0.0;
   out_8932661143090135832[173] = 0.0;
   out_8932661143090135832[174] = 0.0;
   out_8932661143090135832[175] = 0.0;
   out_8932661143090135832[176] = 0.0;
   out_8932661143090135832[177] = 0.0;
   out_8932661143090135832[178] = 0.0;
   out_8932661143090135832[179] = 0.0;
   out_8932661143090135832[180] = 0.0;
   out_8932661143090135832[181] = 0.0;
   out_8932661143090135832[182] = 0.0;
   out_8932661143090135832[183] = 0.0;
   out_8932661143090135832[184] = 0.0;
   out_8932661143090135832[185] = 0.0;
   out_8932661143090135832[186] = 0.0;
   out_8932661143090135832[187] = 0.0;
   out_8932661143090135832[188] = 0.0;
   out_8932661143090135832[189] = 0.0;
   out_8932661143090135832[190] = 1.0;
   out_8932661143090135832[191] = 0.0;
   out_8932661143090135832[192] = 0.0;
   out_8932661143090135832[193] = 0.0;
   out_8932661143090135832[194] = 0.0;
   out_8932661143090135832[195] = 0.0;
   out_8932661143090135832[196] = 0.0;
   out_8932661143090135832[197] = 0.0;
   out_8932661143090135832[198] = 0.0;
   out_8932661143090135832[199] = 0.0;
   out_8932661143090135832[200] = 0.0;
   out_8932661143090135832[201] = 0.0;
   out_8932661143090135832[202] = 0.0;
   out_8932661143090135832[203] = 0.0;
   out_8932661143090135832[204] = 0.0;
   out_8932661143090135832[205] = 0.0;
   out_8932661143090135832[206] = 0.0;
   out_8932661143090135832[207] = 0.0;
   out_8932661143090135832[208] = 0.0;
   out_8932661143090135832[209] = 1.0;
   out_8932661143090135832[210] = 0.0;
   out_8932661143090135832[211] = 0.0;
   out_8932661143090135832[212] = 0.0;
   out_8932661143090135832[213] = 0.0;
   out_8932661143090135832[214] = 0.0;
   out_8932661143090135832[215] = 0.0;
   out_8932661143090135832[216] = 0.0;
   out_8932661143090135832[217] = 0.0;
   out_8932661143090135832[218] = 0.0;
   out_8932661143090135832[219] = 0.0;
   out_8932661143090135832[220] = 0.0;
   out_8932661143090135832[221] = 0.0;
   out_8932661143090135832[222] = 0.0;
   out_8932661143090135832[223] = 0.0;
   out_8932661143090135832[224] = 0.0;
   out_8932661143090135832[225] = 0.0;
   out_8932661143090135832[226] = 0.0;
   out_8932661143090135832[227] = 0.0;
   out_8932661143090135832[228] = 1.0;
   out_8932661143090135832[229] = 0.0;
   out_8932661143090135832[230] = 0.0;
   out_8932661143090135832[231] = 0.0;
   out_8932661143090135832[232] = 0.0;
   out_8932661143090135832[233] = 0.0;
   out_8932661143090135832[234] = 0.0;
   out_8932661143090135832[235] = 0.0;
   out_8932661143090135832[236] = 0.0;
   out_8932661143090135832[237] = 0.0;
   out_8932661143090135832[238] = 0.0;
   out_8932661143090135832[239] = 0.0;
   out_8932661143090135832[240] = 0.0;
   out_8932661143090135832[241] = 0.0;
   out_8932661143090135832[242] = 0.0;
   out_8932661143090135832[243] = 0.0;
   out_8932661143090135832[244] = 0.0;
   out_8932661143090135832[245] = 0.0;
   out_8932661143090135832[246] = 0.0;
   out_8932661143090135832[247] = 1.0;
   out_8932661143090135832[248] = 0.0;
   out_8932661143090135832[249] = 0.0;
   out_8932661143090135832[250] = 0.0;
   out_8932661143090135832[251] = 0.0;
   out_8932661143090135832[252] = 0.0;
   out_8932661143090135832[253] = 0.0;
   out_8932661143090135832[254] = 0.0;
   out_8932661143090135832[255] = 0.0;
   out_8932661143090135832[256] = 0.0;
   out_8932661143090135832[257] = 0.0;
   out_8932661143090135832[258] = 0.0;
   out_8932661143090135832[259] = 0.0;
   out_8932661143090135832[260] = 0.0;
   out_8932661143090135832[261] = 0.0;
   out_8932661143090135832[262] = 0.0;
   out_8932661143090135832[263] = 0.0;
   out_8932661143090135832[264] = 0.0;
   out_8932661143090135832[265] = 0.0;
   out_8932661143090135832[266] = 1.0;
   out_8932661143090135832[267] = 0.0;
   out_8932661143090135832[268] = 0.0;
   out_8932661143090135832[269] = 0.0;
   out_8932661143090135832[270] = 0.0;
   out_8932661143090135832[271] = 0.0;
   out_8932661143090135832[272] = 0.0;
   out_8932661143090135832[273] = 0.0;
   out_8932661143090135832[274] = 0.0;
   out_8932661143090135832[275] = 0.0;
   out_8932661143090135832[276] = 0.0;
   out_8932661143090135832[277] = 0.0;
   out_8932661143090135832[278] = 0.0;
   out_8932661143090135832[279] = 0.0;
   out_8932661143090135832[280] = 0.0;
   out_8932661143090135832[281] = 0.0;
   out_8932661143090135832[282] = 0.0;
   out_8932661143090135832[283] = 0.0;
   out_8932661143090135832[284] = 0.0;
   out_8932661143090135832[285] = 1.0;
   out_8932661143090135832[286] = 0.0;
   out_8932661143090135832[287] = 0.0;
   out_8932661143090135832[288] = 0.0;
   out_8932661143090135832[289] = 0.0;
   out_8932661143090135832[290] = 0.0;
   out_8932661143090135832[291] = 0.0;
   out_8932661143090135832[292] = 0.0;
   out_8932661143090135832[293] = 0.0;
   out_8932661143090135832[294] = 0.0;
   out_8932661143090135832[295] = 0.0;
   out_8932661143090135832[296] = 0.0;
   out_8932661143090135832[297] = 0.0;
   out_8932661143090135832[298] = 0.0;
   out_8932661143090135832[299] = 0.0;
   out_8932661143090135832[300] = 0.0;
   out_8932661143090135832[301] = 0.0;
   out_8932661143090135832[302] = 0.0;
   out_8932661143090135832[303] = 0.0;
   out_8932661143090135832[304] = 1.0;
   out_8932661143090135832[305] = 0.0;
   out_8932661143090135832[306] = 0.0;
   out_8932661143090135832[307] = 0.0;
   out_8932661143090135832[308] = 0.0;
   out_8932661143090135832[309] = 0.0;
   out_8932661143090135832[310] = 0.0;
   out_8932661143090135832[311] = 0.0;
   out_8932661143090135832[312] = 0.0;
   out_8932661143090135832[313] = 0.0;
   out_8932661143090135832[314] = 0.0;
   out_8932661143090135832[315] = 0.0;
   out_8932661143090135832[316] = 0.0;
   out_8932661143090135832[317] = 0.0;
   out_8932661143090135832[318] = 0.0;
   out_8932661143090135832[319] = 0.0;
   out_8932661143090135832[320] = 0.0;
   out_8932661143090135832[321] = 0.0;
   out_8932661143090135832[322] = 0.0;
   out_8932661143090135832[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3609843023403364566) {
   out_3609843023403364566[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3609843023403364566[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3609843023403364566[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3609843023403364566[3] = dt*state[12] + state[3];
   out_3609843023403364566[4] = dt*state[13] + state[4];
   out_3609843023403364566[5] = dt*state[14] + state[5];
   out_3609843023403364566[6] = state[6];
   out_3609843023403364566[7] = state[7];
   out_3609843023403364566[8] = state[8];
   out_3609843023403364566[9] = state[9];
   out_3609843023403364566[10] = state[10];
   out_3609843023403364566[11] = state[11];
   out_3609843023403364566[12] = state[12];
   out_3609843023403364566[13] = state[13];
   out_3609843023403364566[14] = state[14];
   out_3609843023403364566[15] = state[15];
   out_3609843023403364566[16] = state[16];
   out_3609843023403364566[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8950799816554095649) {
   out_8950799816554095649[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8950799816554095649[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8950799816554095649[2] = 0;
   out_8950799816554095649[3] = 0;
   out_8950799816554095649[4] = 0;
   out_8950799816554095649[5] = 0;
   out_8950799816554095649[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8950799816554095649[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8950799816554095649[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8950799816554095649[9] = 0;
   out_8950799816554095649[10] = 0;
   out_8950799816554095649[11] = 0;
   out_8950799816554095649[12] = 0;
   out_8950799816554095649[13] = 0;
   out_8950799816554095649[14] = 0;
   out_8950799816554095649[15] = 0;
   out_8950799816554095649[16] = 0;
   out_8950799816554095649[17] = 0;
   out_8950799816554095649[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8950799816554095649[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8950799816554095649[20] = 0;
   out_8950799816554095649[21] = 0;
   out_8950799816554095649[22] = 0;
   out_8950799816554095649[23] = 0;
   out_8950799816554095649[24] = 0;
   out_8950799816554095649[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8950799816554095649[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8950799816554095649[27] = 0;
   out_8950799816554095649[28] = 0;
   out_8950799816554095649[29] = 0;
   out_8950799816554095649[30] = 0;
   out_8950799816554095649[31] = 0;
   out_8950799816554095649[32] = 0;
   out_8950799816554095649[33] = 0;
   out_8950799816554095649[34] = 0;
   out_8950799816554095649[35] = 0;
   out_8950799816554095649[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8950799816554095649[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8950799816554095649[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8950799816554095649[39] = 0;
   out_8950799816554095649[40] = 0;
   out_8950799816554095649[41] = 0;
   out_8950799816554095649[42] = 0;
   out_8950799816554095649[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8950799816554095649[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8950799816554095649[45] = 0;
   out_8950799816554095649[46] = 0;
   out_8950799816554095649[47] = 0;
   out_8950799816554095649[48] = 0;
   out_8950799816554095649[49] = 0;
   out_8950799816554095649[50] = 0;
   out_8950799816554095649[51] = 0;
   out_8950799816554095649[52] = 0;
   out_8950799816554095649[53] = 0;
   out_8950799816554095649[54] = 0;
   out_8950799816554095649[55] = 0;
   out_8950799816554095649[56] = 0;
   out_8950799816554095649[57] = 1;
   out_8950799816554095649[58] = 0;
   out_8950799816554095649[59] = 0;
   out_8950799816554095649[60] = 0;
   out_8950799816554095649[61] = 0;
   out_8950799816554095649[62] = 0;
   out_8950799816554095649[63] = 0;
   out_8950799816554095649[64] = 0;
   out_8950799816554095649[65] = 0;
   out_8950799816554095649[66] = dt;
   out_8950799816554095649[67] = 0;
   out_8950799816554095649[68] = 0;
   out_8950799816554095649[69] = 0;
   out_8950799816554095649[70] = 0;
   out_8950799816554095649[71] = 0;
   out_8950799816554095649[72] = 0;
   out_8950799816554095649[73] = 0;
   out_8950799816554095649[74] = 0;
   out_8950799816554095649[75] = 0;
   out_8950799816554095649[76] = 1;
   out_8950799816554095649[77] = 0;
   out_8950799816554095649[78] = 0;
   out_8950799816554095649[79] = 0;
   out_8950799816554095649[80] = 0;
   out_8950799816554095649[81] = 0;
   out_8950799816554095649[82] = 0;
   out_8950799816554095649[83] = 0;
   out_8950799816554095649[84] = 0;
   out_8950799816554095649[85] = dt;
   out_8950799816554095649[86] = 0;
   out_8950799816554095649[87] = 0;
   out_8950799816554095649[88] = 0;
   out_8950799816554095649[89] = 0;
   out_8950799816554095649[90] = 0;
   out_8950799816554095649[91] = 0;
   out_8950799816554095649[92] = 0;
   out_8950799816554095649[93] = 0;
   out_8950799816554095649[94] = 0;
   out_8950799816554095649[95] = 1;
   out_8950799816554095649[96] = 0;
   out_8950799816554095649[97] = 0;
   out_8950799816554095649[98] = 0;
   out_8950799816554095649[99] = 0;
   out_8950799816554095649[100] = 0;
   out_8950799816554095649[101] = 0;
   out_8950799816554095649[102] = 0;
   out_8950799816554095649[103] = 0;
   out_8950799816554095649[104] = dt;
   out_8950799816554095649[105] = 0;
   out_8950799816554095649[106] = 0;
   out_8950799816554095649[107] = 0;
   out_8950799816554095649[108] = 0;
   out_8950799816554095649[109] = 0;
   out_8950799816554095649[110] = 0;
   out_8950799816554095649[111] = 0;
   out_8950799816554095649[112] = 0;
   out_8950799816554095649[113] = 0;
   out_8950799816554095649[114] = 1;
   out_8950799816554095649[115] = 0;
   out_8950799816554095649[116] = 0;
   out_8950799816554095649[117] = 0;
   out_8950799816554095649[118] = 0;
   out_8950799816554095649[119] = 0;
   out_8950799816554095649[120] = 0;
   out_8950799816554095649[121] = 0;
   out_8950799816554095649[122] = 0;
   out_8950799816554095649[123] = 0;
   out_8950799816554095649[124] = 0;
   out_8950799816554095649[125] = 0;
   out_8950799816554095649[126] = 0;
   out_8950799816554095649[127] = 0;
   out_8950799816554095649[128] = 0;
   out_8950799816554095649[129] = 0;
   out_8950799816554095649[130] = 0;
   out_8950799816554095649[131] = 0;
   out_8950799816554095649[132] = 0;
   out_8950799816554095649[133] = 1;
   out_8950799816554095649[134] = 0;
   out_8950799816554095649[135] = 0;
   out_8950799816554095649[136] = 0;
   out_8950799816554095649[137] = 0;
   out_8950799816554095649[138] = 0;
   out_8950799816554095649[139] = 0;
   out_8950799816554095649[140] = 0;
   out_8950799816554095649[141] = 0;
   out_8950799816554095649[142] = 0;
   out_8950799816554095649[143] = 0;
   out_8950799816554095649[144] = 0;
   out_8950799816554095649[145] = 0;
   out_8950799816554095649[146] = 0;
   out_8950799816554095649[147] = 0;
   out_8950799816554095649[148] = 0;
   out_8950799816554095649[149] = 0;
   out_8950799816554095649[150] = 0;
   out_8950799816554095649[151] = 0;
   out_8950799816554095649[152] = 1;
   out_8950799816554095649[153] = 0;
   out_8950799816554095649[154] = 0;
   out_8950799816554095649[155] = 0;
   out_8950799816554095649[156] = 0;
   out_8950799816554095649[157] = 0;
   out_8950799816554095649[158] = 0;
   out_8950799816554095649[159] = 0;
   out_8950799816554095649[160] = 0;
   out_8950799816554095649[161] = 0;
   out_8950799816554095649[162] = 0;
   out_8950799816554095649[163] = 0;
   out_8950799816554095649[164] = 0;
   out_8950799816554095649[165] = 0;
   out_8950799816554095649[166] = 0;
   out_8950799816554095649[167] = 0;
   out_8950799816554095649[168] = 0;
   out_8950799816554095649[169] = 0;
   out_8950799816554095649[170] = 0;
   out_8950799816554095649[171] = 1;
   out_8950799816554095649[172] = 0;
   out_8950799816554095649[173] = 0;
   out_8950799816554095649[174] = 0;
   out_8950799816554095649[175] = 0;
   out_8950799816554095649[176] = 0;
   out_8950799816554095649[177] = 0;
   out_8950799816554095649[178] = 0;
   out_8950799816554095649[179] = 0;
   out_8950799816554095649[180] = 0;
   out_8950799816554095649[181] = 0;
   out_8950799816554095649[182] = 0;
   out_8950799816554095649[183] = 0;
   out_8950799816554095649[184] = 0;
   out_8950799816554095649[185] = 0;
   out_8950799816554095649[186] = 0;
   out_8950799816554095649[187] = 0;
   out_8950799816554095649[188] = 0;
   out_8950799816554095649[189] = 0;
   out_8950799816554095649[190] = 1;
   out_8950799816554095649[191] = 0;
   out_8950799816554095649[192] = 0;
   out_8950799816554095649[193] = 0;
   out_8950799816554095649[194] = 0;
   out_8950799816554095649[195] = 0;
   out_8950799816554095649[196] = 0;
   out_8950799816554095649[197] = 0;
   out_8950799816554095649[198] = 0;
   out_8950799816554095649[199] = 0;
   out_8950799816554095649[200] = 0;
   out_8950799816554095649[201] = 0;
   out_8950799816554095649[202] = 0;
   out_8950799816554095649[203] = 0;
   out_8950799816554095649[204] = 0;
   out_8950799816554095649[205] = 0;
   out_8950799816554095649[206] = 0;
   out_8950799816554095649[207] = 0;
   out_8950799816554095649[208] = 0;
   out_8950799816554095649[209] = 1;
   out_8950799816554095649[210] = 0;
   out_8950799816554095649[211] = 0;
   out_8950799816554095649[212] = 0;
   out_8950799816554095649[213] = 0;
   out_8950799816554095649[214] = 0;
   out_8950799816554095649[215] = 0;
   out_8950799816554095649[216] = 0;
   out_8950799816554095649[217] = 0;
   out_8950799816554095649[218] = 0;
   out_8950799816554095649[219] = 0;
   out_8950799816554095649[220] = 0;
   out_8950799816554095649[221] = 0;
   out_8950799816554095649[222] = 0;
   out_8950799816554095649[223] = 0;
   out_8950799816554095649[224] = 0;
   out_8950799816554095649[225] = 0;
   out_8950799816554095649[226] = 0;
   out_8950799816554095649[227] = 0;
   out_8950799816554095649[228] = 1;
   out_8950799816554095649[229] = 0;
   out_8950799816554095649[230] = 0;
   out_8950799816554095649[231] = 0;
   out_8950799816554095649[232] = 0;
   out_8950799816554095649[233] = 0;
   out_8950799816554095649[234] = 0;
   out_8950799816554095649[235] = 0;
   out_8950799816554095649[236] = 0;
   out_8950799816554095649[237] = 0;
   out_8950799816554095649[238] = 0;
   out_8950799816554095649[239] = 0;
   out_8950799816554095649[240] = 0;
   out_8950799816554095649[241] = 0;
   out_8950799816554095649[242] = 0;
   out_8950799816554095649[243] = 0;
   out_8950799816554095649[244] = 0;
   out_8950799816554095649[245] = 0;
   out_8950799816554095649[246] = 0;
   out_8950799816554095649[247] = 1;
   out_8950799816554095649[248] = 0;
   out_8950799816554095649[249] = 0;
   out_8950799816554095649[250] = 0;
   out_8950799816554095649[251] = 0;
   out_8950799816554095649[252] = 0;
   out_8950799816554095649[253] = 0;
   out_8950799816554095649[254] = 0;
   out_8950799816554095649[255] = 0;
   out_8950799816554095649[256] = 0;
   out_8950799816554095649[257] = 0;
   out_8950799816554095649[258] = 0;
   out_8950799816554095649[259] = 0;
   out_8950799816554095649[260] = 0;
   out_8950799816554095649[261] = 0;
   out_8950799816554095649[262] = 0;
   out_8950799816554095649[263] = 0;
   out_8950799816554095649[264] = 0;
   out_8950799816554095649[265] = 0;
   out_8950799816554095649[266] = 1;
   out_8950799816554095649[267] = 0;
   out_8950799816554095649[268] = 0;
   out_8950799816554095649[269] = 0;
   out_8950799816554095649[270] = 0;
   out_8950799816554095649[271] = 0;
   out_8950799816554095649[272] = 0;
   out_8950799816554095649[273] = 0;
   out_8950799816554095649[274] = 0;
   out_8950799816554095649[275] = 0;
   out_8950799816554095649[276] = 0;
   out_8950799816554095649[277] = 0;
   out_8950799816554095649[278] = 0;
   out_8950799816554095649[279] = 0;
   out_8950799816554095649[280] = 0;
   out_8950799816554095649[281] = 0;
   out_8950799816554095649[282] = 0;
   out_8950799816554095649[283] = 0;
   out_8950799816554095649[284] = 0;
   out_8950799816554095649[285] = 1;
   out_8950799816554095649[286] = 0;
   out_8950799816554095649[287] = 0;
   out_8950799816554095649[288] = 0;
   out_8950799816554095649[289] = 0;
   out_8950799816554095649[290] = 0;
   out_8950799816554095649[291] = 0;
   out_8950799816554095649[292] = 0;
   out_8950799816554095649[293] = 0;
   out_8950799816554095649[294] = 0;
   out_8950799816554095649[295] = 0;
   out_8950799816554095649[296] = 0;
   out_8950799816554095649[297] = 0;
   out_8950799816554095649[298] = 0;
   out_8950799816554095649[299] = 0;
   out_8950799816554095649[300] = 0;
   out_8950799816554095649[301] = 0;
   out_8950799816554095649[302] = 0;
   out_8950799816554095649[303] = 0;
   out_8950799816554095649[304] = 1;
   out_8950799816554095649[305] = 0;
   out_8950799816554095649[306] = 0;
   out_8950799816554095649[307] = 0;
   out_8950799816554095649[308] = 0;
   out_8950799816554095649[309] = 0;
   out_8950799816554095649[310] = 0;
   out_8950799816554095649[311] = 0;
   out_8950799816554095649[312] = 0;
   out_8950799816554095649[313] = 0;
   out_8950799816554095649[314] = 0;
   out_8950799816554095649[315] = 0;
   out_8950799816554095649[316] = 0;
   out_8950799816554095649[317] = 0;
   out_8950799816554095649[318] = 0;
   out_8950799816554095649[319] = 0;
   out_8950799816554095649[320] = 0;
   out_8950799816554095649[321] = 0;
   out_8950799816554095649[322] = 0;
   out_8950799816554095649[323] = 1;
}
void h_4(double *state, double *unused, double *out_7061694870208984097) {
   out_7061694870208984097[0] = state[6] + state[9];
   out_7061694870208984097[1] = state[7] + state[10];
   out_7061694870208984097[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4465290511533350274) {
   out_4465290511533350274[0] = 0;
   out_4465290511533350274[1] = 0;
   out_4465290511533350274[2] = 0;
   out_4465290511533350274[3] = 0;
   out_4465290511533350274[4] = 0;
   out_4465290511533350274[5] = 0;
   out_4465290511533350274[6] = 1;
   out_4465290511533350274[7] = 0;
   out_4465290511533350274[8] = 0;
   out_4465290511533350274[9] = 1;
   out_4465290511533350274[10] = 0;
   out_4465290511533350274[11] = 0;
   out_4465290511533350274[12] = 0;
   out_4465290511533350274[13] = 0;
   out_4465290511533350274[14] = 0;
   out_4465290511533350274[15] = 0;
   out_4465290511533350274[16] = 0;
   out_4465290511533350274[17] = 0;
   out_4465290511533350274[18] = 0;
   out_4465290511533350274[19] = 0;
   out_4465290511533350274[20] = 0;
   out_4465290511533350274[21] = 0;
   out_4465290511533350274[22] = 0;
   out_4465290511533350274[23] = 0;
   out_4465290511533350274[24] = 0;
   out_4465290511533350274[25] = 1;
   out_4465290511533350274[26] = 0;
   out_4465290511533350274[27] = 0;
   out_4465290511533350274[28] = 1;
   out_4465290511533350274[29] = 0;
   out_4465290511533350274[30] = 0;
   out_4465290511533350274[31] = 0;
   out_4465290511533350274[32] = 0;
   out_4465290511533350274[33] = 0;
   out_4465290511533350274[34] = 0;
   out_4465290511533350274[35] = 0;
   out_4465290511533350274[36] = 0;
   out_4465290511533350274[37] = 0;
   out_4465290511533350274[38] = 0;
   out_4465290511533350274[39] = 0;
   out_4465290511533350274[40] = 0;
   out_4465290511533350274[41] = 0;
   out_4465290511533350274[42] = 0;
   out_4465290511533350274[43] = 0;
   out_4465290511533350274[44] = 1;
   out_4465290511533350274[45] = 0;
   out_4465290511533350274[46] = 0;
   out_4465290511533350274[47] = 1;
   out_4465290511533350274[48] = 0;
   out_4465290511533350274[49] = 0;
   out_4465290511533350274[50] = 0;
   out_4465290511533350274[51] = 0;
   out_4465290511533350274[52] = 0;
   out_4465290511533350274[53] = 0;
}
void h_10(double *state, double *unused, double *out_10860459686481955) {
   out_10860459686481955[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_10860459686481955[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_10860459686481955[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3271917644950253884) {
   out_3271917644950253884[0] = 0;
   out_3271917644950253884[1] = 9.8100000000000005*cos(state[1]);
   out_3271917644950253884[2] = 0;
   out_3271917644950253884[3] = 0;
   out_3271917644950253884[4] = -state[8];
   out_3271917644950253884[5] = state[7];
   out_3271917644950253884[6] = 0;
   out_3271917644950253884[7] = state[5];
   out_3271917644950253884[8] = -state[4];
   out_3271917644950253884[9] = 0;
   out_3271917644950253884[10] = 0;
   out_3271917644950253884[11] = 0;
   out_3271917644950253884[12] = 1;
   out_3271917644950253884[13] = 0;
   out_3271917644950253884[14] = 0;
   out_3271917644950253884[15] = 1;
   out_3271917644950253884[16] = 0;
   out_3271917644950253884[17] = 0;
   out_3271917644950253884[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3271917644950253884[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3271917644950253884[20] = 0;
   out_3271917644950253884[21] = state[8];
   out_3271917644950253884[22] = 0;
   out_3271917644950253884[23] = -state[6];
   out_3271917644950253884[24] = -state[5];
   out_3271917644950253884[25] = 0;
   out_3271917644950253884[26] = state[3];
   out_3271917644950253884[27] = 0;
   out_3271917644950253884[28] = 0;
   out_3271917644950253884[29] = 0;
   out_3271917644950253884[30] = 0;
   out_3271917644950253884[31] = 1;
   out_3271917644950253884[32] = 0;
   out_3271917644950253884[33] = 0;
   out_3271917644950253884[34] = 1;
   out_3271917644950253884[35] = 0;
   out_3271917644950253884[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3271917644950253884[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3271917644950253884[38] = 0;
   out_3271917644950253884[39] = -state[7];
   out_3271917644950253884[40] = state[6];
   out_3271917644950253884[41] = 0;
   out_3271917644950253884[42] = state[4];
   out_3271917644950253884[43] = -state[3];
   out_3271917644950253884[44] = 0;
   out_3271917644950253884[45] = 0;
   out_3271917644950253884[46] = 0;
   out_3271917644950253884[47] = 0;
   out_3271917644950253884[48] = 0;
   out_3271917644950253884[49] = 0;
   out_3271917644950253884[50] = 1;
   out_3271917644950253884[51] = 0;
   out_3271917644950253884[52] = 0;
   out_3271917644950253884[53] = 1;
}
void h_13(double *state, double *unused, double *out_1178992313314753128) {
   out_1178992313314753128[0] = state[3];
   out_1178992313314753128[1] = state[4];
   out_1178992313314753128[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7677564336865683075) {
   out_7677564336865683075[0] = 0;
   out_7677564336865683075[1] = 0;
   out_7677564336865683075[2] = 0;
   out_7677564336865683075[3] = 1;
   out_7677564336865683075[4] = 0;
   out_7677564336865683075[5] = 0;
   out_7677564336865683075[6] = 0;
   out_7677564336865683075[7] = 0;
   out_7677564336865683075[8] = 0;
   out_7677564336865683075[9] = 0;
   out_7677564336865683075[10] = 0;
   out_7677564336865683075[11] = 0;
   out_7677564336865683075[12] = 0;
   out_7677564336865683075[13] = 0;
   out_7677564336865683075[14] = 0;
   out_7677564336865683075[15] = 0;
   out_7677564336865683075[16] = 0;
   out_7677564336865683075[17] = 0;
   out_7677564336865683075[18] = 0;
   out_7677564336865683075[19] = 0;
   out_7677564336865683075[20] = 0;
   out_7677564336865683075[21] = 0;
   out_7677564336865683075[22] = 1;
   out_7677564336865683075[23] = 0;
   out_7677564336865683075[24] = 0;
   out_7677564336865683075[25] = 0;
   out_7677564336865683075[26] = 0;
   out_7677564336865683075[27] = 0;
   out_7677564336865683075[28] = 0;
   out_7677564336865683075[29] = 0;
   out_7677564336865683075[30] = 0;
   out_7677564336865683075[31] = 0;
   out_7677564336865683075[32] = 0;
   out_7677564336865683075[33] = 0;
   out_7677564336865683075[34] = 0;
   out_7677564336865683075[35] = 0;
   out_7677564336865683075[36] = 0;
   out_7677564336865683075[37] = 0;
   out_7677564336865683075[38] = 0;
   out_7677564336865683075[39] = 0;
   out_7677564336865683075[40] = 0;
   out_7677564336865683075[41] = 1;
   out_7677564336865683075[42] = 0;
   out_7677564336865683075[43] = 0;
   out_7677564336865683075[44] = 0;
   out_7677564336865683075[45] = 0;
   out_7677564336865683075[46] = 0;
   out_7677564336865683075[47] = 0;
   out_7677564336865683075[48] = 0;
   out_7677564336865683075[49] = 0;
   out_7677564336865683075[50] = 0;
   out_7677564336865683075[51] = 0;
   out_7677564336865683075[52] = 0;
   out_7677564336865683075[53] = 0;
}
void h_14(double *state, double *unused, double *out_3940331790740833198) {
   out_3940331790740833198[0] = state[6];
   out_3940331790740833198[1] = state[7];
   out_3940331790740833198[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8428531367872834803) {
   out_8428531367872834803[0] = 0;
   out_8428531367872834803[1] = 0;
   out_8428531367872834803[2] = 0;
   out_8428531367872834803[3] = 0;
   out_8428531367872834803[4] = 0;
   out_8428531367872834803[5] = 0;
   out_8428531367872834803[6] = 1;
   out_8428531367872834803[7] = 0;
   out_8428531367872834803[8] = 0;
   out_8428531367872834803[9] = 0;
   out_8428531367872834803[10] = 0;
   out_8428531367872834803[11] = 0;
   out_8428531367872834803[12] = 0;
   out_8428531367872834803[13] = 0;
   out_8428531367872834803[14] = 0;
   out_8428531367872834803[15] = 0;
   out_8428531367872834803[16] = 0;
   out_8428531367872834803[17] = 0;
   out_8428531367872834803[18] = 0;
   out_8428531367872834803[19] = 0;
   out_8428531367872834803[20] = 0;
   out_8428531367872834803[21] = 0;
   out_8428531367872834803[22] = 0;
   out_8428531367872834803[23] = 0;
   out_8428531367872834803[24] = 0;
   out_8428531367872834803[25] = 1;
   out_8428531367872834803[26] = 0;
   out_8428531367872834803[27] = 0;
   out_8428531367872834803[28] = 0;
   out_8428531367872834803[29] = 0;
   out_8428531367872834803[30] = 0;
   out_8428531367872834803[31] = 0;
   out_8428531367872834803[32] = 0;
   out_8428531367872834803[33] = 0;
   out_8428531367872834803[34] = 0;
   out_8428531367872834803[35] = 0;
   out_8428531367872834803[36] = 0;
   out_8428531367872834803[37] = 0;
   out_8428531367872834803[38] = 0;
   out_8428531367872834803[39] = 0;
   out_8428531367872834803[40] = 0;
   out_8428531367872834803[41] = 0;
   out_8428531367872834803[42] = 0;
   out_8428531367872834803[43] = 0;
   out_8428531367872834803[44] = 1;
   out_8428531367872834803[45] = 0;
   out_8428531367872834803[46] = 0;
   out_8428531367872834803[47] = 0;
   out_8428531367872834803[48] = 0;
   out_8428531367872834803[49] = 0;
   out_8428531367872834803[50] = 0;
   out_8428531367872834803[51] = 0;
   out_8428531367872834803[52] = 0;
   out_8428531367872834803[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_5169544621376104769) {
  err_fun(nom_x, delta_x, out_5169544621376104769);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5560919447530739345) {
  inv_err_fun(nom_x, true_x, out_5560919447530739345);
}
void pose_H_mod_fun(double *state, double *out_8932661143090135832) {
  H_mod_fun(state, out_8932661143090135832);
}
void pose_f_fun(double *state, double dt, double *out_3609843023403364566) {
  f_fun(state,  dt, out_3609843023403364566);
}
void pose_F_fun(double *state, double dt, double *out_8950799816554095649) {
  F_fun(state,  dt, out_8950799816554095649);
}
void pose_h_4(double *state, double *unused, double *out_7061694870208984097) {
  h_4(state, unused, out_7061694870208984097);
}
void pose_H_4(double *state, double *unused, double *out_4465290511533350274) {
  H_4(state, unused, out_4465290511533350274);
}
void pose_h_10(double *state, double *unused, double *out_10860459686481955) {
  h_10(state, unused, out_10860459686481955);
}
void pose_H_10(double *state, double *unused, double *out_3271917644950253884) {
  H_10(state, unused, out_3271917644950253884);
}
void pose_h_13(double *state, double *unused, double *out_1178992313314753128) {
  h_13(state, unused, out_1178992313314753128);
}
void pose_H_13(double *state, double *unused, double *out_7677564336865683075) {
  H_13(state, unused, out_7677564336865683075);
}
void pose_h_14(double *state, double *unused, double *out_3940331790740833198) {
  h_14(state, unused, out_3940331790740833198);
}
void pose_H_14(double *state, double *unused, double *out_8428531367872834803) {
  H_14(state, unused, out_8428531367872834803);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
