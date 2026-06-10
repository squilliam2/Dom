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
void err_fun(double *nom_x, double *delta_x, double *out_5925269994359157710) {
   out_5925269994359157710[0] = delta_x[0] + nom_x[0];
   out_5925269994359157710[1] = delta_x[1] + nom_x[1];
   out_5925269994359157710[2] = delta_x[2] + nom_x[2];
   out_5925269994359157710[3] = delta_x[3] + nom_x[3];
   out_5925269994359157710[4] = delta_x[4] + nom_x[4];
   out_5925269994359157710[5] = delta_x[5] + nom_x[5];
   out_5925269994359157710[6] = delta_x[6] + nom_x[6];
   out_5925269994359157710[7] = delta_x[7] + nom_x[7];
   out_5925269994359157710[8] = delta_x[8] + nom_x[8];
   out_5925269994359157710[9] = delta_x[9] + nom_x[9];
   out_5925269994359157710[10] = delta_x[10] + nom_x[10];
   out_5925269994359157710[11] = delta_x[11] + nom_x[11];
   out_5925269994359157710[12] = delta_x[12] + nom_x[12];
   out_5925269994359157710[13] = delta_x[13] + nom_x[13];
   out_5925269994359157710[14] = delta_x[14] + nom_x[14];
   out_5925269994359157710[15] = delta_x[15] + nom_x[15];
   out_5925269994359157710[16] = delta_x[16] + nom_x[16];
   out_5925269994359157710[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5867765456190971358) {
   out_5867765456190971358[0] = -nom_x[0] + true_x[0];
   out_5867765456190971358[1] = -nom_x[1] + true_x[1];
   out_5867765456190971358[2] = -nom_x[2] + true_x[2];
   out_5867765456190971358[3] = -nom_x[3] + true_x[3];
   out_5867765456190971358[4] = -nom_x[4] + true_x[4];
   out_5867765456190971358[5] = -nom_x[5] + true_x[5];
   out_5867765456190971358[6] = -nom_x[6] + true_x[6];
   out_5867765456190971358[7] = -nom_x[7] + true_x[7];
   out_5867765456190971358[8] = -nom_x[8] + true_x[8];
   out_5867765456190971358[9] = -nom_x[9] + true_x[9];
   out_5867765456190971358[10] = -nom_x[10] + true_x[10];
   out_5867765456190971358[11] = -nom_x[11] + true_x[11];
   out_5867765456190971358[12] = -nom_x[12] + true_x[12];
   out_5867765456190971358[13] = -nom_x[13] + true_x[13];
   out_5867765456190971358[14] = -nom_x[14] + true_x[14];
   out_5867765456190971358[15] = -nom_x[15] + true_x[15];
   out_5867765456190971358[16] = -nom_x[16] + true_x[16];
   out_5867765456190971358[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4243397435317467221) {
   out_4243397435317467221[0] = 1.0;
   out_4243397435317467221[1] = 0.0;
   out_4243397435317467221[2] = 0.0;
   out_4243397435317467221[3] = 0.0;
   out_4243397435317467221[4] = 0.0;
   out_4243397435317467221[5] = 0.0;
   out_4243397435317467221[6] = 0.0;
   out_4243397435317467221[7] = 0.0;
   out_4243397435317467221[8] = 0.0;
   out_4243397435317467221[9] = 0.0;
   out_4243397435317467221[10] = 0.0;
   out_4243397435317467221[11] = 0.0;
   out_4243397435317467221[12] = 0.0;
   out_4243397435317467221[13] = 0.0;
   out_4243397435317467221[14] = 0.0;
   out_4243397435317467221[15] = 0.0;
   out_4243397435317467221[16] = 0.0;
   out_4243397435317467221[17] = 0.0;
   out_4243397435317467221[18] = 0.0;
   out_4243397435317467221[19] = 1.0;
   out_4243397435317467221[20] = 0.0;
   out_4243397435317467221[21] = 0.0;
   out_4243397435317467221[22] = 0.0;
   out_4243397435317467221[23] = 0.0;
   out_4243397435317467221[24] = 0.0;
   out_4243397435317467221[25] = 0.0;
   out_4243397435317467221[26] = 0.0;
   out_4243397435317467221[27] = 0.0;
   out_4243397435317467221[28] = 0.0;
   out_4243397435317467221[29] = 0.0;
   out_4243397435317467221[30] = 0.0;
   out_4243397435317467221[31] = 0.0;
   out_4243397435317467221[32] = 0.0;
   out_4243397435317467221[33] = 0.0;
   out_4243397435317467221[34] = 0.0;
   out_4243397435317467221[35] = 0.0;
   out_4243397435317467221[36] = 0.0;
   out_4243397435317467221[37] = 0.0;
   out_4243397435317467221[38] = 1.0;
   out_4243397435317467221[39] = 0.0;
   out_4243397435317467221[40] = 0.0;
   out_4243397435317467221[41] = 0.0;
   out_4243397435317467221[42] = 0.0;
   out_4243397435317467221[43] = 0.0;
   out_4243397435317467221[44] = 0.0;
   out_4243397435317467221[45] = 0.0;
   out_4243397435317467221[46] = 0.0;
   out_4243397435317467221[47] = 0.0;
   out_4243397435317467221[48] = 0.0;
   out_4243397435317467221[49] = 0.0;
   out_4243397435317467221[50] = 0.0;
   out_4243397435317467221[51] = 0.0;
   out_4243397435317467221[52] = 0.0;
   out_4243397435317467221[53] = 0.0;
   out_4243397435317467221[54] = 0.0;
   out_4243397435317467221[55] = 0.0;
   out_4243397435317467221[56] = 0.0;
   out_4243397435317467221[57] = 1.0;
   out_4243397435317467221[58] = 0.0;
   out_4243397435317467221[59] = 0.0;
   out_4243397435317467221[60] = 0.0;
   out_4243397435317467221[61] = 0.0;
   out_4243397435317467221[62] = 0.0;
   out_4243397435317467221[63] = 0.0;
   out_4243397435317467221[64] = 0.0;
   out_4243397435317467221[65] = 0.0;
   out_4243397435317467221[66] = 0.0;
   out_4243397435317467221[67] = 0.0;
   out_4243397435317467221[68] = 0.0;
   out_4243397435317467221[69] = 0.0;
   out_4243397435317467221[70] = 0.0;
   out_4243397435317467221[71] = 0.0;
   out_4243397435317467221[72] = 0.0;
   out_4243397435317467221[73] = 0.0;
   out_4243397435317467221[74] = 0.0;
   out_4243397435317467221[75] = 0.0;
   out_4243397435317467221[76] = 1.0;
   out_4243397435317467221[77] = 0.0;
   out_4243397435317467221[78] = 0.0;
   out_4243397435317467221[79] = 0.0;
   out_4243397435317467221[80] = 0.0;
   out_4243397435317467221[81] = 0.0;
   out_4243397435317467221[82] = 0.0;
   out_4243397435317467221[83] = 0.0;
   out_4243397435317467221[84] = 0.0;
   out_4243397435317467221[85] = 0.0;
   out_4243397435317467221[86] = 0.0;
   out_4243397435317467221[87] = 0.0;
   out_4243397435317467221[88] = 0.0;
   out_4243397435317467221[89] = 0.0;
   out_4243397435317467221[90] = 0.0;
   out_4243397435317467221[91] = 0.0;
   out_4243397435317467221[92] = 0.0;
   out_4243397435317467221[93] = 0.0;
   out_4243397435317467221[94] = 0.0;
   out_4243397435317467221[95] = 1.0;
   out_4243397435317467221[96] = 0.0;
   out_4243397435317467221[97] = 0.0;
   out_4243397435317467221[98] = 0.0;
   out_4243397435317467221[99] = 0.0;
   out_4243397435317467221[100] = 0.0;
   out_4243397435317467221[101] = 0.0;
   out_4243397435317467221[102] = 0.0;
   out_4243397435317467221[103] = 0.0;
   out_4243397435317467221[104] = 0.0;
   out_4243397435317467221[105] = 0.0;
   out_4243397435317467221[106] = 0.0;
   out_4243397435317467221[107] = 0.0;
   out_4243397435317467221[108] = 0.0;
   out_4243397435317467221[109] = 0.0;
   out_4243397435317467221[110] = 0.0;
   out_4243397435317467221[111] = 0.0;
   out_4243397435317467221[112] = 0.0;
   out_4243397435317467221[113] = 0.0;
   out_4243397435317467221[114] = 1.0;
   out_4243397435317467221[115] = 0.0;
   out_4243397435317467221[116] = 0.0;
   out_4243397435317467221[117] = 0.0;
   out_4243397435317467221[118] = 0.0;
   out_4243397435317467221[119] = 0.0;
   out_4243397435317467221[120] = 0.0;
   out_4243397435317467221[121] = 0.0;
   out_4243397435317467221[122] = 0.0;
   out_4243397435317467221[123] = 0.0;
   out_4243397435317467221[124] = 0.0;
   out_4243397435317467221[125] = 0.0;
   out_4243397435317467221[126] = 0.0;
   out_4243397435317467221[127] = 0.0;
   out_4243397435317467221[128] = 0.0;
   out_4243397435317467221[129] = 0.0;
   out_4243397435317467221[130] = 0.0;
   out_4243397435317467221[131] = 0.0;
   out_4243397435317467221[132] = 0.0;
   out_4243397435317467221[133] = 1.0;
   out_4243397435317467221[134] = 0.0;
   out_4243397435317467221[135] = 0.0;
   out_4243397435317467221[136] = 0.0;
   out_4243397435317467221[137] = 0.0;
   out_4243397435317467221[138] = 0.0;
   out_4243397435317467221[139] = 0.0;
   out_4243397435317467221[140] = 0.0;
   out_4243397435317467221[141] = 0.0;
   out_4243397435317467221[142] = 0.0;
   out_4243397435317467221[143] = 0.0;
   out_4243397435317467221[144] = 0.0;
   out_4243397435317467221[145] = 0.0;
   out_4243397435317467221[146] = 0.0;
   out_4243397435317467221[147] = 0.0;
   out_4243397435317467221[148] = 0.0;
   out_4243397435317467221[149] = 0.0;
   out_4243397435317467221[150] = 0.0;
   out_4243397435317467221[151] = 0.0;
   out_4243397435317467221[152] = 1.0;
   out_4243397435317467221[153] = 0.0;
   out_4243397435317467221[154] = 0.0;
   out_4243397435317467221[155] = 0.0;
   out_4243397435317467221[156] = 0.0;
   out_4243397435317467221[157] = 0.0;
   out_4243397435317467221[158] = 0.0;
   out_4243397435317467221[159] = 0.0;
   out_4243397435317467221[160] = 0.0;
   out_4243397435317467221[161] = 0.0;
   out_4243397435317467221[162] = 0.0;
   out_4243397435317467221[163] = 0.0;
   out_4243397435317467221[164] = 0.0;
   out_4243397435317467221[165] = 0.0;
   out_4243397435317467221[166] = 0.0;
   out_4243397435317467221[167] = 0.0;
   out_4243397435317467221[168] = 0.0;
   out_4243397435317467221[169] = 0.0;
   out_4243397435317467221[170] = 0.0;
   out_4243397435317467221[171] = 1.0;
   out_4243397435317467221[172] = 0.0;
   out_4243397435317467221[173] = 0.0;
   out_4243397435317467221[174] = 0.0;
   out_4243397435317467221[175] = 0.0;
   out_4243397435317467221[176] = 0.0;
   out_4243397435317467221[177] = 0.0;
   out_4243397435317467221[178] = 0.0;
   out_4243397435317467221[179] = 0.0;
   out_4243397435317467221[180] = 0.0;
   out_4243397435317467221[181] = 0.0;
   out_4243397435317467221[182] = 0.0;
   out_4243397435317467221[183] = 0.0;
   out_4243397435317467221[184] = 0.0;
   out_4243397435317467221[185] = 0.0;
   out_4243397435317467221[186] = 0.0;
   out_4243397435317467221[187] = 0.0;
   out_4243397435317467221[188] = 0.0;
   out_4243397435317467221[189] = 0.0;
   out_4243397435317467221[190] = 1.0;
   out_4243397435317467221[191] = 0.0;
   out_4243397435317467221[192] = 0.0;
   out_4243397435317467221[193] = 0.0;
   out_4243397435317467221[194] = 0.0;
   out_4243397435317467221[195] = 0.0;
   out_4243397435317467221[196] = 0.0;
   out_4243397435317467221[197] = 0.0;
   out_4243397435317467221[198] = 0.0;
   out_4243397435317467221[199] = 0.0;
   out_4243397435317467221[200] = 0.0;
   out_4243397435317467221[201] = 0.0;
   out_4243397435317467221[202] = 0.0;
   out_4243397435317467221[203] = 0.0;
   out_4243397435317467221[204] = 0.0;
   out_4243397435317467221[205] = 0.0;
   out_4243397435317467221[206] = 0.0;
   out_4243397435317467221[207] = 0.0;
   out_4243397435317467221[208] = 0.0;
   out_4243397435317467221[209] = 1.0;
   out_4243397435317467221[210] = 0.0;
   out_4243397435317467221[211] = 0.0;
   out_4243397435317467221[212] = 0.0;
   out_4243397435317467221[213] = 0.0;
   out_4243397435317467221[214] = 0.0;
   out_4243397435317467221[215] = 0.0;
   out_4243397435317467221[216] = 0.0;
   out_4243397435317467221[217] = 0.0;
   out_4243397435317467221[218] = 0.0;
   out_4243397435317467221[219] = 0.0;
   out_4243397435317467221[220] = 0.0;
   out_4243397435317467221[221] = 0.0;
   out_4243397435317467221[222] = 0.0;
   out_4243397435317467221[223] = 0.0;
   out_4243397435317467221[224] = 0.0;
   out_4243397435317467221[225] = 0.0;
   out_4243397435317467221[226] = 0.0;
   out_4243397435317467221[227] = 0.0;
   out_4243397435317467221[228] = 1.0;
   out_4243397435317467221[229] = 0.0;
   out_4243397435317467221[230] = 0.0;
   out_4243397435317467221[231] = 0.0;
   out_4243397435317467221[232] = 0.0;
   out_4243397435317467221[233] = 0.0;
   out_4243397435317467221[234] = 0.0;
   out_4243397435317467221[235] = 0.0;
   out_4243397435317467221[236] = 0.0;
   out_4243397435317467221[237] = 0.0;
   out_4243397435317467221[238] = 0.0;
   out_4243397435317467221[239] = 0.0;
   out_4243397435317467221[240] = 0.0;
   out_4243397435317467221[241] = 0.0;
   out_4243397435317467221[242] = 0.0;
   out_4243397435317467221[243] = 0.0;
   out_4243397435317467221[244] = 0.0;
   out_4243397435317467221[245] = 0.0;
   out_4243397435317467221[246] = 0.0;
   out_4243397435317467221[247] = 1.0;
   out_4243397435317467221[248] = 0.0;
   out_4243397435317467221[249] = 0.0;
   out_4243397435317467221[250] = 0.0;
   out_4243397435317467221[251] = 0.0;
   out_4243397435317467221[252] = 0.0;
   out_4243397435317467221[253] = 0.0;
   out_4243397435317467221[254] = 0.0;
   out_4243397435317467221[255] = 0.0;
   out_4243397435317467221[256] = 0.0;
   out_4243397435317467221[257] = 0.0;
   out_4243397435317467221[258] = 0.0;
   out_4243397435317467221[259] = 0.0;
   out_4243397435317467221[260] = 0.0;
   out_4243397435317467221[261] = 0.0;
   out_4243397435317467221[262] = 0.0;
   out_4243397435317467221[263] = 0.0;
   out_4243397435317467221[264] = 0.0;
   out_4243397435317467221[265] = 0.0;
   out_4243397435317467221[266] = 1.0;
   out_4243397435317467221[267] = 0.0;
   out_4243397435317467221[268] = 0.0;
   out_4243397435317467221[269] = 0.0;
   out_4243397435317467221[270] = 0.0;
   out_4243397435317467221[271] = 0.0;
   out_4243397435317467221[272] = 0.0;
   out_4243397435317467221[273] = 0.0;
   out_4243397435317467221[274] = 0.0;
   out_4243397435317467221[275] = 0.0;
   out_4243397435317467221[276] = 0.0;
   out_4243397435317467221[277] = 0.0;
   out_4243397435317467221[278] = 0.0;
   out_4243397435317467221[279] = 0.0;
   out_4243397435317467221[280] = 0.0;
   out_4243397435317467221[281] = 0.0;
   out_4243397435317467221[282] = 0.0;
   out_4243397435317467221[283] = 0.0;
   out_4243397435317467221[284] = 0.0;
   out_4243397435317467221[285] = 1.0;
   out_4243397435317467221[286] = 0.0;
   out_4243397435317467221[287] = 0.0;
   out_4243397435317467221[288] = 0.0;
   out_4243397435317467221[289] = 0.0;
   out_4243397435317467221[290] = 0.0;
   out_4243397435317467221[291] = 0.0;
   out_4243397435317467221[292] = 0.0;
   out_4243397435317467221[293] = 0.0;
   out_4243397435317467221[294] = 0.0;
   out_4243397435317467221[295] = 0.0;
   out_4243397435317467221[296] = 0.0;
   out_4243397435317467221[297] = 0.0;
   out_4243397435317467221[298] = 0.0;
   out_4243397435317467221[299] = 0.0;
   out_4243397435317467221[300] = 0.0;
   out_4243397435317467221[301] = 0.0;
   out_4243397435317467221[302] = 0.0;
   out_4243397435317467221[303] = 0.0;
   out_4243397435317467221[304] = 1.0;
   out_4243397435317467221[305] = 0.0;
   out_4243397435317467221[306] = 0.0;
   out_4243397435317467221[307] = 0.0;
   out_4243397435317467221[308] = 0.0;
   out_4243397435317467221[309] = 0.0;
   out_4243397435317467221[310] = 0.0;
   out_4243397435317467221[311] = 0.0;
   out_4243397435317467221[312] = 0.0;
   out_4243397435317467221[313] = 0.0;
   out_4243397435317467221[314] = 0.0;
   out_4243397435317467221[315] = 0.0;
   out_4243397435317467221[316] = 0.0;
   out_4243397435317467221[317] = 0.0;
   out_4243397435317467221[318] = 0.0;
   out_4243397435317467221[319] = 0.0;
   out_4243397435317467221[320] = 0.0;
   out_4243397435317467221[321] = 0.0;
   out_4243397435317467221[322] = 0.0;
   out_4243397435317467221[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5333365637221194880) {
   out_5333365637221194880[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5333365637221194880[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5333365637221194880[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5333365637221194880[3] = dt*state[12] + state[3];
   out_5333365637221194880[4] = dt*state[13] + state[4];
   out_5333365637221194880[5] = dt*state[14] + state[5];
   out_5333365637221194880[6] = state[6];
   out_5333365637221194880[7] = state[7];
   out_5333365637221194880[8] = state[8];
   out_5333365637221194880[9] = state[9];
   out_5333365637221194880[10] = state[10];
   out_5333365637221194880[11] = state[11];
   out_5333365637221194880[12] = state[12];
   out_5333365637221194880[13] = state[13];
   out_5333365637221194880[14] = state[14];
   out_5333365637221194880[15] = state[15];
   out_5333365637221194880[16] = state[16];
   out_5333365637221194880[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8848460606148442442) {
   out_8848460606148442442[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8848460606148442442[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8848460606148442442[2] = 0;
   out_8848460606148442442[3] = 0;
   out_8848460606148442442[4] = 0;
   out_8848460606148442442[5] = 0;
   out_8848460606148442442[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8848460606148442442[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8848460606148442442[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8848460606148442442[9] = 0;
   out_8848460606148442442[10] = 0;
   out_8848460606148442442[11] = 0;
   out_8848460606148442442[12] = 0;
   out_8848460606148442442[13] = 0;
   out_8848460606148442442[14] = 0;
   out_8848460606148442442[15] = 0;
   out_8848460606148442442[16] = 0;
   out_8848460606148442442[17] = 0;
   out_8848460606148442442[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8848460606148442442[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8848460606148442442[20] = 0;
   out_8848460606148442442[21] = 0;
   out_8848460606148442442[22] = 0;
   out_8848460606148442442[23] = 0;
   out_8848460606148442442[24] = 0;
   out_8848460606148442442[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8848460606148442442[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8848460606148442442[27] = 0;
   out_8848460606148442442[28] = 0;
   out_8848460606148442442[29] = 0;
   out_8848460606148442442[30] = 0;
   out_8848460606148442442[31] = 0;
   out_8848460606148442442[32] = 0;
   out_8848460606148442442[33] = 0;
   out_8848460606148442442[34] = 0;
   out_8848460606148442442[35] = 0;
   out_8848460606148442442[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8848460606148442442[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8848460606148442442[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8848460606148442442[39] = 0;
   out_8848460606148442442[40] = 0;
   out_8848460606148442442[41] = 0;
   out_8848460606148442442[42] = 0;
   out_8848460606148442442[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8848460606148442442[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8848460606148442442[45] = 0;
   out_8848460606148442442[46] = 0;
   out_8848460606148442442[47] = 0;
   out_8848460606148442442[48] = 0;
   out_8848460606148442442[49] = 0;
   out_8848460606148442442[50] = 0;
   out_8848460606148442442[51] = 0;
   out_8848460606148442442[52] = 0;
   out_8848460606148442442[53] = 0;
   out_8848460606148442442[54] = 0;
   out_8848460606148442442[55] = 0;
   out_8848460606148442442[56] = 0;
   out_8848460606148442442[57] = 1;
   out_8848460606148442442[58] = 0;
   out_8848460606148442442[59] = 0;
   out_8848460606148442442[60] = 0;
   out_8848460606148442442[61] = 0;
   out_8848460606148442442[62] = 0;
   out_8848460606148442442[63] = 0;
   out_8848460606148442442[64] = 0;
   out_8848460606148442442[65] = 0;
   out_8848460606148442442[66] = dt;
   out_8848460606148442442[67] = 0;
   out_8848460606148442442[68] = 0;
   out_8848460606148442442[69] = 0;
   out_8848460606148442442[70] = 0;
   out_8848460606148442442[71] = 0;
   out_8848460606148442442[72] = 0;
   out_8848460606148442442[73] = 0;
   out_8848460606148442442[74] = 0;
   out_8848460606148442442[75] = 0;
   out_8848460606148442442[76] = 1;
   out_8848460606148442442[77] = 0;
   out_8848460606148442442[78] = 0;
   out_8848460606148442442[79] = 0;
   out_8848460606148442442[80] = 0;
   out_8848460606148442442[81] = 0;
   out_8848460606148442442[82] = 0;
   out_8848460606148442442[83] = 0;
   out_8848460606148442442[84] = 0;
   out_8848460606148442442[85] = dt;
   out_8848460606148442442[86] = 0;
   out_8848460606148442442[87] = 0;
   out_8848460606148442442[88] = 0;
   out_8848460606148442442[89] = 0;
   out_8848460606148442442[90] = 0;
   out_8848460606148442442[91] = 0;
   out_8848460606148442442[92] = 0;
   out_8848460606148442442[93] = 0;
   out_8848460606148442442[94] = 0;
   out_8848460606148442442[95] = 1;
   out_8848460606148442442[96] = 0;
   out_8848460606148442442[97] = 0;
   out_8848460606148442442[98] = 0;
   out_8848460606148442442[99] = 0;
   out_8848460606148442442[100] = 0;
   out_8848460606148442442[101] = 0;
   out_8848460606148442442[102] = 0;
   out_8848460606148442442[103] = 0;
   out_8848460606148442442[104] = dt;
   out_8848460606148442442[105] = 0;
   out_8848460606148442442[106] = 0;
   out_8848460606148442442[107] = 0;
   out_8848460606148442442[108] = 0;
   out_8848460606148442442[109] = 0;
   out_8848460606148442442[110] = 0;
   out_8848460606148442442[111] = 0;
   out_8848460606148442442[112] = 0;
   out_8848460606148442442[113] = 0;
   out_8848460606148442442[114] = 1;
   out_8848460606148442442[115] = 0;
   out_8848460606148442442[116] = 0;
   out_8848460606148442442[117] = 0;
   out_8848460606148442442[118] = 0;
   out_8848460606148442442[119] = 0;
   out_8848460606148442442[120] = 0;
   out_8848460606148442442[121] = 0;
   out_8848460606148442442[122] = 0;
   out_8848460606148442442[123] = 0;
   out_8848460606148442442[124] = 0;
   out_8848460606148442442[125] = 0;
   out_8848460606148442442[126] = 0;
   out_8848460606148442442[127] = 0;
   out_8848460606148442442[128] = 0;
   out_8848460606148442442[129] = 0;
   out_8848460606148442442[130] = 0;
   out_8848460606148442442[131] = 0;
   out_8848460606148442442[132] = 0;
   out_8848460606148442442[133] = 1;
   out_8848460606148442442[134] = 0;
   out_8848460606148442442[135] = 0;
   out_8848460606148442442[136] = 0;
   out_8848460606148442442[137] = 0;
   out_8848460606148442442[138] = 0;
   out_8848460606148442442[139] = 0;
   out_8848460606148442442[140] = 0;
   out_8848460606148442442[141] = 0;
   out_8848460606148442442[142] = 0;
   out_8848460606148442442[143] = 0;
   out_8848460606148442442[144] = 0;
   out_8848460606148442442[145] = 0;
   out_8848460606148442442[146] = 0;
   out_8848460606148442442[147] = 0;
   out_8848460606148442442[148] = 0;
   out_8848460606148442442[149] = 0;
   out_8848460606148442442[150] = 0;
   out_8848460606148442442[151] = 0;
   out_8848460606148442442[152] = 1;
   out_8848460606148442442[153] = 0;
   out_8848460606148442442[154] = 0;
   out_8848460606148442442[155] = 0;
   out_8848460606148442442[156] = 0;
   out_8848460606148442442[157] = 0;
   out_8848460606148442442[158] = 0;
   out_8848460606148442442[159] = 0;
   out_8848460606148442442[160] = 0;
   out_8848460606148442442[161] = 0;
   out_8848460606148442442[162] = 0;
   out_8848460606148442442[163] = 0;
   out_8848460606148442442[164] = 0;
   out_8848460606148442442[165] = 0;
   out_8848460606148442442[166] = 0;
   out_8848460606148442442[167] = 0;
   out_8848460606148442442[168] = 0;
   out_8848460606148442442[169] = 0;
   out_8848460606148442442[170] = 0;
   out_8848460606148442442[171] = 1;
   out_8848460606148442442[172] = 0;
   out_8848460606148442442[173] = 0;
   out_8848460606148442442[174] = 0;
   out_8848460606148442442[175] = 0;
   out_8848460606148442442[176] = 0;
   out_8848460606148442442[177] = 0;
   out_8848460606148442442[178] = 0;
   out_8848460606148442442[179] = 0;
   out_8848460606148442442[180] = 0;
   out_8848460606148442442[181] = 0;
   out_8848460606148442442[182] = 0;
   out_8848460606148442442[183] = 0;
   out_8848460606148442442[184] = 0;
   out_8848460606148442442[185] = 0;
   out_8848460606148442442[186] = 0;
   out_8848460606148442442[187] = 0;
   out_8848460606148442442[188] = 0;
   out_8848460606148442442[189] = 0;
   out_8848460606148442442[190] = 1;
   out_8848460606148442442[191] = 0;
   out_8848460606148442442[192] = 0;
   out_8848460606148442442[193] = 0;
   out_8848460606148442442[194] = 0;
   out_8848460606148442442[195] = 0;
   out_8848460606148442442[196] = 0;
   out_8848460606148442442[197] = 0;
   out_8848460606148442442[198] = 0;
   out_8848460606148442442[199] = 0;
   out_8848460606148442442[200] = 0;
   out_8848460606148442442[201] = 0;
   out_8848460606148442442[202] = 0;
   out_8848460606148442442[203] = 0;
   out_8848460606148442442[204] = 0;
   out_8848460606148442442[205] = 0;
   out_8848460606148442442[206] = 0;
   out_8848460606148442442[207] = 0;
   out_8848460606148442442[208] = 0;
   out_8848460606148442442[209] = 1;
   out_8848460606148442442[210] = 0;
   out_8848460606148442442[211] = 0;
   out_8848460606148442442[212] = 0;
   out_8848460606148442442[213] = 0;
   out_8848460606148442442[214] = 0;
   out_8848460606148442442[215] = 0;
   out_8848460606148442442[216] = 0;
   out_8848460606148442442[217] = 0;
   out_8848460606148442442[218] = 0;
   out_8848460606148442442[219] = 0;
   out_8848460606148442442[220] = 0;
   out_8848460606148442442[221] = 0;
   out_8848460606148442442[222] = 0;
   out_8848460606148442442[223] = 0;
   out_8848460606148442442[224] = 0;
   out_8848460606148442442[225] = 0;
   out_8848460606148442442[226] = 0;
   out_8848460606148442442[227] = 0;
   out_8848460606148442442[228] = 1;
   out_8848460606148442442[229] = 0;
   out_8848460606148442442[230] = 0;
   out_8848460606148442442[231] = 0;
   out_8848460606148442442[232] = 0;
   out_8848460606148442442[233] = 0;
   out_8848460606148442442[234] = 0;
   out_8848460606148442442[235] = 0;
   out_8848460606148442442[236] = 0;
   out_8848460606148442442[237] = 0;
   out_8848460606148442442[238] = 0;
   out_8848460606148442442[239] = 0;
   out_8848460606148442442[240] = 0;
   out_8848460606148442442[241] = 0;
   out_8848460606148442442[242] = 0;
   out_8848460606148442442[243] = 0;
   out_8848460606148442442[244] = 0;
   out_8848460606148442442[245] = 0;
   out_8848460606148442442[246] = 0;
   out_8848460606148442442[247] = 1;
   out_8848460606148442442[248] = 0;
   out_8848460606148442442[249] = 0;
   out_8848460606148442442[250] = 0;
   out_8848460606148442442[251] = 0;
   out_8848460606148442442[252] = 0;
   out_8848460606148442442[253] = 0;
   out_8848460606148442442[254] = 0;
   out_8848460606148442442[255] = 0;
   out_8848460606148442442[256] = 0;
   out_8848460606148442442[257] = 0;
   out_8848460606148442442[258] = 0;
   out_8848460606148442442[259] = 0;
   out_8848460606148442442[260] = 0;
   out_8848460606148442442[261] = 0;
   out_8848460606148442442[262] = 0;
   out_8848460606148442442[263] = 0;
   out_8848460606148442442[264] = 0;
   out_8848460606148442442[265] = 0;
   out_8848460606148442442[266] = 1;
   out_8848460606148442442[267] = 0;
   out_8848460606148442442[268] = 0;
   out_8848460606148442442[269] = 0;
   out_8848460606148442442[270] = 0;
   out_8848460606148442442[271] = 0;
   out_8848460606148442442[272] = 0;
   out_8848460606148442442[273] = 0;
   out_8848460606148442442[274] = 0;
   out_8848460606148442442[275] = 0;
   out_8848460606148442442[276] = 0;
   out_8848460606148442442[277] = 0;
   out_8848460606148442442[278] = 0;
   out_8848460606148442442[279] = 0;
   out_8848460606148442442[280] = 0;
   out_8848460606148442442[281] = 0;
   out_8848460606148442442[282] = 0;
   out_8848460606148442442[283] = 0;
   out_8848460606148442442[284] = 0;
   out_8848460606148442442[285] = 1;
   out_8848460606148442442[286] = 0;
   out_8848460606148442442[287] = 0;
   out_8848460606148442442[288] = 0;
   out_8848460606148442442[289] = 0;
   out_8848460606148442442[290] = 0;
   out_8848460606148442442[291] = 0;
   out_8848460606148442442[292] = 0;
   out_8848460606148442442[293] = 0;
   out_8848460606148442442[294] = 0;
   out_8848460606148442442[295] = 0;
   out_8848460606148442442[296] = 0;
   out_8848460606148442442[297] = 0;
   out_8848460606148442442[298] = 0;
   out_8848460606148442442[299] = 0;
   out_8848460606148442442[300] = 0;
   out_8848460606148442442[301] = 0;
   out_8848460606148442442[302] = 0;
   out_8848460606148442442[303] = 0;
   out_8848460606148442442[304] = 1;
   out_8848460606148442442[305] = 0;
   out_8848460606148442442[306] = 0;
   out_8848460606148442442[307] = 0;
   out_8848460606148442442[308] = 0;
   out_8848460606148442442[309] = 0;
   out_8848460606148442442[310] = 0;
   out_8848460606148442442[311] = 0;
   out_8848460606148442442[312] = 0;
   out_8848460606148442442[313] = 0;
   out_8848460606148442442[314] = 0;
   out_8848460606148442442[315] = 0;
   out_8848460606148442442[316] = 0;
   out_8848460606148442442[317] = 0;
   out_8848460606148442442[318] = 0;
   out_8848460606148442442[319] = 0;
   out_8848460606148442442[320] = 0;
   out_8848460606148442442[321] = 0;
   out_8848460606148442442[322] = 0;
   out_8848460606148442442[323] = 1;
}
void h_4(double *state, double *unused, double *out_2926038800219696097) {
   out_2926038800219696097[0] = state[6] + state[9];
   out_2926038800219696097[1] = state[7] + state[10];
   out_2926038800219696097[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_9050828253353003660) {
   out_9050828253353003660[0] = 0;
   out_9050828253353003660[1] = 0;
   out_9050828253353003660[2] = 0;
   out_9050828253353003660[3] = 0;
   out_9050828253353003660[4] = 0;
   out_9050828253353003660[5] = 0;
   out_9050828253353003660[6] = 1;
   out_9050828253353003660[7] = 0;
   out_9050828253353003660[8] = 0;
   out_9050828253353003660[9] = 1;
   out_9050828253353003660[10] = 0;
   out_9050828253353003660[11] = 0;
   out_9050828253353003660[12] = 0;
   out_9050828253353003660[13] = 0;
   out_9050828253353003660[14] = 0;
   out_9050828253353003660[15] = 0;
   out_9050828253353003660[16] = 0;
   out_9050828253353003660[17] = 0;
   out_9050828253353003660[18] = 0;
   out_9050828253353003660[19] = 0;
   out_9050828253353003660[20] = 0;
   out_9050828253353003660[21] = 0;
   out_9050828253353003660[22] = 0;
   out_9050828253353003660[23] = 0;
   out_9050828253353003660[24] = 0;
   out_9050828253353003660[25] = 1;
   out_9050828253353003660[26] = 0;
   out_9050828253353003660[27] = 0;
   out_9050828253353003660[28] = 1;
   out_9050828253353003660[29] = 0;
   out_9050828253353003660[30] = 0;
   out_9050828253353003660[31] = 0;
   out_9050828253353003660[32] = 0;
   out_9050828253353003660[33] = 0;
   out_9050828253353003660[34] = 0;
   out_9050828253353003660[35] = 0;
   out_9050828253353003660[36] = 0;
   out_9050828253353003660[37] = 0;
   out_9050828253353003660[38] = 0;
   out_9050828253353003660[39] = 0;
   out_9050828253353003660[40] = 0;
   out_9050828253353003660[41] = 0;
   out_9050828253353003660[42] = 0;
   out_9050828253353003660[43] = 0;
   out_9050828253353003660[44] = 1;
   out_9050828253353003660[45] = 0;
   out_9050828253353003660[46] = 0;
   out_9050828253353003660[47] = 1;
   out_9050828253353003660[48] = 0;
   out_9050828253353003660[49] = 0;
   out_9050828253353003660[50] = 0;
   out_9050828253353003660[51] = 0;
   out_9050828253353003660[52] = 0;
   out_9050828253353003660[53] = 0;
}
void h_10(double *state, double *unused, double *out_3754295376293318230) {
   out_3754295376293318230[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3754295376293318230[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3754295376293318230[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2912584995031240051) {
   out_2912584995031240051[0] = 0;
   out_2912584995031240051[1] = 9.8100000000000005*cos(state[1]);
   out_2912584995031240051[2] = 0;
   out_2912584995031240051[3] = 0;
   out_2912584995031240051[4] = -state[8];
   out_2912584995031240051[5] = state[7];
   out_2912584995031240051[6] = 0;
   out_2912584995031240051[7] = state[5];
   out_2912584995031240051[8] = -state[4];
   out_2912584995031240051[9] = 0;
   out_2912584995031240051[10] = 0;
   out_2912584995031240051[11] = 0;
   out_2912584995031240051[12] = 1;
   out_2912584995031240051[13] = 0;
   out_2912584995031240051[14] = 0;
   out_2912584995031240051[15] = 1;
   out_2912584995031240051[16] = 0;
   out_2912584995031240051[17] = 0;
   out_2912584995031240051[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2912584995031240051[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2912584995031240051[20] = 0;
   out_2912584995031240051[21] = state[8];
   out_2912584995031240051[22] = 0;
   out_2912584995031240051[23] = -state[6];
   out_2912584995031240051[24] = -state[5];
   out_2912584995031240051[25] = 0;
   out_2912584995031240051[26] = state[3];
   out_2912584995031240051[27] = 0;
   out_2912584995031240051[28] = 0;
   out_2912584995031240051[29] = 0;
   out_2912584995031240051[30] = 0;
   out_2912584995031240051[31] = 1;
   out_2912584995031240051[32] = 0;
   out_2912584995031240051[33] = 0;
   out_2912584995031240051[34] = 1;
   out_2912584995031240051[35] = 0;
   out_2912584995031240051[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2912584995031240051[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2912584995031240051[38] = 0;
   out_2912584995031240051[39] = -state[7];
   out_2912584995031240051[40] = state[6];
   out_2912584995031240051[41] = 0;
   out_2912584995031240051[42] = state[4];
   out_2912584995031240051[43] = -state[3];
   out_2912584995031240051[44] = 0;
   out_2912584995031240051[45] = 0;
   out_2912584995031240051[46] = 0;
   out_2912584995031240051[47] = 0;
   out_2912584995031240051[48] = 0;
   out_2912584995031240051[49] = 0;
   out_2912584995031240051[50] = 1;
   out_2912584995031240051[51] = 0;
   out_2912584995031240051[52] = 0;
   out_2912584995031240051[53] = 1;
}
void h_13(double *state, double *unused, double *out_4089270074398195787) {
   out_4089270074398195787[0] = state[3];
   out_4089270074398195787[1] = state[4];
   out_4089270074398195787[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5838554428020670859) {
   out_5838554428020670859[0] = 0;
   out_5838554428020670859[1] = 0;
   out_5838554428020670859[2] = 0;
   out_5838554428020670859[3] = 1;
   out_5838554428020670859[4] = 0;
   out_5838554428020670859[5] = 0;
   out_5838554428020670859[6] = 0;
   out_5838554428020670859[7] = 0;
   out_5838554428020670859[8] = 0;
   out_5838554428020670859[9] = 0;
   out_5838554428020670859[10] = 0;
   out_5838554428020670859[11] = 0;
   out_5838554428020670859[12] = 0;
   out_5838554428020670859[13] = 0;
   out_5838554428020670859[14] = 0;
   out_5838554428020670859[15] = 0;
   out_5838554428020670859[16] = 0;
   out_5838554428020670859[17] = 0;
   out_5838554428020670859[18] = 0;
   out_5838554428020670859[19] = 0;
   out_5838554428020670859[20] = 0;
   out_5838554428020670859[21] = 0;
   out_5838554428020670859[22] = 1;
   out_5838554428020670859[23] = 0;
   out_5838554428020670859[24] = 0;
   out_5838554428020670859[25] = 0;
   out_5838554428020670859[26] = 0;
   out_5838554428020670859[27] = 0;
   out_5838554428020670859[28] = 0;
   out_5838554428020670859[29] = 0;
   out_5838554428020670859[30] = 0;
   out_5838554428020670859[31] = 0;
   out_5838554428020670859[32] = 0;
   out_5838554428020670859[33] = 0;
   out_5838554428020670859[34] = 0;
   out_5838554428020670859[35] = 0;
   out_5838554428020670859[36] = 0;
   out_5838554428020670859[37] = 0;
   out_5838554428020670859[38] = 0;
   out_5838554428020670859[39] = 0;
   out_5838554428020670859[40] = 0;
   out_5838554428020670859[41] = 1;
   out_5838554428020670859[42] = 0;
   out_5838554428020670859[43] = 0;
   out_5838554428020670859[44] = 0;
   out_5838554428020670859[45] = 0;
   out_5838554428020670859[46] = 0;
   out_5838554428020670859[47] = 0;
   out_5838554428020670859[48] = 0;
   out_5838554428020670859[49] = 0;
   out_5838554428020670859[50] = 0;
   out_5838554428020670859[51] = 0;
   out_5838554428020670859[52] = 0;
   out_5838554428020670859[53] = 0;
}
void h_14(double *state, double *unused, double *out_9176020735288104700) {
   out_9176020735288104700[0] = state[6];
   out_9176020735288104700[1] = state[7];
   out_9176020735288104700[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5087587397013519131) {
   out_5087587397013519131[0] = 0;
   out_5087587397013519131[1] = 0;
   out_5087587397013519131[2] = 0;
   out_5087587397013519131[3] = 0;
   out_5087587397013519131[4] = 0;
   out_5087587397013519131[5] = 0;
   out_5087587397013519131[6] = 1;
   out_5087587397013519131[7] = 0;
   out_5087587397013519131[8] = 0;
   out_5087587397013519131[9] = 0;
   out_5087587397013519131[10] = 0;
   out_5087587397013519131[11] = 0;
   out_5087587397013519131[12] = 0;
   out_5087587397013519131[13] = 0;
   out_5087587397013519131[14] = 0;
   out_5087587397013519131[15] = 0;
   out_5087587397013519131[16] = 0;
   out_5087587397013519131[17] = 0;
   out_5087587397013519131[18] = 0;
   out_5087587397013519131[19] = 0;
   out_5087587397013519131[20] = 0;
   out_5087587397013519131[21] = 0;
   out_5087587397013519131[22] = 0;
   out_5087587397013519131[23] = 0;
   out_5087587397013519131[24] = 0;
   out_5087587397013519131[25] = 1;
   out_5087587397013519131[26] = 0;
   out_5087587397013519131[27] = 0;
   out_5087587397013519131[28] = 0;
   out_5087587397013519131[29] = 0;
   out_5087587397013519131[30] = 0;
   out_5087587397013519131[31] = 0;
   out_5087587397013519131[32] = 0;
   out_5087587397013519131[33] = 0;
   out_5087587397013519131[34] = 0;
   out_5087587397013519131[35] = 0;
   out_5087587397013519131[36] = 0;
   out_5087587397013519131[37] = 0;
   out_5087587397013519131[38] = 0;
   out_5087587397013519131[39] = 0;
   out_5087587397013519131[40] = 0;
   out_5087587397013519131[41] = 0;
   out_5087587397013519131[42] = 0;
   out_5087587397013519131[43] = 0;
   out_5087587397013519131[44] = 1;
   out_5087587397013519131[45] = 0;
   out_5087587397013519131[46] = 0;
   out_5087587397013519131[47] = 0;
   out_5087587397013519131[48] = 0;
   out_5087587397013519131[49] = 0;
   out_5087587397013519131[50] = 0;
   out_5087587397013519131[51] = 0;
   out_5087587397013519131[52] = 0;
   out_5087587397013519131[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5925269994359157710) {
  err_fun(nom_x, delta_x, out_5925269994359157710);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5867765456190971358) {
  inv_err_fun(nom_x, true_x, out_5867765456190971358);
}
void pose_H_mod_fun(double *state, double *out_4243397435317467221) {
  H_mod_fun(state, out_4243397435317467221);
}
void pose_f_fun(double *state, double dt, double *out_5333365637221194880) {
  f_fun(state,  dt, out_5333365637221194880);
}
void pose_F_fun(double *state, double dt, double *out_8848460606148442442) {
  F_fun(state,  dt, out_8848460606148442442);
}
void pose_h_4(double *state, double *unused, double *out_2926038800219696097) {
  h_4(state, unused, out_2926038800219696097);
}
void pose_H_4(double *state, double *unused, double *out_9050828253353003660) {
  H_4(state, unused, out_9050828253353003660);
}
void pose_h_10(double *state, double *unused, double *out_3754295376293318230) {
  h_10(state, unused, out_3754295376293318230);
}
void pose_H_10(double *state, double *unused, double *out_2912584995031240051) {
  H_10(state, unused, out_2912584995031240051);
}
void pose_h_13(double *state, double *unused, double *out_4089270074398195787) {
  h_13(state, unused, out_4089270074398195787);
}
void pose_H_13(double *state, double *unused, double *out_5838554428020670859) {
  H_13(state, unused, out_5838554428020670859);
}
void pose_h_14(double *state, double *unused, double *out_9176020735288104700) {
  h_14(state, unused, out_9176020735288104700);
}
void pose_H_14(double *state, double *unused, double *out_5087587397013519131) {
  H_14(state, unused, out_5087587397013519131);
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
