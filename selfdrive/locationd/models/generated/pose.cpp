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
void err_fun(double *nom_x, double *delta_x, double *out_7150506142011136089) {
   out_7150506142011136089[0] = delta_x[0] + nom_x[0];
   out_7150506142011136089[1] = delta_x[1] + nom_x[1];
   out_7150506142011136089[2] = delta_x[2] + nom_x[2];
   out_7150506142011136089[3] = delta_x[3] + nom_x[3];
   out_7150506142011136089[4] = delta_x[4] + nom_x[4];
   out_7150506142011136089[5] = delta_x[5] + nom_x[5];
   out_7150506142011136089[6] = delta_x[6] + nom_x[6];
   out_7150506142011136089[7] = delta_x[7] + nom_x[7];
   out_7150506142011136089[8] = delta_x[8] + nom_x[8];
   out_7150506142011136089[9] = delta_x[9] + nom_x[9];
   out_7150506142011136089[10] = delta_x[10] + nom_x[10];
   out_7150506142011136089[11] = delta_x[11] + nom_x[11];
   out_7150506142011136089[12] = delta_x[12] + nom_x[12];
   out_7150506142011136089[13] = delta_x[13] + nom_x[13];
   out_7150506142011136089[14] = delta_x[14] + nom_x[14];
   out_7150506142011136089[15] = delta_x[15] + nom_x[15];
   out_7150506142011136089[16] = delta_x[16] + nom_x[16];
   out_7150506142011136089[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4307514453378045812) {
   out_4307514453378045812[0] = -nom_x[0] + true_x[0];
   out_4307514453378045812[1] = -nom_x[1] + true_x[1];
   out_4307514453378045812[2] = -nom_x[2] + true_x[2];
   out_4307514453378045812[3] = -nom_x[3] + true_x[3];
   out_4307514453378045812[4] = -nom_x[4] + true_x[4];
   out_4307514453378045812[5] = -nom_x[5] + true_x[5];
   out_4307514453378045812[6] = -nom_x[6] + true_x[6];
   out_4307514453378045812[7] = -nom_x[7] + true_x[7];
   out_4307514453378045812[8] = -nom_x[8] + true_x[8];
   out_4307514453378045812[9] = -nom_x[9] + true_x[9];
   out_4307514453378045812[10] = -nom_x[10] + true_x[10];
   out_4307514453378045812[11] = -nom_x[11] + true_x[11];
   out_4307514453378045812[12] = -nom_x[12] + true_x[12];
   out_4307514453378045812[13] = -nom_x[13] + true_x[13];
   out_4307514453378045812[14] = -nom_x[14] + true_x[14];
   out_4307514453378045812[15] = -nom_x[15] + true_x[15];
   out_4307514453378045812[16] = -nom_x[16] + true_x[16];
   out_4307514453378045812[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_526209948270695177) {
   out_526209948270695177[0] = 1.0;
   out_526209948270695177[1] = 0.0;
   out_526209948270695177[2] = 0.0;
   out_526209948270695177[3] = 0.0;
   out_526209948270695177[4] = 0.0;
   out_526209948270695177[5] = 0.0;
   out_526209948270695177[6] = 0.0;
   out_526209948270695177[7] = 0.0;
   out_526209948270695177[8] = 0.0;
   out_526209948270695177[9] = 0.0;
   out_526209948270695177[10] = 0.0;
   out_526209948270695177[11] = 0.0;
   out_526209948270695177[12] = 0.0;
   out_526209948270695177[13] = 0.0;
   out_526209948270695177[14] = 0.0;
   out_526209948270695177[15] = 0.0;
   out_526209948270695177[16] = 0.0;
   out_526209948270695177[17] = 0.0;
   out_526209948270695177[18] = 0.0;
   out_526209948270695177[19] = 1.0;
   out_526209948270695177[20] = 0.0;
   out_526209948270695177[21] = 0.0;
   out_526209948270695177[22] = 0.0;
   out_526209948270695177[23] = 0.0;
   out_526209948270695177[24] = 0.0;
   out_526209948270695177[25] = 0.0;
   out_526209948270695177[26] = 0.0;
   out_526209948270695177[27] = 0.0;
   out_526209948270695177[28] = 0.0;
   out_526209948270695177[29] = 0.0;
   out_526209948270695177[30] = 0.0;
   out_526209948270695177[31] = 0.0;
   out_526209948270695177[32] = 0.0;
   out_526209948270695177[33] = 0.0;
   out_526209948270695177[34] = 0.0;
   out_526209948270695177[35] = 0.0;
   out_526209948270695177[36] = 0.0;
   out_526209948270695177[37] = 0.0;
   out_526209948270695177[38] = 1.0;
   out_526209948270695177[39] = 0.0;
   out_526209948270695177[40] = 0.0;
   out_526209948270695177[41] = 0.0;
   out_526209948270695177[42] = 0.0;
   out_526209948270695177[43] = 0.0;
   out_526209948270695177[44] = 0.0;
   out_526209948270695177[45] = 0.0;
   out_526209948270695177[46] = 0.0;
   out_526209948270695177[47] = 0.0;
   out_526209948270695177[48] = 0.0;
   out_526209948270695177[49] = 0.0;
   out_526209948270695177[50] = 0.0;
   out_526209948270695177[51] = 0.0;
   out_526209948270695177[52] = 0.0;
   out_526209948270695177[53] = 0.0;
   out_526209948270695177[54] = 0.0;
   out_526209948270695177[55] = 0.0;
   out_526209948270695177[56] = 0.0;
   out_526209948270695177[57] = 1.0;
   out_526209948270695177[58] = 0.0;
   out_526209948270695177[59] = 0.0;
   out_526209948270695177[60] = 0.0;
   out_526209948270695177[61] = 0.0;
   out_526209948270695177[62] = 0.0;
   out_526209948270695177[63] = 0.0;
   out_526209948270695177[64] = 0.0;
   out_526209948270695177[65] = 0.0;
   out_526209948270695177[66] = 0.0;
   out_526209948270695177[67] = 0.0;
   out_526209948270695177[68] = 0.0;
   out_526209948270695177[69] = 0.0;
   out_526209948270695177[70] = 0.0;
   out_526209948270695177[71] = 0.0;
   out_526209948270695177[72] = 0.0;
   out_526209948270695177[73] = 0.0;
   out_526209948270695177[74] = 0.0;
   out_526209948270695177[75] = 0.0;
   out_526209948270695177[76] = 1.0;
   out_526209948270695177[77] = 0.0;
   out_526209948270695177[78] = 0.0;
   out_526209948270695177[79] = 0.0;
   out_526209948270695177[80] = 0.0;
   out_526209948270695177[81] = 0.0;
   out_526209948270695177[82] = 0.0;
   out_526209948270695177[83] = 0.0;
   out_526209948270695177[84] = 0.0;
   out_526209948270695177[85] = 0.0;
   out_526209948270695177[86] = 0.0;
   out_526209948270695177[87] = 0.0;
   out_526209948270695177[88] = 0.0;
   out_526209948270695177[89] = 0.0;
   out_526209948270695177[90] = 0.0;
   out_526209948270695177[91] = 0.0;
   out_526209948270695177[92] = 0.0;
   out_526209948270695177[93] = 0.0;
   out_526209948270695177[94] = 0.0;
   out_526209948270695177[95] = 1.0;
   out_526209948270695177[96] = 0.0;
   out_526209948270695177[97] = 0.0;
   out_526209948270695177[98] = 0.0;
   out_526209948270695177[99] = 0.0;
   out_526209948270695177[100] = 0.0;
   out_526209948270695177[101] = 0.0;
   out_526209948270695177[102] = 0.0;
   out_526209948270695177[103] = 0.0;
   out_526209948270695177[104] = 0.0;
   out_526209948270695177[105] = 0.0;
   out_526209948270695177[106] = 0.0;
   out_526209948270695177[107] = 0.0;
   out_526209948270695177[108] = 0.0;
   out_526209948270695177[109] = 0.0;
   out_526209948270695177[110] = 0.0;
   out_526209948270695177[111] = 0.0;
   out_526209948270695177[112] = 0.0;
   out_526209948270695177[113] = 0.0;
   out_526209948270695177[114] = 1.0;
   out_526209948270695177[115] = 0.0;
   out_526209948270695177[116] = 0.0;
   out_526209948270695177[117] = 0.0;
   out_526209948270695177[118] = 0.0;
   out_526209948270695177[119] = 0.0;
   out_526209948270695177[120] = 0.0;
   out_526209948270695177[121] = 0.0;
   out_526209948270695177[122] = 0.0;
   out_526209948270695177[123] = 0.0;
   out_526209948270695177[124] = 0.0;
   out_526209948270695177[125] = 0.0;
   out_526209948270695177[126] = 0.0;
   out_526209948270695177[127] = 0.0;
   out_526209948270695177[128] = 0.0;
   out_526209948270695177[129] = 0.0;
   out_526209948270695177[130] = 0.0;
   out_526209948270695177[131] = 0.0;
   out_526209948270695177[132] = 0.0;
   out_526209948270695177[133] = 1.0;
   out_526209948270695177[134] = 0.0;
   out_526209948270695177[135] = 0.0;
   out_526209948270695177[136] = 0.0;
   out_526209948270695177[137] = 0.0;
   out_526209948270695177[138] = 0.0;
   out_526209948270695177[139] = 0.0;
   out_526209948270695177[140] = 0.0;
   out_526209948270695177[141] = 0.0;
   out_526209948270695177[142] = 0.0;
   out_526209948270695177[143] = 0.0;
   out_526209948270695177[144] = 0.0;
   out_526209948270695177[145] = 0.0;
   out_526209948270695177[146] = 0.0;
   out_526209948270695177[147] = 0.0;
   out_526209948270695177[148] = 0.0;
   out_526209948270695177[149] = 0.0;
   out_526209948270695177[150] = 0.0;
   out_526209948270695177[151] = 0.0;
   out_526209948270695177[152] = 1.0;
   out_526209948270695177[153] = 0.0;
   out_526209948270695177[154] = 0.0;
   out_526209948270695177[155] = 0.0;
   out_526209948270695177[156] = 0.0;
   out_526209948270695177[157] = 0.0;
   out_526209948270695177[158] = 0.0;
   out_526209948270695177[159] = 0.0;
   out_526209948270695177[160] = 0.0;
   out_526209948270695177[161] = 0.0;
   out_526209948270695177[162] = 0.0;
   out_526209948270695177[163] = 0.0;
   out_526209948270695177[164] = 0.0;
   out_526209948270695177[165] = 0.0;
   out_526209948270695177[166] = 0.0;
   out_526209948270695177[167] = 0.0;
   out_526209948270695177[168] = 0.0;
   out_526209948270695177[169] = 0.0;
   out_526209948270695177[170] = 0.0;
   out_526209948270695177[171] = 1.0;
   out_526209948270695177[172] = 0.0;
   out_526209948270695177[173] = 0.0;
   out_526209948270695177[174] = 0.0;
   out_526209948270695177[175] = 0.0;
   out_526209948270695177[176] = 0.0;
   out_526209948270695177[177] = 0.0;
   out_526209948270695177[178] = 0.0;
   out_526209948270695177[179] = 0.0;
   out_526209948270695177[180] = 0.0;
   out_526209948270695177[181] = 0.0;
   out_526209948270695177[182] = 0.0;
   out_526209948270695177[183] = 0.0;
   out_526209948270695177[184] = 0.0;
   out_526209948270695177[185] = 0.0;
   out_526209948270695177[186] = 0.0;
   out_526209948270695177[187] = 0.0;
   out_526209948270695177[188] = 0.0;
   out_526209948270695177[189] = 0.0;
   out_526209948270695177[190] = 1.0;
   out_526209948270695177[191] = 0.0;
   out_526209948270695177[192] = 0.0;
   out_526209948270695177[193] = 0.0;
   out_526209948270695177[194] = 0.0;
   out_526209948270695177[195] = 0.0;
   out_526209948270695177[196] = 0.0;
   out_526209948270695177[197] = 0.0;
   out_526209948270695177[198] = 0.0;
   out_526209948270695177[199] = 0.0;
   out_526209948270695177[200] = 0.0;
   out_526209948270695177[201] = 0.0;
   out_526209948270695177[202] = 0.0;
   out_526209948270695177[203] = 0.0;
   out_526209948270695177[204] = 0.0;
   out_526209948270695177[205] = 0.0;
   out_526209948270695177[206] = 0.0;
   out_526209948270695177[207] = 0.0;
   out_526209948270695177[208] = 0.0;
   out_526209948270695177[209] = 1.0;
   out_526209948270695177[210] = 0.0;
   out_526209948270695177[211] = 0.0;
   out_526209948270695177[212] = 0.0;
   out_526209948270695177[213] = 0.0;
   out_526209948270695177[214] = 0.0;
   out_526209948270695177[215] = 0.0;
   out_526209948270695177[216] = 0.0;
   out_526209948270695177[217] = 0.0;
   out_526209948270695177[218] = 0.0;
   out_526209948270695177[219] = 0.0;
   out_526209948270695177[220] = 0.0;
   out_526209948270695177[221] = 0.0;
   out_526209948270695177[222] = 0.0;
   out_526209948270695177[223] = 0.0;
   out_526209948270695177[224] = 0.0;
   out_526209948270695177[225] = 0.0;
   out_526209948270695177[226] = 0.0;
   out_526209948270695177[227] = 0.0;
   out_526209948270695177[228] = 1.0;
   out_526209948270695177[229] = 0.0;
   out_526209948270695177[230] = 0.0;
   out_526209948270695177[231] = 0.0;
   out_526209948270695177[232] = 0.0;
   out_526209948270695177[233] = 0.0;
   out_526209948270695177[234] = 0.0;
   out_526209948270695177[235] = 0.0;
   out_526209948270695177[236] = 0.0;
   out_526209948270695177[237] = 0.0;
   out_526209948270695177[238] = 0.0;
   out_526209948270695177[239] = 0.0;
   out_526209948270695177[240] = 0.0;
   out_526209948270695177[241] = 0.0;
   out_526209948270695177[242] = 0.0;
   out_526209948270695177[243] = 0.0;
   out_526209948270695177[244] = 0.0;
   out_526209948270695177[245] = 0.0;
   out_526209948270695177[246] = 0.0;
   out_526209948270695177[247] = 1.0;
   out_526209948270695177[248] = 0.0;
   out_526209948270695177[249] = 0.0;
   out_526209948270695177[250] = 0.0;
   out_526209948270695177[251] = 0.0;
   out_526209948270695177[252] = 0.0;
   out_526209948270695177[253] = 0.0;
   out_526209948270695177[254] = 0.0;
   out_526209948270695177[255] = 0.0;
   out_526209948270695177[256] = 0.0;
   out_526209948270695177[257] = 0.0;
   out_526209948270695177[258] = 0.0;
   out_526209948270695177[259] = 0.0;
   out_526209948270695177[260] = 0.0;
   out_526209948270695177[261] = 0.0;
   out_526209948270695177[262] = 0.0;
   out_526209948270695177[263] = 0.0;
   out_526209948270695177[264] = 0.0;
   out_526209948270695177[265] = 0.0;
   out_526209948270695177[266] = 1.0;
   out_526209948270695177[267] = 0.0;
   out_526209948270695177[268] = 0.0;
   out_526209948270695177[269] = 0.0;
   out_526209948270695177[270] = 0.0;
   out_526209948270695177[271] = 0.0;
   out_526209948270695177[272] = 0.0;
   out_526209948270695177[273] = 0.0;
   out_526209948270695177[274] = 0.0;
   out_526209948270695177[275] = 0.0;
   out_526209948270695177[276] = 0.0;
   out_526209948270695177[277] = 0.0;
   out_526209948270695177[278] = 0.0;
   out_526209948270695177[279] = 0.0;
   out_526209948270695177[280] = 0.0;
   out_526209948270695177[281] = 0.0;
   out_526209948270695177[282] = 0.0;
   out_526209948270695177[283] = 0.0;
   out_526209948270695177[284] = 0.0;
   out_526209948270695177[285] = 1.0;
   out_526209948270695177[286] = 0.0;
   out_526209948270695177[287] = 0.0;
   out_526209948270695177[288] = 0.0;
   out_526209948270695177[289] = 0.0;
   out_526209948270695177[290] = 0.0;
   out_526209948270695177[291] = 0.0;
   out_526209948270695177[292] = 0.0;
   out_526209948270695177[293] = 0.0;
   out_526209948270695177[294] = 0.0;
   out_526209948270695177[295] = 0.0;
   out_526209948270695177[296] = 0.0;
   out_526209948270695177[297] = 0.0;
   out_526209948270695177[298] = 0.0;
   out_526209948270695177[299] = 0.0;
   out_526209948270695177[300] = 0.0;
   out_526209948270695177[301] = 0.0;
   out_526209948270695177[302] = 0.0;
   out_526209948270695177[303] = 0.0;
   out_526209948270695177[304] = 1.0;
   out_526209948270695177[305] = 0.0;
   out_526209948270695177[306] = 0.0;
   out_526209948270695177[307] = 0.0;
   out_526209948270695177[308] = 0.0;
   out_526209948270695177[309] = 0.0;
   out_526209948270695177[310] = 0.0;
   out_526209948270695177[311] = 0.0;
   out_526209948270695177[312] = 0.0;
   out_526209948270695177[313] = 0.0;
   out_526209948270695177[314] = 0.0;
   out_526209948270695177[315] = 0.0;
   out_526209948270695177[316] = 0.0;
   out_526209948270695177[317] = 0.0;
   out_526209948270695177[318] = 0.0;
   out_526209948270695177[319] = 0.0;
   out_526209948270695177[320] = 0.0;
   out_526209948270695177[321] = 0.0;
   out_526209948270695177[322] = 0.0;
   out_526209948270695177[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_826153410981652937) {
   out_826153410981652937[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_826153410981652937[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_826153410981652937[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_826153410981652937[3] = dt*state[12] + state[3];
   out_826153410981652937[4] = dt*state[13] + state[4];
   out_826153410981652937[5] = dt*state[14] + state[5];
   out_826153410981652937[6] = state[6];
   out_826153410981652937[7] = state[7];
   out_826153410981652937[8] = state[8];
   out_826153410981652937[9] = state[9];
   out_826153410981652937[10] = state[10];
   out_826153410981652937[11] = state[11];
   out_826153410981652937[12] = state[12];
   out_826153410981652937[13] = state[13];
   out_826153410981652937[14] = state[14];
   out_826153410981652937[15] = state[15];
   out_826153410981652937[16] = state[16];
   out_826153410981652937[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2504584572758712159) {
   out_2504584572758712159[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504584572758712159[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504584572758712159[2] = 0;
   out_2504584572758712159[3] = 0;
   out_2504584572758712159[4] = 0;
   out_2504584572758712159[5] = 0;
   out_2504584572758712159[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504584572758712159[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504584572758712159[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2504584572758712159[9] = 0;
   out_2504584572758712159[10] = 0;
   out_2504584572758712159[11] = 0;
   out_2504584572758712159[12] = 0;
   out_2504584572758712159[13] = 0;
   out_2504584572758712159[14] = 0;
   out_2504584572758712159[15] = 0;
   out_2504584572758712159[16] = 0;
   out_2504584572758712159[17] = 0;
   out_2504584572758712159[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504584572758712159[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504584572758712159[20] = 0;
   out_2504584572758712159[21] = 0;
   out_2504584572758712159[22] = 0;
   out_2504584572758712159[23] = 0;
   out_2504584572758712159[24] = 0;
   out_2504584572758712159[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504584572758712159[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2504584572758712159[27] = 0;
   out_2504584572758712159[28] = 0;
   out_2504584572758712159[29] = 0;
   out_2504584572758712159[30] = 0;
   out_2504584572758712159[31] = 0;
   out_2504584572758712159[32] = 0;
   out_2504584572758712159[33] = 0;
   out_2504584572758712159[34] = 0;
   out_2504584572758712159[35] = 0;
   out_2504584572758712159[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504584572758712159[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504584572758712159[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504584572758712159[39] = 0;
   out_2504584572758712159[40] = 0;
   out_2504584572758712159[41] = 0;
   out_2504584572758712159[42] = 0;
   out_2504584572758712159[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504584572758712159[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2504584572758712159[45] = 0;
   out_2504584572758712159[46] = 0;
   out_2504584572758712159[47] = 0;
   out_2504584572758712159[48] = 0;
   out_2504584572758712159[49] = 0;
   out_2504584572758712159[50] = 0;
   out_2504584572758712159[51] = 0;
   out_2504584572758712159[52] = 0;
   out_2504584572758712159[53] = 0;
   out_2504584572758712159[54] = 0;
   out_2504584572758712159[55] = 0;
   out_2504584572758712159[56] = 0;
   out_2504584572758712159[57] = 1;
   out_2504584572758712159[58] = 0;
   out_2504584572758712159[59] = 0;
   out_2504584572758712159[60] = 0;
   out_2504584572758712159[61] = 0;
   out_2504584572758712159[62] = 0;
   out_2504584572758712159[63] = 0;
   out_2504584572758712159[64] = 0;
   out_2504584572758712159[65] = 0;
   out_2504584572758712159[66] = dt;
   out_2504584572758712159[67] = 0;
   out_2504584572758712159[68] = 0;
   out_2504584572758712159[69] = 0;
   out_2504584572758712159[70] = 0;
   out_2504584572758712159[71] = 0;
   out_2504584572758712159[72] = 0;
   out_2504584572758712159[73] = 0;
   out_2504584572758712159[74] = 0;
   out_2504584572758712159[75] = 0;
   out_2504584572758712159[76] = 1;
   out_2504584572758712159[77] = 0;
   out_2504584572758712159[78] = 0;
   out_2504584572758712159[79] = 0;
   out_2504584572758712159[80] = 0;
   out_2504584572758712159[81] = 0;
   out_2504584572758712159[82] = 0;
   out_2504584572758712159[83] = 0;
   out_2504584572758712159[84] = 0;
   out_2504584572758712159[85] = dt;
   out_2504584572758712159[86] = 0;
   out_2504584572758712159[87] = 0;
   out_2504584572758712159[88] = 0;
   out_2504584572758712159[89] = 0;
   out_2504584572758712159[90] = 0;
   out_2504584572758712159[91] = 0;
   out_2504584572758712159[92] = 0;
   out_2504584572758712159[93] = 0;
   out_2504584572758712159[94] = 0;
   out_2504584572758712159[95] = 1;
   out_2504584572758712159[96] = 0;
   out_2504584572758712159[97] = 0;
   out_2504584572758712159[98] = 0;
   out_2504584572758712159[99] = 0;
   out_2504584572758712159[100] = 0;
   out_2504584572758712159[101] = 0;
   out_2504584572758712159[102] = 0;
   out_2504584572758712159[103] = 0;
   out_2504584572758712159[104] = dt;
   out_2504584572758712159[105] = 0;
   out_2504584572758712159[106] = 0;
   out_2504584572758712159[107] = 0;
   out_2504584572758712159[108] = 0;
   out_2504584572758712159[109] = 0;
   out_2504584572758712159[110] = 0;
   out_2504584572758712159[111] = 0;
   out_2504584572758712159[112] = 0;
   out_2504584572758712159[113] = 0;
   out_2504584572758712159[114] = 1;
   out_2504584572758712159[115] = 0;
   out_2504584572758712159[116] = 0;
   out_2504584572758712159[117] = 0;
   out_2504584572758712159[118] = 0;
   out_2504584572758712159[119] = 0;
   out_2504584572758712159[120] = 0;
   out_2504584572758712159[121] = 0;
   out_2504584572758712159[122] = 0;
   out_2504584572758712159[123] = 0;
   out_2504584572758712159[124] = 0;
   out_2504584572758712159[125] = 0;
   out_2504584572758712159[126] = 0;
   out_2504584572758712159[127] = 0;
   out_2504584572758712159[128] = 0;
   out_2504584572758712159[129] = 0;
   out_2504584572758712159[130] = 0;
   out_2504584572758712159[131] = 0;
   out_2504584572758712159[132] = 0;
   out_2504584572758712159[133] = 1;
   out_2504584572758712159[134] = 0;
   out_2504584572758712159[135] = 0;
   out_2504584572758712159[136] = 0;
   out_2504584572758712159[137] = 0;
   out_2504584572758712159[138] = 0;
   out_2504584572758712159[139] = 0;
   out_2504584572758712159[140] = 0;
   out_2504584572758712159[141] = 0;
   out_2504584572758712159[142] = 0;
   out_2504584572758712159[143] = 0;
   out_2504584572758712159[144] = 0;
   out_2504584572758712159[145] = 0;
   out_2504584572758712159[146] = 0;
   out_2504584572758712159[147] = 0;
   out_2504584572758712159[148] = 0;
   out_2504584572758712159[149] = 0;
   out_2504584572758712159[150] = 0;
   out_2504584572758712159[151] = 0;
   out_2504584572758712159[152] = 1;
   out_2504584572758712159[153] = 0;
   out_2504584572758712159[154] = 0;
   out_2504584572758712159[155] = 0;
   out_2504584572758712159[156] = 0;
   out_2504584572758712159[157] = 0;
   out_2504584572758712159[158] = 0;
   out_2504584572758712159[159] = 0;
   out_2504584572758712159[160] = 0;
   out_2504584572758712159[161] = 0;
   out_2504584572758712159[162] = 0;
   out_2504584572758712159[163] = 0;
   out_2504584572758712159[164] = 0;
   out_2504584572758712159[165] = 0;
   out_2504584572758712159[166] = 0;
   out_2504584572758712159[167] = 0;
   out_2504584572758712159[168] = 0;
   out_2504584572758712159[169] = 0;
   out_2504584572758712159[170] = 0;
   out_2504584572758712159[171] = 1;
   out_2504584572758712159[172] = 0;
   out_2504584572758712159[173] = 0;
   out_2504584572758712159[174] = 0;
   out_2504584572758712159[175] = 0;
   out_2504584572758712159[176] = 0;
   out_2504584572758712159[177] = 0;
   out_2504584572758712159[178] = 0;
   out_2504584572758712159[179] = 0;
   out_2504584572758712159[180] = 0;
   out_2504584572758712159[181] = 0;
   out_2504584572758712159[182] = 0;
   out_2504584572758712159[183] = 0;
   out_2504584572758712159[184] = 0;
   out_2504584572758712159[185] = 0;
   out_2504584572758712159[186] = 0;
   out_2504584572758712159[187] = 0;
   out_2504584572758712159[188] = 0;
   out_2504584572758712159[189] = 0;
   out_2504584572758712159[190] = 1;
   out_2504584572758712159[191] = 0;
   out_2504584572758712159[192] = 0;
   out_2504584572758712159[193] = 0;
   out_2504584572758712159[194] = 0;
   out_2504584572758712159[195] = 0;
   out_2504584572758712159[196] = 0;
   out_2504584572758712159[197] = 0;
   out_2504584572758712159[198] = 0;
   out_2504584572758712159[199] = 0;
   out_2504584572758712159[200] = 0;
   out_2504584572758712159[201] = 0;
   out_2504584572758712159[202] = 0;
   out_2504584572758712159[203] = 0;
   out_2504584572758712159[204] = 0;
   out_2504584572758712159[205] = 0;
   out_2504584572758712159[206] = 0;
   out_2504584572758712159[207] = 0;
   out_2504584572758712159[208] = 0;
   out_2504584572758712159[209] = 1;
   out_2504584572758712159[210] = 0;
   out_2504584572758712159[211] = 0;
   out_2504584572758712159[212] = 0;
   out_2504584572758712159[213] = 0;
   out_2504584572758712159[214] = 0;
   out_2504584572758712159[215] = 0;
   out_2504584572758712159[216] = 0;
   out_2504584572758712159[217] = 0;
   out_2504584572758712159[218] = 0;
   out_2504584572758712159[219] = 0;
   out_2504584572758712159[220] = 0;
   out_2504584572758712159[221] = 0;
   out_2504584572758712159[222] = 0;
   out_2504584572758712159[223] = 0;
   out_2504584572758712159[224] = 0;
   out_2504584572758712159[225] = 0;
   out_2504584572758712159[226] = 0;
   out_2504584572758712159[227] = 0;
   out_2504584572758712159[228] = 1;
   out_2504584572758712159[229] = 0;
   out_2504584572758712159[230] = 0;
   out_2504584572758712159[231] = 0;
   out_2504584572758712159[232] = 0;
   out_2504584572758712159[233] = 0;
   out_2504584572758712159[234] = 0;
   out_2504584572758712159[235] = 0;
   out_2504584572758712159[236] = 0;
   out_2504584572758712159[237] = 0;
   out_2504584572758712159[238] = 0;
   out_2504584572758712159[239] = 0;
   out_2504584572758712159[240] = 0;
   out_2504584572758712159[241] = 0;
   out_2504584572758712159[242] = 0;
   out_2504584572758712159[243] = 0;
   out_2504584572758712159[244] = 0;
   out_2504584572758712159[245] = 0;
   out_2504584572758712159[246] = 0;
   out_2504584572758712159[247] = 1;
   out_2504584572758712159[248] = 0;
   out_2504584572758712159[249] = 0;
   out_2504584572758712159[250] = 0;
   out_2504584572758712159[251] = 0;
   out_2504584572758712159[252] = 0;
   out_2504584572758712159[253] = 0;
   out_2504584572758712159[254] = 0;
   out_2504584572758712159[255] = 0;
   out_2504584572758712159[256] = 0;
   out_2504584572758712159[257] = 0;
   out_2504584572758712159[258] = 0;
   out_2504584572758712159[259] = 0;
   out_2504584572758712159[260] = 0;
   out_2504584572758712159[261] = 0;
   out_2504584572758712159[262] = 0;
   out_2504584572758712159[263] = 0;
   out_2504584572758712159[264] = 0;
   out_2504584572758712159[265] = 0;
   out_2504584572758712159[266] = 1;
   out_2504584572758712159[267] = 0;
   out_2504584572758712159[268] = 0;
   out_2504584572758712159[269] = 0;
   out_2504584572758712159[270] = 0;
   out_2504584572758712159[271] = 0;
   out_2504584572758712159[272] = 0;
   out_2504584572758712159[273] = 0;
   out_2504584572758712159[274] = 0;
   out_2504584572758712159[275] = 0;
   out_2504584572758712159[276] = 0;
   out_2504584572758712159[277] = 0;
   out_2504584572758712159[278] = 0;
   out_2504584572758712159[279] = 0;
   out_2504584572758712159[280] = 0;
   out_2504584572758712159[281] = 0;
   out_2504584572758712159[282] = 0;
   out_2504584572758712159[283] = 0;
   out_2504584572758712159[284] = 0;
   out_2504584572758712159[285] = 1;
   out_2504584572758712159[286] = 0;
   out_2504584572758712159[287] = 0;
   out_2504584572758712159[288] = 0;
   out_2504584572758712159[289] = 0;
   out_2504584572758712159[290] = 0;
   out_2504584572758712159[291] = 0;
   out_2504584572758712159[292] = 0;
   out_2504584572758712159[293] = 0;
   out_2504584572758712159[294] = 0;
   out_2504584572758712159[295] = 0;
   out_2504584572758712159[296] = 0;
   out_2504584572758712159[297] = 0;
   out_2504584572758712159[298] = 0;
   out_2504584572758712159[299] = 0;
   out_2504584572758712159[300] = 0;
   out_2504584572758712159[301] = 0;
   out_2504584572758712159[302] = 0;
   out_2504584572758712159[303] = 0;
   out_2504584572758712159[304] = 1;
   out_2504584572758712159[305] = 0;
   out_2504584572758712159[306] = 0;
   out_2504584572758712159[307] = 0;
   out_2504584572758712159[308] = 0;
   out_2504584572758712159[309] = 0;
   out_2504584572758712159[310] = 0;
   out_2504584572758712159[311] = 0;
   out_2504584572758712159[312] = 0;
   out_2504584572758712159[313] = 0;
   out_2504584572758712159[314] = 0;
   out_2504584572758712159[315] = 0;
   out_2504584572758712159[316] = 0;
   out_2504584572758712159[317] = 0;
   out_2504584572758712159[318] = 0;
   out_2504584572758712159[319] = 0;
   out_2504584572758712159[320] = 0;
   out_2504584572758712159[321] = 0;
   out_2504584572758712159[322] = 0;
   out_2504584572758712159[323] = 1;
}
void h_4(double *state, double *unused, double *out_7442480903303367172) {
   out_7442480903303367172[0] = state[6] + state[9];
   out_7442480903303367172[1] = state[7] + state[10];
   out_7442480903303367172[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3800432027061644430) {
   out_3800432027061644430[0] = 0;
   out_3800432027061644430[1] = 0;
   out_3800432027061644430[2] = 0;
   out_3800432027061644430[3] = 0;
   out_3800432027061644430[4] = 0;
   out_3800432027061644430[5] = 0;
   out_3800432027061644430[6] = 1;
   out_3800432027061644430[7] = 0;
   out_3800432027061644430[8] = 0;
   out_3800432027061644430[9] = 1;
   out_3800432027061644430[10] = 0;
   out_3800432027061644430[11] = 0;
   out_3800432027061644430[12] = 0;
   out_3800432027061644430[13] = 0;
   out_3800432027061644430[14] = 0;
   out_3800432027061644430[15] = 0;
   out_3800432027061644430[16] = 0;
   out_3800432027061644430[17] = 0;
   out_3800432027061644430[18] = 0;
   out_3800432027061644430[19] = 0;
   out_3800432027061644430[20] = 0;
   out_3800432027061644430[21] = 0;
   out_3800432027061644430[22] = 0;
   out_3800432027061644430[23] = 0;
   out_3800432027061644430[24] = 0;
   out_3800432027061644430[25] = 1;
   out_3800432027061644430[26] = 0;
   out_3800432027061644430[27] = 0;
   out_3800432027061644430[28] = 1;
   out_3800432027061644430[29] = 0;
   out_3800432027061644430[30] = 0;
   out_3800432027061644430[31] = 0;
   out_3800432027061644430[32] = 0;
   out_3800432027061644430[33] = 0;
   out_3800432027061644430[34] = 0;
   out_3800432027061644430[35] = 0;
   out_3800432027061644430[36] = 0;
   out_3800432027061644430[37] = 0;
   out_3800432027061644430[38] = 0;
   out_3800432027061644430[39] = 0;
   out_3800432027061644430[40] = 0;
   out_3800432027061644430[41] = 0;
   out_3800432027061644430[42] = 0;
   out_3800432027061644430[43] = 0;
   out_3800432027061644430[44] = 1;
   out_3800432027061644430[45] = 0;
   out_3800432027061644430[46] = 0;
   out_3800432027061644430[47] = 1;
   out_3800432027061644430[48] = 0;
   out_3800432027061644430[49] = 0;
   out_3800432027061644430[50] = 0;
   out_3800432027061644430[51] = 0;
   out_3800432027061644430[52] = 0;
   out_3800432027061644430[53] = 0;
}
void h_10(double *state, double *unused, double *out_8932011361837519248) {
   out_8932011361837519248[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8932011361837519248[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8932011361837519248[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4464178208942290131) {
   out_4464178208942290131[0] = 0;
   out_4464178208942290131[1] = 9.8100000000000005*cos(state[1]);
   out_4464178208942290131[2] = 0;
   out_4464178208942290131[3] = 0;
   out_4464178208942290131[4] = -state[8];
   out_4464178208942290131[5] = state[7];
   out_4464178208942290131[6] = 0;
   out_4464178208942290131[7] = state[5];
   out_4464178208942290131[8] = -state[4];
   out_4464178208942290131[9] = 0;
   out_4464178208942290131[10] = 0;
   out_4464178208942290131[11] = 0;
   out_4464178208942290131[12] = 1;
   out_4464178208942290131[13] = 0;
   out_4464178208942290131[14] = 0;
   out_4464178208942290131[15] = 1;
   out_4464178208942290131[16] = 0;
   out_4464178208942290131[17] = 0;
   out_4464178208942290131[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4464178208942290131[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4464178208942290131[20] = 0;
   out_4464178208942290131[21] = state[8];
   out_4464178208942290131[22] = 0;
   out_4464178208942290131[23] = -state[6];
   out_4464178208942290131[24] = -state[5];
   out_4464178208942290131[25] = 0;
   out_4464178208942290131[26] = state[3];
   out_4464178208942290131[27] = 0;
   out_4464178208942290131[28] = 0;
   out_4464178208942290131[29] = 0;
   out_4464178208942290131[30] = 0;
   out_4464178208942290131[31] = 1;
   out_4464178208942290131[32] = 0;
   out_4464178208942290131[33] = 0;
   out_4464178208942290131[34] = 1;
   out_4464178208942290131[35] = 0;
   out_4464178208942290131[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4464178208942290131[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4464178208942290131[38] = 0;
   out_4464178208942290131[39] = -state[7];
   out_4464178208942290131[40] = state[6];
   out_4464178208942290131[41] = 0;
   out_4464178208942290131[42] = state[4];
   out_4464178208942290131[43] = -state[3];
   out_4464178208942290131[44] = 0;
   out_4464178208942290131[45] = 0;
   out_4464178208942290131[46] = 0;
   out_4464178208942290131[47] = 0;
   out_4464178208942290131[48] = 0;
   out_4464178208942290131[49] = 0;
   out_4464178208942290131[50] = 1;
   out_4464178208942290131[51] = 0;
   out_4464178208942290131[52] = 0;
   out_4464178208942290131[53] = 1;
}
void h_13(double *state, double *unused, double *out_6459110219088517442) {
   out_6459110219088517442[0] = state[3];
   out_6459110219088517442[1] = state[4];
   out_6459110219088517442[2] = state[5];
}
void H_13(double *state, double *unused, double *out_588158201729311629) {
   out_588158201729311629[0] = 0;
   out_588158201729311629[1] = 0;
   out_588158201729311629[2] = 0;
   out_588158201729311629[3] = 1;
   out_588158201729311629[4] = 0;
   out_588158201729311629[5] = 0;
   out_588158201729311629[6] = 0;
   out_588158201729311629[7] = 0;
   out_588158201729311629[8] = 0;
   out_588158201729311629[9] = 0;
   out_588158201729311629[10] = 0;
   out_588158201729311629[11] = 0;
   out_588158201729311629[12] = 0;
   out_588158201729311629[13] = 0;
   out_588158201729311629[14] = 0;
   out_588158201729311629[15] = 0;
   out_588158201729311629[16] = 0;
   out_588158201729311629[17] = 0;
   out_588158201729311629[18] = 0;
   out_588158201729311629[19] = 0;
   out_588158201729311629[20] = 0;
   out_588158201729311629[21] = 0;
   out_588158201729311629[22] = 1;
   out_588158201729311629[23] = 0;
   out_588158201729311629[24] = 0;
   out_588158201729311629[25] = 0;
   out_588158201729311629[26] = 0;
   out_588158201729311629[27] = 0;
   out_588158201729311629[28] = 0;
   out_588158201729311629[29] = 0;
   out_588158201729311629[30] = 0;
   out_588158201729311629[31] = 0;
   out_588158201729311629[32] = 0;
   out_588158201729311629[33] = 0;
   out_588158201729311629[34] = 0;
   out_588158201729311629[35] = 0;
   out_588158201729311629[36] = 0;
   out_588158201729311629[37] = 0;
   out_588158201729311629[38] = 0;
   out_588158201729311629[39] = 0;
   out_588158201729311629[40] = 0;
   out_588158201729311629[41] = 1;
   out_588158201729311629[42] = 0;
   out_588158201729311629[43] = 0;
   out_588158201729311629[44] = 0;
   out_588158201729311629[45] = 0;
   out_588158201729311629[46] = 0;
   out_588158201729311629[47] = 0;
   out_588158201729311629[48] = 0;
   out_588158201729311629[49] = 0;
   out_588158201729311629[50] = 0;
   out_588158201729311629[51] = 0;
   out_588158201729311629[52] = 0;
   out_588158201729311629[53] = 0;
}
void h_14(double *state, double *unused, double *out_7025019117935111535) {
   out_7025019117935111535[0] = state[6];
   out_7025019117935111535[1] = state[7];
   out_7025019117935111535[2] = state[8];
}
void H_14(double *state, double *unused, double *out_162808829277840099) {
   out_162808829277840099[0] = 0;
   out_162808829277840099[1] = 0;
   out_162808829277840099[2] = 0;
   out_162808829277840099[3] = 0;
   out_162808829277840099[4] = 0;
   out_162808829277840099[5] = 0;
   out_162808829277840099[6] = 1;
   out_162808829277840099[7] = 0;
   out_162808829277840099[8] = 0;
   out_162808829277840099[9] = 0;
   out_162808829277840099[10] = 0;
   out_162808829277840099[11] = 0;
   out_162808829277840099[12] = 0;
   out_162808829277840099[13] = 0;
   out_162808829277840099[14] = 0;
   out_162808829277840099[15] = 0;
   out_162808829277840099[16] = 0;
   out_162808829277840099[17] = 0;
   out_162808829277840099[18] = 0;
   out_162808829277840099[19] = 0;
   out_162808829277840099[20] = 0;
   out_162808829277840099[21] = 0;
   out_162808829277840099[22] = 0;
   out_162808829277840099[23] = 0;
   out_162808829277840099[24] = 0;
   out_162808829277840099[25] = 1;
   out_162808829277840099[26] = 0;
   out_162808829277840099[27] = 0;
   out_162808829277840099[28] = 0;
   out_162808829277840099[29] = 0;
   out_162808829277840099[30] = 0;
   out_162808829277840099[31] = 0;
   out_162808829277840099[32] = 0;
   out_162808829277840099[33] = 0;
   out_162808829277840099[34] = 0;
   out_162808829277840099[35] = 0;
   out_162808829277840099[36] = 0;
   out_162808829277840099[37] = 0;
   out_162808829277840099[38] = 0;
   out_162808829277840099[39] = 0;
   out_162808829277840099[40] = 0;
   out_162808829277840099[41] = 0;
   out_162808829277840099[42] = 0;
   out_162808829277840099[43] = 0;
   out_162808829277840099[44] = 1;
   out_162808829277840099[45] = 0;
   out_162808829277840099[46] = 0;
   out_162808829277840099[47] = 0;
   out_162808829277840099[48] = 0;
   out_162808829277840099[49] = 0;
   out_162808829277840099[50] = 0;
   out_162808829277840099[51] = 0;
   out_162808829277840099[52] = 0;
   out_162808829277840099[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7150506142011136089) {
  err_fun(nom_x, delta_x, out_7150506142011136089);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4307514453378045812) {
  inv_err_fun(nom_x, true_x, out_4307514453378045812);
}
void pose_H_mod_fun(double *state, double *out_526209948270695177) {
  H_mod_fun(state, out_526209948270695177);
}
void pose_f_fun(double *state, double dt, double *out_826153410981652937) {
  f_fun(state,  dt, out_826153410981652937);
}
void pose_F_fun(double *state, double dt, double *out_2504584572758712159) {
  F_fun(state,  dt, out_2504584572758712159);
}
void pose_h_4(double *state, double *unused, double *out_7442480903303367172) {
  h_4(state, unused, out_7442480903303367172);
}
void pose_H_4(double *state, double *unused, double *out_3800432027061644430) {
  H_4(state, unused, out_3800432027061644430);
}
void pose_h_10(double *state, double *unused, double *out_8932011361837519248) {
  h_10(state, unused, out_8932011361837519248);
}
void pose_H_10(double *state, double *unused, double *out_4464178208942290131) {
  H_10(state, unused, out_4464178208942290131);
}
void pose_h_13(double *state, double *unused, double *out_6459110219088517442) {
  h_13(state, unused, out_6459110219088517442);
}
void pose_H_13(double *state, double *unused, double *out_588158201729311629) {
  H_13(state, unused, out_588158201729311629);
}
void pose_h_14(double *state, double *unused, double *out_7025019117935111535) {
  h_14(state, unused, out_7025019117935111535);
}
void pose_H_14(double *state, double *unused, double *out_162808829277840099) {
  H_14(state, unused, out_162808829277840099);
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
