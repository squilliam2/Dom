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
void err_fun(double *nom_x, double *delta_x, double *out_3190087603797747831) {
   out_3190087603797747831[0] = delta_x[0] + nom_x[0];
   out_3190087603797747831[1] = delta_x[1] + nom_x[1];
   out_3190087603797747831[2] = delta_x[2] + nom_x[2];
   out_3190087603797747831[3] = delta_x[3] + nom_x[3];
   out_3190087603797747831[4] = delta_x[4] + nom_x[4];
   out_3190087603797747831[5] = delta_x[5] + nom_x[5];
   out_3190087603797747831[6] = delta_x[6] + nom_x[6];
   out_3190087603797747831[7] = delta_x[7] + nom_x[7];
   out_3190087603797747831[8] = delta_x[8] + nom_x[8];
   out_3190087603797747831[9] = delta_x[9] + nom_x[9];
   out_3190087603797747831[10] = delta_x[10] + nom_x[10];
   out_3190087603797747831[11] = delta_x[11] + nom_x[11];
   out_3190087603797747831[12] = delta_x[12] + nom_x[12];
   out_3190087603797747831[13] = delta_x[13] + nom_x[13];
   out_3190087603797747831[14] = delta_x[14] + nom_x[14];
   out_3190087603797747831[15] = delta_x[15] + nom_x[15];
   out_3190087603797747831[16] = delta_x[16] + nom_x[16];
   out_3190087603797747831[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_509645540564194226) {
   out_509645540564194226[0] = -nom_x[0] + true_x[0];
   out_509645540564194226[1] = -nom_x[1] + true_x[1];
   out_509645540564194226[2] = -nom_x[2] + true_x[2];
   out_509645540564194226[3] = -nom_x[3] + true_x[3];
   out_509645540564194226[4] = -nom_x[4] + true_x[4];
   out_509645540564194226[5] = -nom_x[5] + true_x[5];
   out_509645540564194226[6] = -nom_x[6] + true_x[6];
   out_509645540564194226[7] = -nom_x[7] + true_x[7];
   out_509645540564194226[8] = -nom_x[8] + true_x[8];
   out_509645540564194226[9] = -nom_x[9] + true_x[9];
   out_509645540564194226[10] = -nom_x[10] + true_x[10];
   out_509645540564194226[11] = -nom_x[11] + true_x[11];
   out_509645540564194226[12] = -nom_x[12] + true_x[12];
   out_509645540564194226[13] = -nom_x[13] + true_x[13];
   out_509645540564194226[14] = -nom_x[14] + true_x[14];
   out_509645540564194226[15] = -nom_x[15] + true_x[15];
   out_509645540564194226[16] = -nom_x[16] + true_x[16];
   out_509645540564194226[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5916418097484803312) {
   out_5916418097484803312[0] = 1.0;
   out_5916418097484803312[1] = 0.0;
   out_5916418097484803312[2] = 0.0;
   out_5916418097484803312[3] = 0.0;
   out_5916418097484803312[4] = 0.0;
   out_5916418097484803312[5] = 0.0;
   out_5916418097484803312[6] = 0.0;
   out_5916418097484803312[7] = 0.0;
   out_5916418097484803312[8] = 0.0;
   out_5916418097484803312[9] = 0.0;
   out_5916418097484803312[10] = 0.0;
   out_5916418097484803312[11] = 0.0;
   out_5916418097484803312[12] = 0.0;
   out_5916418097484803312[13] = 0.0;
   out_5916418097484803312[14] = 0.0;
   out_5916418097484803312[15] = 0.0;
   out_5916418097484803312[16] = 0.0;
   out_5916418097484803312[17] = 0.0;
   out_5916418097484803312[18] = 0.0;
   out_5916418097484803312[19] = 1.0;
   out_5916418097484803312[20] = 0.0;
   out_5916418097484803312[21] = 0.0;
   out_5916418097484803312[22] = 0.0;
   out_5916418097484803312[23] = 0.0;
   out_5916418097484803312[24] = 0.0;
   out_5916418097484803312[25] = 0.0;
   out_5916418097484803312[26] = 0.0;
   out_5916418097484803312[27] = 0.0;
   out_5916418097484803312[28] = 0.0;
   out_5916418097484803312[29] = 0.0;
   out_5916418097484803312[30] = 0.0;
   out_5916418097484803312[31] = 0.0;
   out_5916418097484803312[32] = 0.0;
   out_5916418097484803312[33] = 0.0;
   out_5916418097484803312[34] = 0.0;
   out_5916418097484803312[35] = 0.0;
   out_5916418097484803312[36] = 0.0;
   out_5916418097484803312[37] = 0.0;
   out_5916418097484803312[38] = 1.0;
   out_5916418097484803312[39] = 0.0;
   out_5916418097484803312[40] = 0.0;
   out_5916418097484803312[41] = 0.0;
   out_5916418097484803312[42] = 0.0;
   out_5916418097484803312[43] = 0.0;
   out_5916418097484803312[44] = 0.0;
   out_5916418097484803312[45] = 0.0;
   out_5916418097484803312[46] = 0.0;
   out_5916418097484803312[47] = 0.0;
   out_5916418097484803312[48] = 0.0;
   out_5916418097484803312[49] = 0.0;
   out_5916418097484803312[50] = 0.0;
   out_5916418097484803312[51] = 0.0;
   out_5916418097484803312[52] = 0.0;
   out_5916418097484803312[53] = 0.0;
   out_5916418097484803312[54] = 0.0;
   out_5916418097484803312[55] = 0.0;
   out_5916418097484803312[56] = 0.0;
   out_5916418097484803312[57] = 1.0;
   out_5916418097484803312[58] = 0.0;
   out_5916418097484803312[59] = 0.0;
   out_5916418097484803312[60] = 0.0;
   out_5916418097484803312[61] = 0.0;
   out_5916418097484803312[62] = 0.0;
   out_5916418097484803312[63] = 0.0;
   out_5916418097484803312[64] = 0.0;
   out_5916418097484803312[65] = 0.0;
   out_5916418097484803312[66] = 0.0;
   out_5916418097484803312[67] = 0.0;
   out_5916418097484803312[68] = 0.0;
   out_5916418097484803312[69] = 0.0;
   out_5916418097484803312[70] = 0.0;
   out_5916418097484803312[71] = 0.0;
   out_5916418097484803312[72] = 0.0;
   out_5916418097484803312[73] = 0.0;
   out_5916418097484803312[74] = 0.0;
   out_5916418097484803312[75] = 0.0;
   out_5916418097484803312[76] = 1.0;
   out_5916418097484803312[77] = 0.0;
   out_5916418097484803312[78] = 0.0;
   out_5916418097484803312[79] = 0.0;
   out_5916418097484803312[80] = 0.0;
   out_5916418097484803312[81] = 0.0;
   out_5916418097484803312[82] = 0.0;
   out_5916418097484803312[83] = 0.0;
   out_5916418097484803312[84] = 0.0;
   out_5916418097484803312[85] = 0.0;
   out_5916418097484803312[86] = 0.0;
   out_5916418097484803312[87] = 0.0;
   out_5916418097484803312[88] = 0.0;
   out_5916418097484803312[89] = 0.0;
   out_5916418097484803312[90] = 0.0;
   out_5916418097484803312[91] = 0.0;
   out_5916418097484803312[92] = 0.0;
   out_5916418097484803312[93] = 0.0;
   out_5916418097484803312[94] = 0.0;
   out_5916418097484803312[95] = 1.0;
   out_5916418097484803312[96] = 0.0;
   out_5916418097484803312[97] = 0.0;
   out_5916418097484803312[98] = 0.0;
   out_5916418097484803312[99] = 0.0;
   out_5916418097484803312[100] = 0.0;
   out_5916418097484803312[101] = 0.0;
   out_5916418097484803312[102] = 0.0;
   out_5916418097484803312[103] = 0.0;
   out_5916418097484803312[104] = 0.0;
   out_5916418097484803312[105] = 0.0;
   out_5916418097484803312[106] = 0.0;
   out_5916418097484803312[107] = 0.0;
   out_5916418097484803312[108] = 0.0;
   out_5916418097484803312[109] = 0.0;
   out_5916418097484803312[110] = 0.0;
   out_5916418097484803312[111] = 0.0;
   out_5916418097484803312[112] = 0.0;
   out_5916418097484803312[113] = 0.0;
   out_5916418097484803312[114] = 1.0;
   out_5916418097484803312[115] = 0.0;
   out_5916418097484803312[116] = 0.0;
   out_5916418097484803312[117] = 0.0;
   out_5916418097484803312[118] = 0.0;
   out_5916418097484803312[119] = 0.0;
   out_5916418097484803312[120] = 0.0;
   out_5916418097484803312[121] = 0.0;
   out_5916418097484803312[122] = 0.0;
   out_5916418097484803312[123] = 0.0;
   out_5916418097484803312[124] = 0.0;
   out_5916418097484803312[125] = 0.0;
   out_5916418097484803312[126] = 0.0;
   out_5916418097484803312[127] = 0.0;
   out_5916418097484803312[128] = 0.0;
   out_5916418097484803312[129] = 0.0;
   out_5916418097484803312[130] = 0.0;
   out_5916418097484803312[131] = 0.0;
   out_5916418097484803312[132] = 0.0;
   out_5916418097484803312[133] = 1.0;
   out_5916418097484803312[134] = 0.0;
   out_5916418097484803312[135] = 0.0;
   out_5916418097484803312[136] = 0.0;
   out_5916418097484803312[137] = 0.0;
   out_5916418097484803312[138] = 0.0;
   out_5916418097484803312[139] = 0.0;
   out_5916418097484803312[140] = 0.0;
   out_5916418097484803312[141] = 0.0;
   out_5916418097484803312[142] = 0.0;
   out_5916418097484803312[143] = 0.0;
   out_5916418097484803312[144] = 0.0;
   out_5916418097484803312[145] = 0.0;
   out_5916418097484803312[146] = 0.0;
   out_5916418097484803312[147] = 0.0;
   out_5916418097484803312[148] = 0.0;
   out_5916418097484803312[149] = 0.0;
   out_5916418097484803312[150] = 0.0;
   out_5916418097484803312[151] = 0.0;
   out_5916418097484803312[152] = 1.0;
   out_5916418097484803312[153] = 0.0;
   out_5916418097484803312[154] = 0.0;
   out_5916418097484803312[155] = 0.0;
   out_5916418097484803312[156] = 0.0;
   out_5916418097484803312[157] = 0.0;
   out_5916418097484803312[158] = 0.0;
   out_5916418097484803312[159] = 0.0;
   out_5916418097484803312[160] = 0.0;
   out_5916418097484803312[161] = 0.0;
   out_5916418097484803312[162] = 0.0;
   out_5916418097484803312[163] = 0.0;
   out_5916418097484803312[164] = 0.0;
   out_5916418097484803312[165] = 0.0;
   out_5916418097484803312[166] = 0.0;
   out_5916418097484803312[167] = 0.0;
   out_5916418097484803312[168] = 0.0;
   out_5916418097484803312[169] = 0.0;
   out_5916418097484803312[170] = 0.0;
   out_5916418097484803312[171] = 1.0;
   out_5916418097484803312[172] = 0.0;
   out_5916418097484803312[173] = 0.0;
   out_5916418097484803312[174] = 0.0;
   out_5916418097484803312[175] = 0.0;
   out_5916418097484803312[176] = 0.0;
   out_5916418097484803312[177] = 0.0;
   out_5916418097484803312[178] = 0.0;
   out_5916418097484803312[179] = 0.0;
   out_5916418097484803312[180] = 0.0;
   out_5916418097484803312[181] = 0.0;
   out_5916418097484803312[182] = 0.0;
   out_5916418097484803312[183] = 0.0;
   out_5916418097484803312[184] = 0.0;
   out_5916418097484803312[185] = 0.0;
   out_5916418097484803312[186] = 0.0;
   out_5916418097484803312[187] = 0.0;
   out_5916418097484803312[188] = 0.0;
   out_5916418097484803312[189] = 0.0;
   out_5916418097484803312[190] = 1.0;
   out_5916418097484803312[191] = 0.0;
   out_5916418097484803312[192] = 0.0;
   out_5916418097484803312[193] = 0.0;
   out_5916418097484803312[194] = 0.0;
   out_5916418097484803312[195] = 0.0;
   out_5916418097484803312[196] = 0.0;
   out_5916418097484803312[197] = 0.0;
   out_5916418097484803312[198] = 0.0;
   out_5916418097484803312[199] = 0.0;
   out_5916418097484803312[200] = 0.0;
   out_5916418097484803312[201] = 0.0;
   out_5916418097484803312[202] = 0.0;
   out_5916418097484803312[203] = 0.0;
   out_5916418097484803312[204] = 0.0;
   out_5916418097484803312[205] = 0.0;
   out_5916418097484803312[206] = 0.0;
   out_5916418097484803312[207] = 0.0;
   out_5916418097484803312[208] = 0.0;
   out_5916418097484803312[209] = 1.0;
   out_5916418097484803312[210] = 0.0;
   out_5916418097484803312[211] = 0.0;
   out_5916418097484803312[212] = 0.0;
   out_5916418097484803312[213] = 0.0;
   out_5916418097484803312[214] = 0.0;
   out_5916418097484803312[215] = 0.0;
   out_5916418097484803312[216] = 0.0;
   out_5916418097484803312[217] = 0.0;
   out_5916418097484803312[218] = 0.0;
   out_5916418097484803312[219] = 0.0;
   out_5916418097484803312[220] = 0.0;
   out_5916418097484803312[221] = 0.0;
   out_5916418097484803312[222] = 0.0;
   out_5916418097484803312[223] = 0.0;
   out_5916418097484803312[224] = 0.0;
   out_5916418097484803312[225] = 0.0;
   out_5916418097484803312[226] = 0.0;
   out_5916418097484803312[227] = 0.0;
   out_5916418097484803312[228] = 1.0;
   out_5916418097484803312[229] = 0.0;
   out_5916418097484803312[230] = 0.0;
   out_5916418097484803312[231] = 0.0;
   out_5916418097484803312[232] = 0.0;
   out_5916418097484803312[233] = 0.0;
   out_5916418097484803312[234] = 0.0;
   out_5916418097484803312[235] = 0.0;
   out_5916418097484803312[236] = 0.0;
   out_5916418097484803312[237] = 0.0;
   out_5916418097484803312[238] = 0.0;
   out_5916418097484803312[239] = 0.0;
   out_5916418097484803312[240] = 0.0;
   out_5916418097484803312[241] = 0.0;
   out_5916418097484803312[242] = 0.0;
   out_5916418097484803312[243] = 0.0;
   out_5916418097484803312[244] = 0.0;
   out_5916418097484803312[245] = 0.0;
   out_5916418097484803312[246] = 0.0;
   out_5916418097484803312[247] = 1.0;
   out_5916418097484803312[248] = 0.0;
   out_5916418097484803312[249] = 0.0;
   out_5916418097484803312[250] = 0.0;
   out_5916418097484803312[251] = 0.0;
   out_5916418097484803312[252] = 0.0;
   out_5916418097484803312[253] = 0.0;
   out_5916418097484803312[254] = 0.0;
   out_5916418097484803312[255] = 0.0;
   out_5916418097484803312[256] = 0.0;
   out_5916418097484803312[257] = 0.0;
   out_5916418097484803312[258] = 0.0;
   out_5916418097484803312[259] = 0.0;
   out_5916418097484803312[260] = 0.0;
   out_5916418097484803312[261] = 0.0;
   out_5916418097484803312[262] = 0.0;
   out_5916418097484803312[263] = 0.0;
   out_5916418097484803312[264] = 0.0;
   out_5916418097484803312[265] = 0.0;
   out_5916418097484803312[266] = 1.0;
   out_5916418097484803312[267] = 0.0;
   out_5916418097484803312[268] = 0.0;
   out_5916418097484803312[269] = 0.0;
   out_5916418097484803312[270] = 0.0;
   out_5916418097484803312[271] = 0.0;
   out_5916418097484803312[272] = 0.0;
   out_5916418097484803312[273] = 0.0;
   out_5916418097484803312[274] = 0.0;
   out_5916418097484803312[275] = 0.0;
   out_5916418097484803312[276] = 0.0;
   out_5916418097484803312[277] = 0.0;
   out_5916418097484803312[278] = 0.0;
   out_5916418097484803312[279] = 0.0;
   out_5916418097484803312[280] = 0.0;
   out_5916418097484803312[281] = 0.0;
   out_5916418097484803312[282] = 0.0;
   out_5916418097484803312[283] = 0.0;
   out_5916418097484803312[284] = 0.0;
   out_5916418097484803312[285] = 1.0;
   out_5916418097484803312[286] = 0.0;
   out_5916418097484803312[287] = 0.0;
   out_5916418097484803312[288] = 0.0;
   out_5916418097484803312[289] = 0.0;
   out_5916418097484803312[290] = 0.0;
   out_5916418097484803312[291] = 0.0;
   out_5916418097484803312[292] = 0.0;
   out_5916418097484803312[293] = 0.0;
   out_5916418097484803312[294] = 0.0;
   out_5916418097484803312[295] = 0.0;
   out_5916418097484803312[296] = 0.0;
   out_5916418097484803312[297] = 0.0;
   out_5916418097484803312[298] = 0.0;
   out_5916418097484803312[299] = 0.0;
   out_5916418097484803312[300] = 0.0;
   out_5916418097484803312[301] = 0.0;
   out_5916418097484803312[302] = 0.0;
   out_5916418097484803312[303] = 0.0;
   out_5916418097484803312[304] = 1.0;
   out_5916418097484803312[305] = 0.0;
   out_5916418097484803312[306] = 0.0;
   out_5916418097484803312[307] = 0.0;
   out_5916418097484803312[308] = 0.0;
   out_5916418097484803312[309] = 0.0;
   out_5916418097484803312[310] = 0.0;
   out_5916418097484803312[311] = 0.0;
   out_5916418097484803312[312] = 0.0;
   out_5916418097484803312[313] = 0.0;
   out_5916418097484803312[314] = 0.0;
   out_5916418097484803312[315] = 0.0;
   out_5916418097484803312[316] = 0.0;
   out_5916418097484803312[317] = 0.0;
   out_5916418097484803312[318] = 0.0;
   out_5916418097484803312[319] = 0.0;
   out_5916418097484803312[320] = 0.0;
   out_5916418097484803312[321] = 0.0;
   out_5916418097484803312[322] = 0.0;
   out_5916418097484803312[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1884549682660320153) {
   out_1884549682660320153[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1884549682660320153[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1884549682660320153[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1884549682660320153[3] = dt*state[12] + state[3];
   out_1884549682660320153[4] = dt*state[13] + state[4];
   out_1884549682660320153[5] = dt*state[14] + state[5];
   out_1884549682660320153[6] = state[6];
   out_1884549682660320153[7] = state[7];
   out_1884549682660320153[8] = state[8];
   out_1884549682660320153[9] = state[9];
   out_1884549682660320153[10] = state[10];
   out_1884549682660320153[11] = state[11];
   out_1884549682660320153[12] = state[12];
   out_1884549682660320153[13] = state[13];
   out_1884549682660320153[14] = state[14];
   out_1884549682660320153[15] = state[15];
   out_1884549682660320153[16] = state[16];
   out_1884549682660320153[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2096520336867054981) {
   out_2096520336867054981[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2096520336867054981[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2096520336867054981[2] = 0;
   out_2096520336867054981[3] = 0;
   out_2096520336867054981[4] = 0;
   out_2096520336867054981[5] = 0;
   out_2096520336867054981[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2096520336867054981[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2096520336867054981[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2096520336867054981[9] = 0;
   out_2096520336867054981[10] = 0;
   out_2096520336867054981[11] = 0;
   out_2096520336867054981[12] = 0;
   out_2096520336867054981[13] = 0;
   out_2096520336867054981[14] = 0;
   out_2096520336867054981[15] = 0;
   out_2096520336867054981[16] = 0;
   out_2096520336867054981[17] = 0;
   out_2096520336867054981[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2096520336867054981[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2096520336867054981[20] = 0;
   out_2096520336867054981[21] = 0;
   out_2096520336867054981[22] = 0;
   out_2096520336867054981[23] = 0;
   out_2096520336867054981[24] = 0;
   out_2096520336867054981[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2096520336867054981[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2096520336867054981[27] = 0;
   out_2096520336867054981[28] = 0;
   out_2096520336867054981[29] = 0;
   out_2096520336867054981[30] = 0;
   out_2096520336867054981[31] = 0;
   out_2096520336867054981[32] = 0;
   out_2096520336867054981[33] = 0;
   out_2096520336867054981[34] = 0;
   out_2096520336867054981[35] = 0;
   out_2096520336867054981[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2096520336867054981[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2096520336867054981[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2096520336867054981[39] = 0;
   out_2096520336867054981[40] = 0;
   out_2096520336867054981[41] = 0;
   out_2096520336867054981[42] = 0;
   out_2096520336867054981[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2096520336867054981[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2096520336867054981[45] = 0;
   out_2096520336867054981[46] = 0;
   out_2096520336867054981[47] = 0;
   out_2096520336867054981[48] = 0;
   out_2096520336867054981[49] = 0;
   out_2096520336867054981[50] = 0;
   out_2096520336867054981[51] = 0;
   out_2096520336867054981[52] = 0;
   out_2096520336867054981[53] = 0;
   out_2096520336867054981[54] = 0;
   out_2096520336867054981[55] = 0;
   out_2096520336867054981[56] = 0;
   out_2096520336867054981[57] = 1;
   out_2096520336867054981[58] = 0;
   out_2096520336867054981[59] = 0;
   out_2096520336867054981[60] = 0;
   out_2096520336867054981[61] = 0;
   out_2096520336867054981[62] = 0;
   out_2096520336867054981[63] = 0;
   out_2096520336867054981[64] = 0;
   out_2096520336867054981[65] = 0;
   out_2096520336867054981[66] = dt;
   out_2096520336867054981[67] = 0;
   out_2096520336867054981[68] = 0;
   out_2096520336867054981[69] = 0;
   out_2096520336867054981[70] = 0;
   out_2096520336867054981[71] = 0;
   out_2096520336867054981[72] = 0;
   out_2096520336867054981[73] = 0;
   out_2096520336867054981[74] = 0;
   out_2096520336867054981[75] = 0;
   out_2096520336867054981[76] = 1;
   out_2096520336867054981[77] = 0;
   out_2096520336867054981[78] = 0;
   out_2096520336867054981[79] = 0;
   out_2096520336867054981[80] = 0;
   out_2096520336867054981[81] = 0;
   out_2096520336867054981[82] = 0;
   out_2096520336867054981[83] = 0;
   out_2096520336867054981[84] = 0;
   out_2096520336867054981[85] = dt;
   out_2096520336867054981[86] = 0;
   out_2096520336867054981[87] = 0;
   out_2096520336867054981[88] = 0;
   out_2096520336867054981[89] = 0;
   out_2096520336867054981[90] = 0;
   out_2096520336867054981[91] = 0;
   out_2096520336867054981[92] = 0;
   out_2096520336867054981[93] = 0;
   out_2096520336867054981[94] = 0;
   out_2096520336867054981[95] = 1;
   out_2096520336867054981[96] = 0;
   out_2096520336867054981[97] = 0;
   out_2096520336867054981[98] = 0;
   out_2096520336867054981[99] = 0;
   out_2096520336867054981[100] = 0;
   out_2096520336867054981[101] = 0;
   out_2096520336867054981[102] = 0;
   out_2096520336867054981[103] = 0;
   out_2096520336867054981[104] = dt;
   out_2096520336867054981[105] = 0;
   out_2096520336867054981[106] = 0;
   out_2096520336867054981[107] = 0;
   out_2096520336867054981[108] = 0;
   out_2096520336867054981[109] = 0;
   out_2096520336867054981[110] = 0;
   out_2096520336867054981[111] = 0;
   out_2096520336867054981[112] = 0;
   out_2096520336867054981[113] = 0;
   out_2096520336867054981[114] = 1;
   out_2096520336867054981[115] = 0;
   out_2096520336867054981[116] = 0;
   out_2096520336867054981[117] = 0;
   out_2096520336867054981[118] = 0;
   out_2096520336867054981[119] = 0;
   out_2096520336867054981[120] = 0;
   out_2096520336867054981[121] = 0;
   out_2096520336867054981[122] = 0;
   out_2096520336867054981[123] = 0;
   out_2096520336867054981[124] = 0;
   out_2096520336867054981[125] = 0;
   out_2096520336867054981[126] = 0;
   out_2096520336867054981[127] = 0;
   out_2096520336867054981[128] = 0;
   out_2096520336867054981[129] = 0;
   out_2096520336867054981[130] = 0;
   out_2096520336867054981[131] = 0;
   out_2096520336867054981[132] = 0;
   out_2096520336867054981[133] = 1;
   out_2096520336867054981[134] = 0;
   out_2096520336867054981[135] = 0;
   out_2096520336867054981[136] = 0;
   out_2096520336867054981[137] = 0;
   out_2096520336867054981[138] = 0;
   out_2096520336867054981[139] = 0;
   out_2096520336867054981[140] = 0;
   out_2096520336867054981[141] = 0;
   out_2096520336867054981[142] = 0;
   out_2096520336867054981[143] = 0;
   out_2096520336867054981[144] = 0;
   out_2096520336867054981[145] = 0;
   out_2096520336867054981[146] = 0;
   out_2096520336867054981[147] = 0;
   out_2096520336867054981[148] = 0;
   out_2096520336867054981[149] = 0;
   out_2096520336867054981[150] = 0;
   out_2096520336867054981[151] = 0;
   out_2096520336867054981[152] = 1;
   out_2096520336867054981[153] = 0;
   out_2096520336867054981[154] = 0;
   out_2096520336867054981[155] = 0;
   out_2096520336867054981[156] = 0;
   out_2096520336867054981[157] = 0;
   out_2096520336867054981[158] = 0;
   out_2096520336867054981[159] = 0;
   out_2096520336867054981[160] = 0;
   out_2096520336867054981[161] = 0;
   out_2096520336867054981[162] = 0;
   out_2096520336867054981[163] = 0;
   out_2096520336867054981[164] = 0;
   out_2096520336867054981[165] = 0;
   out_2096520336867054981[166] = 0;
   out_2096520336867054981[167] = 0;
   out_2096520336867054981[168] = 0;
   out_2096520336867054981[169] = 0;
   out_2096520336867054981[170] = 0;
   out_2096520336867054981[171] = 1;
   out_2096520336867054981[172] = 0;
   out_2096520336867054981[173] = 0;
   out_2096520336867054981[174] = 0;
   out_2096520336867054981[175] = 0;
   out_2096520336867054981[176] = 0;
   out_2096520336867054981[177] = 0;
   out_2096520336867054981[178] = 0;
   out_2096520336867054981[179] = 0;
   out_2096520336867054981[180] = 0;
   out_2096520336867054981[181] = 0;
   out_2096520336867054981[182] = 0;
   out_2096520336867054981[183] = 0;
   out_2096520336867054981[184] = 0;
   out_2096520336867054981[185] = 0;
   out_2096520336867054981[186] = 0;
   out_2096520336867054981[187] = 0;
   out_2096520336867054981[188] = 0;
   out_2096520336867054981[189] = 0;
   out_2096520336867054981[190] = 1;
   out_2096520336867054981[191] = 0;
   out_2096520336867054981[192] = 0;
   out_2096520336867054981[193] = 0;
   out_2096520336867054981[194] = 0;
   out_2096520336867054981[195] = 0;
   out_2096520336867054981[196] = 0;
   out_2096520336867054981[197] = 0;
   out_2096520336867054981[198] = 0;
   out_2096520336867054981[199] = 0;
   out_2096520336867054981[200] = 0;
   out_2096520336867054981[201] = 0;
   out_2096520336867054981[202] = 0;
   out_2096520336867054981[203] = 0;
   out_2096520336867054981[204] = 0;
   out_2096520336867054981[205] = 0;
   out_2096520336867054981[206] = 0;
   out_2096520336867054981[207] = 0;
   out_2096520336867054981[208] = 0;
   out_2096520336867054981[209] = 1;
   out_2096520336867054981[210] = 0;
   out_2096520336867054981[211] = 0;
   out_2096520336867054981[212] = 0;
   out_2096520336867054981[213] = 0;
   out_2096520336867054981[214] = 0;
   out_2096520336867054981[215] = 0;
   out_2096520336867054981[216] = 0;
   out_2096520336867054981[217] = 0;
   out_2096520336867054981[218] = 0;
   out_2096520336867054981[219] = 0;
   out_2096520336867054981[220] = 0;
   out_2096520336867054981[221] = 0;
   out_2096520336867054981[222] = 0;
   out_2096520336867054981[223] = 0;
   out_2096520336867054981[224] = 0;
   out_2096520336867054981[225] = 0;
   out_2096520336867054981[226] = 0;
   out_2096520336867054981[227] = 0;
   out_2096520336867054981[228] = 1;
   out_2096520336867054981[229] = 0;
   out_2096520336867054981[230] = 0;
   out_2096520336867054981[231] = 0;
   out_2096520336867054981[232] = 0;
   out_2096520336867054981[233] = 0;
   out_2096520336867054981[234] = 0;
   out_2096520336867054981[235] = 0;
   out_2096520336867054981[236] = 0;
   out_2096520336867054981[237] = 0;
   out_2096520336867054981[238] = 0;
   out_2096520336867054981[239] = 0;
   out_2096520336867054981[240] = 0;
   out_2096520336867054981[241] = 0;
   out_2096520336867054981[242] = 0;
   out_2096520336867054981[243] = 0;
   out_2096520336867054981[244] = 0;
   out_2096520336867054981[245] = 0;
   out_2096520336867054981[246] = 0;
   out_2096520336867054981[247] = 1;
   out_2096520336867054981[248] = 0;
   out_2096520336867054981[249] = 0;
   out_2096520336867054981[250] = 0;
   out_2096520336867054981[251] = 0;
   out_2096520336867054981[252] = 0;
   out_2096520336867054981[253] = 0;
   out_2096520336867054981[254] = 0;
   out_2096520336867054981[255] = 0;
   out_2096520336867054981[256] = 0;
   out_2096520336867054981[257] = 0;
   out_2096520336867054981[258] = 0;
   out_2096520336867054981[259] = 0;
   out_2096520336867054981[260] = 0;
   out_2096520336867054981[261] = 0;
   out_2096520336867054981[262] = 0;
   out_2096520336867054981[263] = 0;
   out_2096520336867054981[264] = 0;
   out_2096520336867054981[265] = 0;
   out_2096520336867054981[266] = 1;
   out_2096520336867054981[267] = 0;
   out_2096520336867054981[268] = 0;
   out_2096520336867054981[269] = 0;
   out_2096520336867054981[270] = 0;
   out_2096520336867054981[271] = 0;
   out_2096520336867054981[272] = 0;
   out_2096520336867054981[273] = 0;
   out_2096520336867054981[274] = 0;
   out_2096520336867054981[275] = 0;
   out_2096520336867054981[276] = 0;
   out_2096520336867054981[277] = 0;
   out_2096520336867054981[278] = 0;
   out_2096520336867054981[279] = 0;
   out_2096520336867054981[280] = 0;
   out_2096520336867054981[281] = 0;
   out_2096520336867054981[282] = 0;
   out_2096520336867054981[283] = 0;
   out_2096520336867054981[284] = 0;
   out_2096520336867054981[285] = 1;
   out_2096520336867054981[286] = 0;
   out_2096520336867054981[287] = 0;
   out_2096520336867054981[288] = 0;
   out_2096520336867054981[289] = 0;
   out_2096520336867054981[290] = 0;
   out_2096520336867054981[291] = 0;
   out_2096520336867054981[292] = 0;
   out_2096520336867054981[293] = 0;
   out_2096520336867054981[294] = 0;
   out_2096520336867054981[295] = 0;
   out_2096520336867054981[296] = 0;
   out_2096520336867054981[297] = 0;
   out_2096520336867054981[298] = 0;
   out_2096520336867054981[299] = 0;
   out_2096520336867054981[300] = 0;
   out_2096520336867054981[301] = 0;
   out_2096520336867054981[302] = 0;
   out_2096520336867054981[303] = 0;
   out_2096520336867054981[304] = 1;
   out_2096520336867054981[305] = 0;
   out_2096520336867054981[306] = 0;
   out_2096520336867054981[307] = 0;
   out_2096520336867054981[308] = 0;
   out_2096520336867054981[309] = 0;
   out_2096520336867054981[310] = 0;
   out_2096520336867054981[311] = 0;
   out_2096520336867054981[312] = 0;
   out_2096520336867054981[313] = 0;
   out_2096520336867054981[314] = 0;
   out_2096520336867054981[315] = 0;
   out_2096520336867054981[316] = 0;
   out_2096520336867054981[317] = 0;
   out_2096520336867054981[318] = 0;
   out_2096520336867054981[319] = 0;
   out_2096520336867054981[320] = 0;
   out_2096520336867054981[321] = 0;
   out_2096520336867054981[322] = 0;
   out_2096520336867054981[323] = 1;
}
void h_4(double *state, double *unused, double *out_2454407190288685983) {
   out_2454407190288685983[0] = state[6] + state[9];
   out_2454407190288685983[1] = state[7] + state[10];
   out_2454407190288685983[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6670579099539515919) {
   out_6670579099539515919[0] = 0;
   out_6670579099539515919[1] = 0;
   out_6670579099539515919[2] = 0;
   out_6670579099539515919[3] = 0;
   out_6670579099539515919[4] = 0;
   out_6670579099539515919[5] = 0;
   out_6670579099539515919[6] = 1;
   out_6670579099539515919[7] = 0;
   out_6670579099539515919[8] = 0;
   out_6670579099539515919[9] = 1;
   out_6670579099539515919[10] = 0;
   out_6670579099539515919[11] = 0;
   out_6670579099539515919[12] = 0;
   out_6670579099539515919[13] = 0;
   out_6670579099539515919[14] = 0;
   out_6670579099539515919[15] = 0;
   out_6670579099539515919[16] = 0;
   out_6670579099539515919[17] = 0;
   out_6670579099539515919[18] = 0;
   out_6670579099539515919[19] = 0;
   out_6670579099539515919[20] = 0;
   out_6670579099539515919[21] = 0;
   out_6670579099539515919[22] = 0;
   out_6670579099539515919[23] = 0;
   out_6670579099539515919[24] = 0;
   out_6670579099539515919[25] = 1;
   out_6670579099539515919[26] = 0;
   out_6670579099539515919[27] = 0;
   out_6670579099539515919[28] = 1;
   out_6670579099539515919[29] = 0;
   out_6670579099539515919[30] = 0;
   out_6670579099539515919[31] = 0;
   out_6670579099539515919[32] = 0;
   out_6670579099539515919[33] = 0;
   out_6670579099539515919[34] = 0;
   out_6670579099539515919[35] = 0;
   out_6670579099539515919[36] = 0;
   out_6670579099539515919[37] = 0;
   out_6670579099539515919[38] = 0;
   out_6670579099539515919[39] = 0;
   out_6670579099539515919[40] = 0;
   out_6670579099539515919[41] = 0;
   out_6670579099539515919[42] = 0;
   out_6670579099539515919[43] = 0;
   out_6670579099539515919[44] = 1;
   out_6670579099539515919[45] = 0;
   out_6670579099539515919[46] = 0;
   out_6670579099539515919[47] = 1;
   out_6670579099539515919[48] = 0;
   out_6670579099539515919[49] = 0;
   out_6670579099539515919[50] = 0;
   out_6670579099539515919[51] = 0;
   out_6670579099539515919[52] = 0;
   out_6670579099539515919[53] = 0;
}
void h_10(double *state, double *unused, double *out_8369687601978266142) {
   out_8369687601978266142[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8369687601978266142[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8369687601978266142[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7187578973007118545) {
   out_7187578973007118545[0] = 0;
   out_7187578973007118545[1] = 9.8100000000000005*cos(state[1]);
   out_7187578973007118545[2] = 0;
   out_7187578973007118545[3] = 0;
   out_7187578973007118545[4] = -state[8];
   out_7187578973007118545[5] = state[7];
   out_7187578973007118545[6] = 0;
   out_7187578973007118545[7] = state[5];
   out_7187578973007118545[8] = -state[4];
   out_7187578973007118545[9] = 0;
   out_7187578973007118545[10] = 0;
   out_7187578973007118545[11] = 0;
   out_7187578973007118545[12] = 1;
   out_7187578973007118545[13] = 0;
   out_7187578973007118545[14] = 0;
   out_7187578973007118545[15] = 1;
   out_7187578973007118545[16] = 0;
   out_7187578973007118545[17] = 0;
   out_7187578973007118545[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7187578973007118545[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7187578973007118545[20] = 0;
   out_7187578973007118545[21] = state[8];
   out_7187578973007118545[22] = 0;
   out_7187578973007118545[23] = -state[6];
   out_7187578973007118545[24] = -state[5];
   out_7187578973007118545[25] = 0;
   out_7187578973007118545[26] = state[3];
   out_7187578973007118545[27] = 0;
   out_7187578973007118545[28] = 0;
   out_7187578973007118545[29] = 0;
   out_7187578973007118545[30] = 0;
   out_7187578973007118545[31] = 1;
   out_7187578973007118545[32] = 0;
   out_7187578973007118545[33] = 0;
   out_7187578973007118545[34] = 1;
   out_7187578973007118545[35] = 0;
   out_7187578973007118545[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7187578973007118545[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7187578973007118545[38] = 0;
   out_7187578973007118545[39] = -state[7];
   out_7187578973007118545[40] = state[6];
   out_7187578973007118545[41] = 0;
   out_7187578973007118545[42] = state[4];
   out_7187578973007118545[43] = -state[3];
   out_7187578973007118545[44] = 0;
   out_7187578973007118545[45] = 0;
   out_7187578973007118545[46] = 0;
   out_7187578973007118545[47] = 0;
   out_7187578973007118545[48] = 0;
   out_7187578973007118545[49] = 0;
   out_7187578973007118545[50] = 1;
   out_7187578973007118545[51] = 0;
   out_7187578973007118545[52] = 0;
   out_7187578973007118545[53] = 1;
}
void h_13(double *state, double *unused, double *out_23418844804759200) {
   out_23418844804759200[0] = state[3];
   out_23418844804759200[1] = state[4];
   out_23418844804759200[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4165533765853334768) {
   out_4165533765853334768[0] = 0;
   out_4165533765853334768[1] = 0;
   out_4165533765853334768[2] = 0;
   out_4165533765853334768[3] = 1;
   out_4165533765853334768[4] = 0;
   out_4165533765853334768[5] = 0;
   out_4165533765853334768[6] = 0;
   out_4165533765853334768[7] = 0;
   out_4165533765853334768[8] = 0;
   out_4165533765853334768[9] = 0;
   out_4165533765853334768[10] = 0;
   out_4165533765853334768[11] = 0;
   out_4165533765853334768[12] = 0;
   out_4165533765853334768[13] = 0;
   out_4165533765853334768[14] = 0;
   out_4165533765853334768[15] = 0;
   out_4165533765853334768[16] = 0;
   out_4165533765853334768[17] = 0;
   out_4165533765853334768[18] = 0;
   out_4165533765853334768[19] = 0;
   out_4165533765853334768[20] = 0;
   out_4165533765853334768[21] = 0;
   out_4165533765853334768[22] = 1;
   out_4165533765853334768[23] = 0;
   out_4165533765853334768[24] = 0;
   out_4165533765853334768[25] = 0;
   out_4165533765853334768[26] = 0;
   out_4165533765853334768[27] = 0;
   out_4165533765853334768[28] = 0;
   out_4165533765853334768[29] = 0;
   out_4165533765853334768[30] = 0;
   out_4165533765853334768[31] = 0;
   out_4165533765853334768[32] = 0;
   out_4165533765853334768[33] = 0;
   out_4165533765853334768[34] = 0;
   out_4165533765853334768[35] = 0;
   out_4165533765853334768[36] = 0;
   out_4165533765853334768[37] = 0;
   out_4165533765853334768[38] = 0;
   out_4165533765853334768[39] = 0;
   out_4165533765853334768[40] = 0;
   out_4165533765853334768[41] = 1;
   out_4165533765853334768[42] = 0;
   out_4165533765853334768[43] = 0;
   out_4165533765853334768[44] = 0;
   out_4165533765853334768[45] = 0;
   out_4165533765853334768[46] = 0;
   out_4165533765853334768[47] = 0;
   out_4165533765853334768[48] = 0;
   out_4165533765853334768[49] = 0;
   out_4165533765853334768[50] = 0;
   out_4165533765853334768[51] = 0;
   out_4165533765853334768[52] = 0;
   out_4165533765853334768[53] = 0;
}
void h_14(double *state, double *unused, double *out_3766794879461642001) {
   out_3766794879461642001[0] = state[6];
   out_3766794879461642001[1] = state[7];
   out_3766794879461642001[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7812924117830551168) {
   out_7812924117830551168[0] = 0;
   out_7812924117830551168[1] = 0;
   out_7812924117830551168[2] = 0;
   out_7812924117830551168[3] = 0;
   out_7812924117830551168[4] = 0;
   out_7812924117830551168[5] = 0;
   out_7812924117830551168[6] = 1;
   out_7812924117830551168[7] = 0;
   out_7812924117830551168[8] = 0;
   out_7812924117830551168[9] = 0;
   out_7812924117830551168[10] = 0;
   out_7812924117830551168[11] = 0;
   out_7812924117830551168[12] = 0;
   out_7812924117830551168[13] = 0;
   out_7812924117830551168[14] = 0;
   out_7812924117830551168[15] = 0;
   out_7812924117830551168[16] = 0;
   out_7812924117830551168[17] = 0;
   out_7812924117830551168[18] = 0;
   out_7812924117830551168[19] = 0;
   out_7812924117830551168[20] = 0;
   out_7812924117830551168[21] = 0;
   out_7812924117830551168[22] = 0;
   out_7812924117830551168[23] = 0;
   out_7812924117830551168[24] = 0;
   out_7812924117830551168[25] = 1;
   out_7812924117830551168[26] = 0;
   out_7812924117830551168[27] = 0;
   out_7812924117830551168[28] = 0;
   out_7812924117830551168[29] = 0;
   out_7812924117830551168[30] = 0;
   out_7812924117830551168[31] = 0;
   out_7812924117830551168[32] = 0;
   out_7812924117830551168[33] = 0;
   out_7812924117830551168[34] = 0;
   out_7812924117830551168[35] = 0;
   out_7812924117830551168[36] = 0;
   out_7812924117830551168[37] = 0;
   out_7812924117830551168[38] = 0;
   out_7812924117830551168[39] = 0;
   out_7812924117830551168[40] = 0;
   out_7812924117830551168[41] = 0;
   out_7812924117830551168[42] = 0;
   out_7812924117830551168[43] = 0;
   out_7812924117830551168[44] = 1;
   out_7812924117830551168[45] = 0;
   out_7812924117830551168[46] = 0;
   out_7812924117830551168[47] = 0;
   out_7812924117830551168[48] = 0;
   out_7812924117830551168[49] = 0;
   out_7812924117830551168[50] = 0;
   out_7812924117830551168[51] = 0;
   out_7812924117830551168[52] = 0;
   out_7812924117830551168[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3190087603797747831) {
  err_fun(nom_x, delta_x, out_3190087603797747831);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_509645540564194226) {
  inv_err_fun(nom_x, true_x, out_509645540564194226);
}
void pose_H_mod_fun(double *state, double *out_5916418097484803312) {
  H_mod_fun(state, out_5916418097484803312);
}
void pose_f_fun(double *state, double dt, double *out_1884549682660320153) {
  f_fun(state,  dt, out_1884549682660320153);
}
void pose_F_fun(double *state, double dt, double *out_2096520336867054981) {
  F_fun(state,  dt, out_2096520336867054981);
}
void pose_h_4(double *state, double *unused, double *out_2454407190288685983) {
  h_4(state, unused, out_2454407190288685983);
}
void pose_H_4(double *state, double *unused, double *out_6670579099539515919) {
  H_4(state, unused, out_6670579099539515919);
}
void pose_h_10(double *state, double *unused, double *out_8369687601978266142) {
  h_10(state, unused, out_8369687601978266142);
}
void pose_H_10(double *state, double *unused, double *out_7187578973007118545) {
  H_10(state, unused, out_7187578973007118545);
}
void pose_h_13(double *state, double *unused, double *out_23418844804759200) {
  h_13(state, unused, out_23418844804759200);
}
void pose_H_13(double *state, double *unused, double *out_4165533765853334768) {
  H_13(state, unused, out_4165533765853334768);
}
void pose_h_14(double *state, double *unused, double *out_3766794879461642001) {
  h_14(state, unused, out_3766794879461642001);
}
void pose_H_14(double *state, double *unused, double *out_7812924117830551168) {
  H_14(state, unused, out_7812924117830551168);
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
