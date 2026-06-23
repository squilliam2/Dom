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
void err_fun(double *nom_x, double *delta_x, double *out_7527833659731555578) {
   out_7527833659731555578[0] = delta_x[0] + nom_x[0];
   out_7527833659731555578[1] = delta_x[1] + nom_x[1];
   out_7527833659731555578[2] = delta_x[2] + nom_x[2];
   out_7527833659731555578[3] = delta_x[3] + nom_x[3];
   out_7527833659731555578[4] = delta_x[4] + nom_x[4];
   out_7527833659731555578[5] = delta_x[5] + nom_x[5];
   out_7527833659731555578[6] = delta_x[6] + nom_x[6];
   out_7527833659731555578[7] = delta_x[7] + nom_x[7];
   out_7527833659731555578[8] = delta_x[8] + nom_x[8];
   out_7527833659731555578[9] = delta_x[9] + nom_x[9];
   out_7527833659731555578[10] = delta_x[10] + nom_x[10];
   out_7527833659731555578[11] = delta_x[11] + nom_x[11];
   out_7527833659731555578[12] = delta_x[12] + nom_x[12];
   out_7527833659731555578[13] = delta_x[13] + nom_x[13];
   out_7527833659731555578[14] = delta_x[14] + nom_x[14];
   out_7527833659731555578[15] = delta_x[15] + nom_x[15];
   out_7527833659731555578[16] = delta_x[16] + nom_x[16];
   out_7527833659731555578[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8121371430920178446) {
   out_8121371430920178446[0] = -nom_x[0] + true_x[0];
   out_8121371430920178446[1] = -nom_x[1] + true_x[1];
   out_8121371430920178446[2] = -nom_x[2] + true_x[2];
   out_8121371430920178446[3] = -nom_x[3] + true_x[3];
   out_8121371430920178446[4] = -nom_x[4] + true_x[4];
   out_8121371430920178446[5] = -nom_x[5] + true_x[5];
   out_8121371430920178446[6] = -nom_x[6] + true_x[6];
   out_8121371430920178446[7] = -nom_x[7] + true_x[7];
   out_8121371430920178446[8] = -nom_x[8] + true_x[8];
   out_8121371430920178446[9] = -nom_x[9] + true_x[9];
   out_8121371430920178446[10] = -nom_x[10] + true_x[10];
   out_8121371430920178446[11] = -nom_x[11] + true_x[11];
   out_8121371430920178446[12] = -nom_x[12] + true_x[12];
   out_8121371430920178446[13] = -nom_x[13] + true_x[13];
   out_8121371430920178446[14] = -nom_x[14] + true_x[14];
   out_8121371430920178446[15] = -nom_x[15] + true_x[15];
   out_8121371430920178446[16] = -nom_x[16] + true_x[16];
   out_8121371430920178446[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2787357462559363540) {
   out_2787357462559363540[0] = 1.0;
   out_2787357462559363540[1] = 0.0;
   out_2787357462559363540[2] = 0.0;
   out_2787357462559363540[3] = 0.0;
   out_2787357462559363540[4] = 0.0;
   out_2787357462559363540[5] = 0.0;
   out_2787357462559363540[6] = 0.0;
   out_2787357462559363540[7] = 0.0;
   out_2787357462559363540[8] = 0.0;
   out_2787357462559363540[9] = 0.0;
   out_2787357462559363540[10] = 0.0;
   out_2787357462559363540[11] = 0.0;
   out_2787357462559363540[12] = 0.0;
   out_2787357462559363540[13] = 0.0;
   out_2787357462559363540[14] = 0.0;
   out_2787357462559363540[15] = 0.0;
   out_2787357462559363540[16] = 0.0;
   out_2787357462559363540[17] = 0.0;
   out_2787357462559363540[18] = 0.0;
   out_2787357462559363540[19] = 1.0;
   out_2787357462559363540[20] = 0.0;
   out_2787357462559363540[21] = 0.0;
   out_2787357462559363540[22] = 0.0;
   out_2787357462559363540[23] = 0.0;
   out_2787357462559363540[24] = 0.0;
   out_2787357462559363540[25] = 0.0;
   out_2787357462559363540[26] = 0.0;
   out_2787357462559363540[27] = 0.0;
   out_2787357462559363540[28] = 0.0;
   out_2787357462559363540[29] = 0.0;
   out_2787357462559363540[30] = 0.0;
   out_2787357462559363540[31] = 0.0;
   out_2787357462559363540[32] = 0.0;
   out_2787357462559363540[33] = 0.0;
   out_2787357462559363540[34] = 0.0;
   out_2787357462559363540[35] = 0.0;
   out_2787357462559363540[36] = 0.0;
   out_2787357462559363540[37] = 0.0;
   out_2787357462559363540[38] = 1.0;
   out_2787357462559363540[39] = 0.0;
   out_2787357462559363540[40] = 0.0;
   out_2787357462559363540[41] = 0.0;
   out_2787357462559363540[42] = 0.0;
   out_2787357462559363540[43] = 0.0;
   out_2787357462559363540[44] = 0.0;
   out_2787357462559363540[45] = 0.0;
   out_2787357462559363540[46] = 0.0;
   out_2787357462559363540[47] = 0.0;
   out_2787357462559363540[48] = 0.0;
   out_2787357462559363540[49] = 0.0;
   out_2787357462559363540[50] = 0.0;
   out_2787357462559363540[51] = 0.0;
   out_2787357462559363540[52] = 0.0;
   out_2787357462559363540[53] = 0.0;
   out_2787357462559363540[54] = 0.0;
   out_2787357462559363540[55] = 0.0;
   out_2787357462559363540[56] = 0.0;
   out_2787357462559363540[57] = 1.0;
   out_2787357462559363540[58] = 0.0;
   out_2787357462559363540[59] = 0.0;
   out_2787357462559363540[60] = 0.0;
   out_2787357462559363540[61] = 0.0;
   out_2787357462559363540[62] = 0.0;
   out_2787357462559363540[63] = 0.0;
   out_2787357462559363540[64] = 0.0;
   out_2787357462559363540[65] = 0.0;
   out_2787357462559363540[66] = 0.0;
   out_2787357462559363540[67] = 0.0;
   out_2787357462559363540[68] = 0.0;
   out_2787357462559363540[69] = 0.0;
   out_2787357462559363540[70] = 0.0;
   out_2787357462559363540[71] = 0.0;
   out_2787357462559363540[72] = 0.0;
   out_2787357462559363540[73] = 0.0;
   out_2787357462559363540[74] = 0.0;
   out_2787357462559363540[75] = 0.0;
   out_2787357462559363540[76] = 1.0;
   out_2787357462559363540[77] = 0.0;
   out_2787357462559363540[78] = 0.0;
   out_2787357462559363540[79] = 0.0;
   out_2787357462559363540[80] = 0.0;
   out_2787357462559363540[81] = 0.0;
   out_2787357462559363540[82] = 0.0;
   out_2787357462559363540[83] = 0.0;
   out_2787357462559363540[84] = 0.0;
   out_2787357462559363540[85] = 0.0;
   out_2787357462559363540[86] = 0.0;
   out_2787357462559363540[87] = 0.0;
   out_2787357462559363540[88] = 0.0;
   out_2787357462559363540[89] = 0.0;
   out_2787357462559363540[90] = 0.0;
   out_2787357462559363540[91] = 0.0;
   out_2787357462559363540[92] = 0.0;
   out_2787357462559363540[93] = 0.0;
   out_2787357462559363540[94] = 0.0;
   out_2787357462559363540[95] = 1.0;
   out_2787357462559363540[96] = 0.0;
   out_2787357462559363540[97] = 0.0;
   out_2787357462559363540[98] = 0.0;
   out_2787357462559363540[99] = 0.0;
   out_2787357462559363540[100] = 0.0;
   out_2787357462559363540[101] = 0.0;
   out_2787357462559363540[102] = 0.0;
   out_2787357462559363540[103] = 0.0;
   out_2787357462559363540[104] = 0.0;
   out_2787357462559363540[105] = 0.0;
   out_2787357462559363540[106] = 0.0;
   out_2787357462559363540[107] = 0.0;
   out_2787357462559363540[108] = 0.0;
   out_2787357462559363540[109] = 0.0;
   out_2787357462559363540[110] = 0.0;
   out_2787357462559363540[111] = 0.0;
   out_2787357462559363540[112] = 0.0;
   out_2787357462559363540[113] = 0.0;
   out_2787357462559363540[114] = 1.0;
   out_2787357462559363540[115] = 0.0;
   out_2787357462559363540[116] = 0.0;
   out_2787357462559363540[117] = 0.0;
   out_2787357462559363540[118] = 0.0;
   out_2787357462559363540[119] = 0.0;
   out_2787357462559363540[120] = 0.0;
   out_2787357462559363540[121] = 0.0;
   out_2787357462559363540[122] = 0.0;
   out_2787357462559363540[123] = 0.0;
   out_2787357462559363540[124] = 0.0;
   out_2787357462559363540[125] = 0.0;
   out_2787357462559363540[126] = 0.0;
   out_2787357462559363540[127] = 0.0;
   out_2787357462559363540[128] = 0.0;
   out_2787357462559363540[129] = 0.0;
   out_2787357462559363540[130] = 0.0;
   out_2787357462559363540[131] = 0.0;
   out_2787357462559363540[132] = 0.0;
   out_2787357462559363540[133] = 1.0;
   out_2787357462559363540[134] = 0.0;
   out_2787357462559363540[135] = 0.0;
   out_2787357462559363540[136] = 0.0;
   out_2787357462559363540[137] = 0.0;
   out_2787357462559363540[138] = 0.0;
   out_2787357462559363540[139] = 0.0;
   out_2787357462559363540[140] = 0.0;
   out_2787357462559363540[141] = 0.0;
   out_2787357462559363540[142] = 0.0;
   out_2787357462559363540[143] = 0.0;
   out_2787357462559363540[144] = 0.0;
   out_2787357462559363540[145] = 0.0;
   out_2787357462559363540[146] = 0.0;
   out_2787357462559363540[147] = 0.0;
   out_2787357462559363540[148] = 0.0;
   out_2787357462559363540[149] = 0.0;
   out_2787357462559363540[150] = 0.0;
   out_2787357462559363540[151] = 0.0;
   out_2787357462559363540[152] = 1.0;
   out_2787357462559363540[153] = 0.0;
   out_2787357462559363540[154] = 0.0;
   out_2787357462559363540[155] = 0.0;
   out_2787357462559363540[156] = 0.0;
   out_2787357462559363540[157] = 0.0;
   out_2787357462559363540[158] = 0.0;
   out_2787357462559363540[159] = 0.0;
   out_2787357462559363540[160] = 0.0;
   out_2787357462559363540[161] = 0.0;
   out_2787357462559363540[162] = 0.0;
   out_2787357462559363540[163] = 0.0;
   out_2787357462559363540[164] = 0.0;
   out_2787357462559363540[165] = 0.0;
   out_2787357462559363540[166] = 0.0;
   out_2787357462559363540[167] = 0.0;
   out_2787357462559363540[168] = 0.0;
   out_2787357462559363540[169] = 0.0;
   out_2787357462559363540[170] = 0.0;
   out_2787357462559363540[171] = 1.0;
   out_2787357462559363540[172] = 0.0;
   out_2787357462559363540[173] = 0.0;
   out_2787357462559363540[174] = 0.0;
   out_2787357462559363540[175] = 0.0;
   out_2787357462559363540[176] = 0.0;
   out_2787357462559363540[177] = 0.0;
   out_2787357462559363540[178] = 0.0;
   out_2787357462559363540[179] = 0.0;
   out_2787357462559363540[180] = 0.0;
   out_2787357462559363540[181] = 0.0;
   out_2787357462559363540[182] = 0.0;
   out_2787357462559363540[183] = 0.0;
   out_2787357462559363540[184] = 0.0;
   out_2787357462559363540[185] = 0.0;
   out_2787357462559363540[186] = 0.0;
   out_2787357462559363540[187] = 0.0;
   out_2787357462559363540[188] = 0.0;
   out_2787357462559363540[189] = 0.0;
   out_2787357462559363540[190] = 1.0;
   out_2787357462559363540[191] = 0.0;
   out_2787357462559363540[192] = 0.0;
   out_2787357462559363540[193] = 0.0;
   out_2787357462559363540[194] = 0.0;
   out_2787357462559363540[195] = 0.0;
   out_2787357462559363540[196] = 0.0;
   out_2787357462559363540[197] = 0.0;
   out_2787357462559363540[198] = 0.0;
   out_2787357462559363540[199] = 0.0;
   out_2787357462559363540[200] = 0.0;
   out_2787357462559363540[201] = 0.0;
   out_2787357462559363540[202] = 0.0;
   out_2787357462559363540[203] = 0.0;
   out_2787357462559363540[204] = 0.0;
   out_2787357462559363540[205] = 0.0;
   out_2787357462559363540[206] = 0.0;
   out_2787357462559363540[207] = 0.0;
   out_2787357462559363540[208] = 0.0;
   out_2787357462559363540[209] = 1.0;
   out_2787357462559363540[210] = 0.0;
   out_2787357462559363540[211] = 0.0;
   out_2787357462559363540[212] = 0.0;
   out_2787357462559363540[213] = 0.0;
   out_2787357462559363540[214] = 0.0;
   out_2787357462559363540[215] = 0.0;
   out_2787357462559363540[216] = 0.0;
   out_2787357462559363540[217] = 0.0;
   out_2787357462559363540[218] = 0.0;
   out_2787357462559363540[219] = 0.0;
   out_2787357462559363540[220] = 0.0;
   out_2787357462559363540[221] = 0.0;
   out_2787357462559363540[222] = 0.0;
   out_2787357462559363540[223] = 0.0;
   out_2787357462559363540[224] = 0.0;
   out_2787357462559363540[225] = 0.0;
   out_2787357462559363540[226] = 0.0;
   out_2787357462559363540[227] = 0.0;
   out_2787357462559363540[228] = 1.0;
   out_2787357462559363540[229] = 0.0;
   out_2787357462559363540[230] = 0.0;
   out_2787357462559363540[231] = 0.0;
   out_2787357462559363540[232] = 0.0;
   out_2787357462559363540[233] = 0.0;
   out_2787357462559363540[234] = 0.0;
   out_2787357462559363540[235] = 0.0;
   out_2787357462559363540[236] = 0.0;
   out_2787357462559363540[237] = 0.0;
   out_2787357462559363540[238] = 0.0;
   out_2787357462559363540[239] = 0.0;
   out_2787357462559363540[240] = 0.0;
   out_2787357462559363540[241] = 0.0;
   out_2787357462559363540[242] = 0.0;
   out_2787357462559363540[243] = 0.0;
   out_2787357462559363540[244] = 0.0;
   out_2787357462559363540[245] = 0.0;
   out_2787357462559363540[246] = 0.0;
   out_2787357462559363540[247] = 1.0;
   out_2787357462559363540[248] = 0.0;
   out_2787357462559363540[249] = 0.0;
   out_2787357462559363540[250] = 0.0;
   out_2787357462559363540[251] = 0.0;
   out_2787357462559363540[252] = 0.0;
   out_2787357462559363540[253] = 0.0;
   out_2787357462559363540[254] = 0.0;
   out_2787357462559363540[255] = 0.0;
   out_2787357462559363540[256] = 0.0;
   out_2787357462559363540[257] = 0.0;
   out_2787357462559363540[258] = 0.0;
   out_2787357462559363540[259] = 0.0;
   out_2787357462559363540[260] = 0.0;
   out_2787357462559363540[261] = 0.0;
   out_2787357462559363540[262] = 0.0;
   out_2787357462559363540[263] = 0.0;
   out_2787357462559363540[264] = 0.0;
   out_2787357462559363540[265] = 0.0;
   out_2787357462559363540[266] = 1.0;
   out_2787357462559363540[267] = 0.0;
   out_2787357462559363540[268] = 0.0;
   out_2787357462559363540[269] = 0.0;
   out_2787357462559363540[270] = 0.0;
   out_2787357462559363540[271] = 0.0;
   out_2787357462559363540[272] = 0.0;
   out_2787357462559363540[273] = 0.0;
   out_2787357462559363540[274] = 0.0;
   out_2787357462559363540[275] = 0.0;
   out_2787357462559363540[276] = 0.0;
   out_2787357462559363540[277] = 0.0;
   out_2787357462559363540[278] = 0.0;
   out_2787357462559363540[279] = 0.0;
   out_2787357462559363540[280] = 0.0;
   out_2787357462559363540[281] = 0.0;
   out_2787357462559363540[282] = 0.0;
   out_2787357462559363540[283] = 0.0;
   out_2787357462559363540[284] = 0.0;
   out_2787357462559363540[285] = 1.0;
   out_2787357462559363540[286] = 0.0;
   out_2787357462559363540[287] = 0.0;
   out_2787357462559363540[288] = 0.0;
   out_2787357462559363540[289] = 0.0;
   out_2787357462559363540[290] = 0.0;
   out_2787357462559363540[291] = 0.0;
   out_2787357462559363540[292] = 0.0;
   out_2787357462559363540[293] = 0.0;
   out_2787357462559363540[294] = 0.0;
   out_2787357462559363540[295] = 0.0;
   out_2787357462559363540[296] = 0.0;
   out_2787357462559363540[297] = 0.0;
   out_2787357462559363540[298] = 0.0;
   out_2787357462559363540[299] = 0.0;
   out_2787357462559363540[300] = 0.0;
   out_2787357462559363540[301] = 0.0;
   out_2787357462559363540[302] = 0.0;
   out_2787357462559363540[303] = 0.0;
   out_2787357462559363540[304] = 1.0;
   out_2787357462559363540[305] = 0.0;
   out_2787357462559363540[306] = 0.0;
   out_2787357462559363540[307] = 0.0;
   out_2787357462559363540[308] = 0.0;
   out_2787357462559363540[309] = 0.0;
   out_2787357462559363540[310] = 0.0;
   out_2787357462559363540[311] = 0.0;
   out_2787357462559363540[312] = 0.0;
   out_2787357462559363540[313] = 0.0;
   out_2787357462559363540[314] = 0.0;
   out_2787357462559363540[315] = 0.0;
   out_2787357462559363540[316] = 0.0;
   out_2787357462559363540[317] = 0.0;
   out_2787357462559363540[318] = 0.0;
   out_2787357462559363540[319] = 0.0;
   out_2787357462559363540[320] = 0.0;
   out_2787357462559363540[321] = 0.0;
   out_2787357462559363540[322] = 0.0;
   out_2787357462559363540[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2997254779517652533) {
   out_2997254779517652533[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2997254779517652533[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2997254779517652533[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2997254779517652533[3] = dt*state[12] + state[3];
   out_2997254779517652533[4] = dt*state[13] + state[4];
   out_2997254779517652533[5] = dt*state[14] + state[5];
   out_2997254779517652533[6] = state[6];
   out_2997254779517652533[7] = state[7];
   out_2997254779517652533[8] = state[8];
   out_2997254779517652533[9] = state[9];
   out_2997254779517652533[10] = state[10];
   out_2997254779517652533[11] = state[11];
   out_2997254779517652533[12] = state[12];
   out_2997254779517652533[13] = state[13];
   out_2997254779517652533[14] = state[14];
   out_2997254779517652533[15] = state[15];
   out_2997254779517652533[16] = state[16];
   out_2997254779517652533[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3476500674504442735) {
   out_3476500674504442735[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3476500674504442735[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3476500674504442735[2] = 0;
   out_3476500674504442735[3] = 0;
   out_3476500674504442735[4] = 0;
   out_3476500674504442735[5] = 0;
   out_3476500674504442735[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3476500674504442735[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3476500674504442735[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3476500674504442735[9] = 0;
   out_3476500674504442735[10] = 0;
   out_3476500674504442735[11] = 0;
   out_3476500674504442735[12] = 0;
   out_3476500674504442735[13] = 0;
   out_3476500674504442735[14] = 0;
   out_3476500674504442735[15] = 0;
   out_3476500674504442735[16] = 0;
   out_3476500674504442735[17] = 0;
   out_3476500674504442735[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3476500674504442735[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3476500674504442735[20] = 0;
   out_3476500674504442735[21] = 0;
   out_3476500674504442735[22] = 0;
   out_3476500674504442735[23] = 0;
   out_3476500674504442735[24] = 0;
   out_3476500674504442735[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3476500674504442735[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3476500674504442735[27] = 0;
   out_3476500674504442735[28] = 0;
   out_3476500674504442735[29] = 0;
   out_3476500674504442735[30] = 0;
   out_3476500674504442735[31] = 0;
   out_3476500674504442735[32] = 0;
   out_3476500674504442735[33] = 0;
   out_3476500674504442735[34] = 0;
   out_3476500674504442735[35] = 0;
   out_3476500674504442735[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3476500674504442735[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3476500674504442735[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3476500674504442735[39] = 0;
   out_3476500674504442735[40] = 0;
   out_3476500674504442735[41] = 0;
   out_3476500674504442735[42] = 0;
   out_3476500674504442735[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3476500674504442735[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3476500674504442735[45] = 0;
   out_3476500674504442735[46] = 0;
   out_3476500674504442735[47] = 0;
   out_3476500674504442735[48] = 0;
   out_3476500674504442735[49] = 0;
   out_3476500674504442735[50] = 0;
   out_3476500674504442735[51] = 0;
   out_3476500674504442735[52] = 0;
   out_3476500674504442735[53] = 0;
   out_3476500674504442735[54] = 0;
   out_3476500674504442735[55] = 0;
   out_3476500674504442735[56] = 0;
   out_3476500674504442735[57] = 1;
   out_3476500674504442735[58] = 0;
   out_3476500674504442735[59] = 0;
   out_3476500674504442735[60] = 0;
   out_3476500674504442735[61] = 0;
   out_3476500674504442735[62] = 0;
   out_3476500674504442735[63] = 0;
   out_3476500674504442735[64] = 0;
   out_3476500674504442735[65] = 0;
   out_3476500674504442735[66] = dt;
   out_3476500674504442735[67] = 0;
   out_3476500674504442735[68] = 0;
   out_3476500674504442735[69] = 0;
   out_3476500674504442735[70] = 0;
   out_3476500674504442735[71] = 0;
   out_3476500674504442735[72] = 0;
   out_3476500674504442735[73] = 0;
   out_3476500674504442735[74] = 0;
   out_3476500674504442735[75] = 0;
   out_3476500674504442735[76] = 1;
   out_3476500674504442735[77] = 0;
   out_3476500674504442735[78] = 0;
   out_3476500674504442735[79] = 0;
   out_3476500674504442735[80] = 0;
   out_3476500674504442735[81] = 0;
   out_3476500674504442735[82] = 0;
   out_3476500674504442735[83] = 0;
   out_3476500674504442735[84] = 0;
   out_3476500674504442735[85] = dt;
   out_3476500674504442735[86] = 0;
   out_3476500674504442735[87] = 0;
   out_3476500674504442735[88] = 0;
   out_3476500674504442735[89] = 0;
   out_3476500674504442735[90] = 0;
   out_3476500674504442735[91] = 0;
   out_3476500674504442735[92] = 0;
   out_3476500674504442735[93] = 0;
   out_3476500674504442735[94] = 0;
   out_3476500674504442735[95] = 1;
   out_3476500674504442735[96] = 0;
   out_3476500674504442735[97] = 0;
   out_3476500674504442735[98] = 0;
   out_3476500674504442735[99] = 0;
   out_3476500674504442735[100] = 0;
   out_3476500674504442735[101] = 0;
   out_3476500674504442735[102] = 0;
   out_3476500674504442735[103] = 0;
   out_3476500674504442735[104] = dt;
   out_3476500674504442735[105] = 0;
   out_3476500674504442735[106] = 0;
   out_3476500674504442735[107] = 0;
   out_3476500674504442735[108] = 0;
   out_3476500674504442735[109] = 0;
   out_3476500674504442735[110] = 0;
   out_3476500674504442735[111] = 0;
   out_3476500674504442735[112] = 0;
   out_3476500674504442735[113] = 0;
   out_3476500674504442735[114] = 1;
   out_3476500674504442735[115] = 0;
   out_3476500674504442735[116] = 0;
   out_3476500674504442735[117] = 0;
   out_3476500674504442735[118] = 0;
   out_3476500674504442735[119] = 0;
   out_3476500674504442735[120] = 0;
   out_3476500674504442735[121] = 0;
   out_3476500674504442735[122] = 0;
   out_3476500674504442735[123] = 0;
   out_3476500674504442735[124] = 0;
   out_3476500674504442735[125] = 0;
   out_3476500674504442735[126] = 0;
   out_3476500674504442735[127] = 0;
   out_3476500674504442735[128] = 0;
   out_3476500674504442735[129] = 0;
   out_3476500674504442735[130] = 0;
   out_3476500674504442735[131] = 0;
   out_3476500674504442735[132] = 0;
   out_3476500674504442735[133] = 1;
   out_3476500674504442735[134] = 0;
   out_3476500674504442735[135] = 0;
   out_3476500674504442735[136] = 0;
   out_3476500674504442735[137] = 0;
   out_3476500674504442735[138] = 0;
   out_3476500674504442735[139] = 0;
   out_3476500674504442735[140] = 0;
   out_3476500674504442735[141] = 0;
   out_3476500674504442735[142] = 0;
   out_3476500674504442735[143] = 0;
   out_3476500674504442735[144] = 0;
   out_3476500674504442735[145] = 0;
   out_3476500674504442735[146] = 0;
   out_3476500674504442735[147] = 0;
   out_3476500674504442735[148] = 0;
   out_3476500674504442735[149] = 0;
   out_3476500674504442735[150] = 0;
   out_3476500674504442735[151] = 0;
   out_3476500674504442735[152] = 1;
   out_3476500674504442735[153] = 0;
   out_3476500674504442735[154] = 0;
   out_3476500674504442735[155] = 0;
   out_3476500674504442735[156] = 0;
   out_3476500674504442735[157] = 0;
   out_3476500674504442735[158] = 0;
   out_3476500674504442735[159] = 0;
   out_3476500674504442735[160] = 0;
   out_3476500674504442735[161] = 0;
   out_3476500674504442735[162] = 0;
   out_3476500674504442735[163] = 0;
   out_3476500674504442735[164] = 0;
   out_3476500674504442735[165] = 0;
   out_3476500674504442735[166] = 0;
   out_3476500674504442735[167] = 0;
   out_3476500674504442735[168] = 0;
   out_3476500674504442735[169] = 0;
   out_3476500674504442735[170] = 0;
   out_3476500674504442735[171] = 1;
   out_3476500674504442735[172] = 0;
   out_3476500674504442735[173] = 0;
   out_3476500674504442735[174] = 0;
   out_3476500674504442735[175] = 0;
   out_3476500674504442735[176] = 0;
   out_3476500674504442735[177] = 0;
   out_3476500674504442735[178] = 0;
   out_3476500674504442735[179] = 0;
   out_3476500674504442735[180] = 0;
   out_3476500674504442735[181] = 0;
   out_3476500674504442735[182] = 0;
   out_3476500674504442735[183] = 0;
   out_3476500674504442735[184] = 0;
   out_3476500674504442735[185] = 0;
   out_3476500674504442735[186] = 0;
   out_3476500674504442735[187] = 0;
   out_3476500674504442735[188] = 0;
   out_3476500674504442735[189] = 0;
   out_3476500674504442735[190] = 1;
   out_3476500674504442735[191] = 0;
   out_3476500674504442735[192] = 0;
   out_3476500674504442735[193] = 0;
   out_3476500674504442735[194] = 0;
   out_3476500674504442735[195] = 0;
   out_3476500674504442735[196] = 0;
   out_3476500674504442735[197] = 0;
   out_3476500674504442735[198] = 0;
   out_3476500674504442735[199] = 0;
   out_3476500674504442735[200] = 0;
   out_3476500674504442735[201] = 0;
   out_3476500674504442735[202] = 0;
   out_3476500674504442735[203] = 0;
   out_3476500674504442735[204] = 0;
   out_3476500674504442735[205] = 0;
   out_3476500674504442735[206] = 0;
   out_3476500674504442735[207] = 0;
   out_3476500674504442735[208] = 0;
   out_3476500674504442735[209] = 1;
   out_3476500674504442735[210] = 0;
   out_3476500674504442735[211] = 0;
   out_3476500674504442735[212] = 0;
   out_3476500674504442735[213] = 0;
   out_3476500674504442735[214] = 0;
   out_3476500674504442735[215] = 0;
   out_3476500674504442735[216] = 0;
   out_3476500674504442735[217] = 0;
   out_3476500674504442735[218] = 0;
   out_3476500674504442735[219] = 0;
   out_3476500674504442735[220] = 0;
   out_3476500674504442735[221] = 0;
   out_3476500674504442735[222] = 0;
   out_3476500674504442735[223] = 0;
   out_3476500674504442735[224] = 0;
   out_3476500674504442735[225] = 0;
   out_3476500674504442735[226] = 0;
   out_3476500674504442735[227] = 0;
   out_3476500674504442735[228] = 1;
   out_3476500674504442735[229] = 0;
   out_3476500674504442735[230] = 0;
   out_3476500674504442735[231] = 0;
   out_3476500674504442735[232] = 0;
   out_3476500674504442735[233] = 0;
   out_3476500674504442735[234] = 0;
   out_3476500674504442735[235] = 0;
   out_3476500674504442735[236] = 0;
   out_3476500674504442735[237] = 0;
   out_3476500674504442735[238] = 0;
   out_3476500674504442735[239] = 0;
   out_3476500674504442735[240] = 0;
   out_3476500674504442735[241] = 0;
   out_3476500674504442735[242] = 0;
   out_3476500674504442735[243] = 0;
   out_3476500674504442735[244] = 0;
   out_3476500674504442735[245] = 0;
   out_3476500674504442735[246] = 0;
   out_3476500674504442735[247] = 1;
   out_3476500674504442735[248] = 0;
   out_3476500674504442735[249] = 0;
   out_3476500674504442735[250] = 0;
   out_3476500674504442735[251] = 0;
   out_3476500674504442735[252] = 0;
   out_3476500674504442735[253] = 0;
   out_3476500674504442735[254] = 0;
   out_3476500674504442735[255] = 0;
   out_3476500674504442735[256] = 0;
   out_3476500674504442735[257] = 0;
   out_3476500674504442735[258] = 0;
   out_3476500674504442735[259] = 0;
   out_3476500674504442735[260] = 0;
   out_3476500674504442735[261] = 0;
   out_3476500674504442735[262] = 0;
   out_3476500674504442735[263] = 0;
   out_3476500674504442735[264] = 0;
   out_3476500674504442735[265] = 0;
   out_3476500674504442735[266] = 1;
   out_3476500674504442735[267] = 0;
   out_3476500674504442735[268] = 0;
   out_3476500674504442735[269] = 0;
   out_3476500674504442735[270] = 0;
   out_3476500674504442735[271] = 0;
   out_3476500674504442735[272] = 0;
   out_3476500674504442735[273] = 0;
   out_3476500674504442735[274] = 0;
   out_3476500674504442735[275] = 0;
   out_3476500674504442735[276] = 0;
   out_3476500674504442735[277] = 0;
   out_3476500674504442735[278] = 0;
   out_3476500674504442735[279] = 0;
   out_3476500674504442735[280] = 0;
   out_3476500674504442735[281] = 0;
   out_3476500674504442735[282] = 0;
   out_3476500674504442735[283] = 0;
   out_3476500674504442735[284] = 0;
   out_3476500674504442735[285] = 1;
   out_3476500674504442735[286] = 0;
   out_3476500674504442735[287] = 0;
   out_3476500674504442735[288] = 0;
   out_3476500674504442735[289] = 0;
   out_3476500674504442735[290] = 0;
   out_3476500674504442735[291] = 0;
   out_3476500674504442735[292] = 0;
   out_3476500674504442735[293] = 0;
   out_3476500674504442735[294] = 0;
   out_3476500674504442735[295] = 0;
   out_3476500674504442735[296] = 0;
   out_3476500674504442735[297] = 0;
   out_3476500674504442735[298] = 0;
   out_3476500674504442735[299] = 0;
   out_3476500674504442735[300] = 0;
   out_3476500674504442735[301] = 0;
   out_3476500674504442735[302] = 0;
   out_3476500674504442735[303] = 0;
   out_3476500674504442735[304] = 1;
   out_3476500674504442735[305] = 0;
   out_3476500674504442735[306] = 0;
   out_3476500674504442735[307] = 0;
   out_3476500674504442735[308] = 0;
   out_3476500674504442735[309] = 0;
   out_3476500674504442735[310] = 0;
   out_3476500674504442735[311] = 0;
   out_3476500674504442735[312] = 0;
   out_3476500674504442735[313] = 0;
   out_3476500674504442735[314] = 0;
   out_3476500674504442735[315] = 0;
   out_3476500674504442735[316] = 0;
   out_3476500674504442735[317] = 0;
   out_3476500674504442735[318] = 0;
   out_3476500674504442735[319] = 0;
   out_3476500674504442735[320] = 0;
   out_3476500674504442735[321] = 0;
   out_3476500674504442735[322] = 0;
   out_3476500674504442735[323] = 1;
}
void h_4(double *state, double *unused, double *out_2259436079279725972) {
   out_2259436079279725972[0] = state[6] + state[9];
   out_2259436079279725972[1] = state[7] + state[10];
   out_2259436079279725972[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6715024945092366734) {
   out_6715024945092366734[0] = 0;
   out_6715024945092366734[1] = 0;
   out_6715024945092366734[2] = 0;
   out_6715024945092366734[3] = 0;
   out_6715024945092366734[4] = 0;
   out_6715024945092366734[5] = 0;
   out_6715024945092366734[6] = 1;
   out_6715024945092366734[7] = 0;
   out_6715024945092366734[8] = 0;
   out_6715024945092366734[9] = 1;
   out_6715024945092366734[10] = 0;
   out_6715024945092366734[11] = 0;
   out_6715024945092366734[12] = 0;
   out_6715024945092366734[13] = 0;
   out_6715024945092366734[14] = 0;
   out_6715024945092366734[15] = 0;
   out_6715024945092366734[16] = 0;
   out_6715024945092366734[17] = 0;
   out_6715024945092366734[18] = 0;
   out_6715024945092366734[19] = 0;
   out_6715024945092366734[20] = 0;
   out_6715024945092366734[21] = 0;
   out_6715024945092366734[22] = 0;
   out_6715024945092366734[23] = 0;
   out_6715024945092366734[24] = 0;
   out_6715024945092366734[25] = 1;
   out_6715024945092366734[26] = 0;
   out_6715024945092366734[27] = 0;
   out_6715024945092366734[28] = 1;
   out_6715024945092366734[29] = 0;
   out_6715024945092366734[30] = 0;
   out_6715024945092366734[31] = 0;
   out_6715024945092366734[32] = 0;
   out_6715024945092366734[33] = 0;
   out_6715024945092366734[34] = 0;
   out_6715024945092366734[35] = 0;
   out_6715024945092366734[36] = 0;
   out_6715024945092366734[37] = 0;
   out_6715024945092366734[38] = 0;
   out_6715024945092366734[39] = 0;
   out_6715024945092366734[40] = 0;
   out_6715024945092366734[41] = 0;
   out_6715024945092366734[42] = 0;
   out_6715024945092366734[43] = 0;
   out_6715024945092366734[44] = 1;
   out_6715024945092366734[45] = 0;
   out_6715024945092366734[46] = 0;
   out_6715024945092366734[47] = 1;
   out_6715024945092366734[48] = 0;
   out_6715024945092366734[49] = 0;
   out_6715024945092366734[50] = 0;
   out_6715024945092366734[51] = 0;
   out_6715024945092366734[52] = 0;
   out_6715024945092366734[53] = 0;
}
void h_10(double *state, double *unused, double *out_4495031819694209583) {
   out_4495031819694209583[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4495031819694209583[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4495031819694209583[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8084729141614988184) {
   out_8084729141614988184[0] = 0;
   out_8084729141614988184[1] = 9.8100000000000005*cos(state[1]);
   out_8084729141614988184[2] = 0;
   out_8084729141614988184[3] = 0;
   out_8084729141614988184[4] = -state[8];
   out_8084729141614988184[5] = state[7];
   out_8084729141614988184[6] = 0;
   out_8084729141614988184[7] = state[5];
   out_8084729141614988184[8] = -state[4];
   out_8084729141614988184[9] = 0;
   out_8084729141614988184[10] = 0;
   out_8084729141614988184[11] = 0;
   out_8084729141614988184[12] = 1;
   out_8084729141614988184[13] = 0;
   out_8084729141614988184[14] = 0;
   out_8084729141614988184[15] = 1;
   out_8084729141614988184[16] = 0;
   out_8084729141614988184[17] = 0;
   out_8084729141614988184[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8084729141614988184[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8084729141614988184[20] = 0;
   out_8084729141614988184[21] = state[8];
   out_8084729141614988184[22] = 0;
   out_8084729141614988184[23] = -state[6];
   out_8084729141614988184[24] = -state[5];
   out_8084729141614988184[25] = 0;
   out_8084729141614988184[26] = state[3];
   out_8084729141614988184[27] = 0;
   out_8084729141614988184[28] = 0;
   out_8084729141614988184[29] = 0;
   out_8084729141614988184[30] = 0;
   out_8084729141614988184[31] = 1;
   out_8084729141614988184[32] = 0;
   out_8084729141614988184[33] = 0;
   out_8084729141614988184[34] = 1;
   out_8084729141614988184[35] = 0;
   out_8084729141614988184[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8084729141614988184[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8084729141614988184[38] = 0;
   out_8084729141614988184[39] = -state[7];
   out_8084729141614988184[40] = state[6];
   out_8084729141614988184[41] = 0;
   out_8084729141614988184[42] = state[4];
   out_8084729141614988184[43] = -state[3];
   out_8084729141614988184[44] = 0;
   out_8084729141614988184[45] = 0;
   out_8084729141614988184[46] = 0;
   out_8084729141614988184[47] = 0;
   out_8084729141614988184[48] = 0;
   out_8084729141614988184[49] = 0;
   out_8084729141614988184[50] = 1;
   out_8084729141614988184[51] = 0;
   out_8084729141614988184[52] = 0;
   out_8084729141614988184[53] = 1;
}
void h_13(double *state, double *unused, double *out_7265342654384269353) {
   out_7265342654384269353[0] = state[3];
   out_7265342654384269353[1] = state[4];
   out_7265342654384269353[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8519445303284852081) {
   out_8519445303284852081[0] = 0;
   out_8519445303284852081[1] = 0;
   out_8519445303284852081[2] = 0;
   out_8519445303284852081[3] = 1;
   out_8519445303284852081[4] = 0;
   out_8519445303284852081[5] = 0;
   out_8519445303284852081[6] = 0;
   out_8519445303284852081[7] = 0;
   out_8519445303284852081[8] = 0;
   out_8519445303284852081[9] = 0;
   out_8519445303284852081[10] = 0;
   out_8519445303284852081[11] = 0;
   out_8519445303284852081[12] = 0;
   out_8519445303284852081[13] = 0;
   out_8519445303284852081[14] = 0;
   out_8519445303284852081[15] = 0;
   out_8519445303284852081[16] = 0;
   out_8519445303284852081[17] = 0;
   out_8519445303284852081[18] = 0;
   out_8519445303284852081[19] = 0;
   out_8519445303284852081[20] = 0;
   out_8519445303284852081[21] = 0;
   out_8519445303284852081[22] = 1;
   out_8519445303284852081[23] = 0;
   out_8519445303284852081[24] = 0;
   out_8519445303284852081[25] = 0;
   out_8519445303284852081[26] = 0;
   out_8519445303284852081[27] = 0;
   out_8519445303284852081[28] = 0;
   out_8519445303284852081[29] = 0;
   out_8519445303284852081[30] = 0;
   out_8519445303284852081[31] = 0;
   out_8519445303284852081[32] = 0;
   out_8519445303284852081[33] = 0;
   out_8519445303284852081[34] = 0;
   out_8519445303284852081[35] = 0;
   out_8519445303284852081[36] = 0;
   out_8519445303284852081[37] = 0;
   out_8519445303284852081[38] = 0;
   out_8519445303284852081[39] = 0;
   out_8519445303284852081[40] = 0;
   out_8519445303284852081[41] = 1;
   out_8519445303284852081[42] = 0;
   out_8519445303284852081[43] = 0;
   out_8519445303284852081[44] = 0;
   out_8519445303284852081[45] = 0;
   out_8519445303284852081[46] = 0;
   out_8519445303284852081[47] = 0;
   out_8519445303284852081[48] = 0;
   out_8519445303284852081[49] = 0;
   out_8519445303284852081[50] = 0;
   out_8519445303284852081[51] = 0;
   out_8519445303284852081[52] = 0;
   out_8519445303284852081[53] = 0;
}
void h_14(double *state, double *unused, double *out_2527703015463387955) {
   out_2527703015463387955[0] = state[6];
   out_2527703015463387955[1] = state[7];
   out_2527703015463387955[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7768478272277700353) {
   out_7768478272277700353[0] = 0;
   out_7768478272277700353[1] = 0;
   out_7768478272277700353[2] = 0;
   out_7768478272277700353[3] = 0;
   out_7768478272277700353[4] = 0;
   out_7768478272277700353[5] = 0;
   out_7768478272277700353[6] = 1;
   out_7768478272277700353[7] = 0;
   out_7768478272277700353[8] = 0;
   out_7768478272277700353[9] = 0;
   out_7768478272277700353[10] = 0;
   out_7768478272277700353[11] = 0;
   out_7768478272277700353[12] = 0;
   out_7768478272277700353[13] = 0;
   out_7768478272277700353[14] = 0;
   out_7768478272277700353[15] = 0;
   out_7768478272277700353[16] = 0;
   out_7768478272277700353[17] = 0;
   out_7768478272277700353[18] = 0;
   out_7768478272277700353[19] = 0;
   out_7768478272277700353[20] = 0;
   out_7768478272277700353[21] = 0;
   out_7768478272277700353[22] = 0;
   out_7768478272277700353[23] = 0;
   out_7768478272277700353[24] = 0;
   out_7768478272277700353[25] = 1;
   out_7768478272277700353[26] = 0;
   out_7768478272277700353[27] = 0;
   out_7768478272277700353[28] = 0;
   out_7768478272277700353[29] = 0;
   out_7768478272277700353[30] = 0;
   out_7768478272277700353[31] = 0;
   out_7768478272277700353[32] = 0;
   out_7768478272277700353[33] = 0;
   out_7768478272277700353[34] = 0;
   out_7768478272277700353[35] = 0;
   out_7768478272277700353[36] = 0;
   out_7768478272277700353[37] = 0;
   out_7768478272277700353[38] = 0;
   out_7768478272277700353[39] = 0;
   out_7768478272277700353[40] = 0;
   out_7768478272277700353[41] = 0;
   out_7768478272277700353[42] = 0;
   out_7768478272277700353[43] = 0;
   out_7768478272277700353[44] = 1;
   out_7768478272277700353[45] = 0;
   out_7768478272277700353[46] = 0;
   out_7768478272277700353[47] = 0;
   out_7768478272277700353[48] = 0;
   out_7768478272277700353[49] = 0;
   out_7768478272277700353[50] = 0;
   out_7768478272277700353[51] = 0;
   out_7768478272277700353[52] = 0;
   out_7768478272277700353[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7527833659731555578) {
  err_fun(nom_x, delta_x, out_7527833659731555578);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8121371430920178446) {
  inv_err_fun(nom_x, true_x, out_8121371430920178446);
}
void pose_H_mod_fun(double *state, double *out_2787357462559363540) {
  H_mod_fun(state, out_2787357462559363540);
}
void pose_f_fun(double *state, double dt, double *out_2997254779517652533) {
  f_fun(state,  dt, out_2997254779517652533);
}
void pose_F_fun(double *state, double dt, double *out_3476500674504442735) {
  F_fun(state,  dt, out_3476500674504442735);
}
void pose_h_4(double *state, double *unused, double *out_2259436079279725972) {
  h_4(state, unused, out_2259436079279725972);
}
void pose_H_4(double *state, double *unused, double *out_6715024945092366734) {
  H_4(state, unused, out_6715024945092366734);
}
void pose_h_10(double *state, double *unused, double *out_4495031819694209583) {
  h_10(state, unused, out_4495031819694209583);
}
void pose_H_10(double *state, double *unused, double *out_8084729141614988184) {
  H_10(state, unused, out_8084729141614988184);
}
void pose_h_13(double *state, double *unused, double *out_7265342654384269353) {
  h_13(state, unused, out_7265342654384269353);
}
void pose_H_13(double *state, double *unused, double *out_8519445303284852081) {
  H_13(state, unused, out_8519445303284852081);
}
void pose_h_14(double *state, double *unused, double *out_2527703015463387955) {
  h_14(state, unused, out_2527703015463387955);
}
void pose_H_14(double *state, double *unused, double *out_7768478272277700353) {
  H_14(state, unused, out_7768478272277700353);
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
