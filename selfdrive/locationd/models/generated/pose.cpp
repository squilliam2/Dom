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
void err_fun(double *nom_x, double *delta_x, double *out_2550502777521953992) {
   out_2550502777521953992[0] = delta_x[0] + nom_x[0];
   out_2550502777521953992[1] = delta_x[1] + nom_x[1];
   out_2550502777521953992[2] = delta_x[2] + nom_x[2];
   out_2550502777521953992[3] = delta_x[3] + nom_x[3];
   out_2550502777521953992[4] = delta_x[4] + nom_x[4];
   out_2550502777521953992[5] = delta_x[5] + nom_x[5];
   out_2550502777521953992[6] = delta_x[6] + nom_x[6];
   out_2550502777521953992[7] = delta_x[7] + nom_x[7];
   out_2550502777521953992[8] = delta_x[8] + nom_x[8];
   out_2550502777521953992[9] = delta_x[9] + nom_x[9];
   out_2550502777521953992[10] = delta_x[10] + nom_x[10];
   out_2550502777521953992[11] = delta_x[11] + nom_x[11];
   out_2550502777521953992[12] = delta_x[12] + nom_x[12];
   out_2550502777521953992[13] = delta_x[13] + nom_x[13];
   out_2550502777521953992[14] = delta_x[14] + nom_x[14];
   out_2550502777521953992[15] = delta_x[15] + nom_x[15];
   out_2550502777521953992[16] = delta_x[16] + nom_x[16];
   out_2550502777521953992[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2991013798952875835) {
   out_2991013798952875835[0] = -nom_x[0] + true_x[0];
   out_2991013798952875835[1] = -nom_x[1] + true_x[1];
   out_2991013798952875835[2] = -nom_x[2] + true_x[2];
   out_2991013798952875835[3] = -nom_x[3] + true_x[3];
   out_2991013798952875835[4] = -nom_x[4] + true_x[4];
   out_2991013798952875835[5] = -nom_x[5] + true_x[5];
   out_2991013798952875835[6] = -nom_x[6] + true_x[6];
   out_2991013798952875835[7] = -nom_x[7] + true_x[7];
   out_2991013798952875835[8] = -nom_x[8] + true_x[8];
   out_2991013798952875835[9] = -nom_x[9] + true_x[9];
   out_2991013798952875835[10] = -nom_x[10] + true_x[10];
   out_2991013798952875835[11] = -nom_x[11] + true_x[11];
   out_2991013798952875835[12] = -nom_x[12] + true_x[12];
   out_2991013798952875835[13] = -nom_x[13] + true_x[13];
   out_2991013798952875835[14] = -nom_x[14] + true_x[14];
   out_2991013798952875835[15] = -nom_x[15] + true_x[15];
   out_2991013798952875835[16] = -nom_x[16] + true_x[16];
   out_2991013798952875835[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3992538829710935120) {
   out_3992538829710935120[0] = 1.0;
   out_3992538829710935120[1] = 0.0;
   out_3992538829710935120[2] = 0.0;
   out_3992538829710935120[3] = 0.0;
   out_3992538829710935120[4] = 0.0;
   out_3992538829710935120[5] = 0.0;
   out_3992538829710935120[6] = 0.0;
   out_3992538829710935120[7] = 0.0;
   out_3992538829710935120[8] = 0.0;
   out_3992538829710935120[9] = 0.0;
   out_3992538829710935120[10] = 0.0;
   out_3992538829710935120[11] = 0.0;
   out_3992538829710935120[12] = 0.0;
   out_3992538829710935120[13] = 0.0;
   out_3992538829710935120[14] = 0.0;
   out_3992538829710935120[15] = 0.0;
   out_3992538829710935120[16] = 0.0;
   out_3992538829710935120[17] = 0.0;
   out_3992538829710935120[18] = 0.0;
   out_3992538829710935120[19] = 1.0;
   out_3992538829710935120[20] = 0.0;
   out_3992538829710935120[21] = 0.0;
   out_3992538829710935120[22] = 0.0;
   out_3992538829710935120[23] = 0.0;
   out_3992538829710935120[24] = 0.0;
   out_3992538829710935120[25] = 0.0;
   out_3992538829710935120[26] = 0.0;
   out_3992538829710935120[27] = 0.0;
   out_3992538829710935120[28] = 0.0;
   out_3992538829710935120[29] = 0.0;
   out_3992538829710935120[30] = 0.0;
   out_3992538829710935120[31] = 0.0;
   out_3992538829710935120[32] = 0.0;
   out_3992538829710935120[33] = 0.0;
   out_3992538829710935120[34] = 0.0;
   out_3992538829710935120[35] = 0.0;
   out_3992538829710935120[36] = 0.0;
   out_3992538829710935120[37] = 0.0;
   out_3992538829710935120[38] = 1.0;
   out_3992538829710935120[39] = 0.0;
   out_3992538829710935120[40] = 0.0;
   out_3992538829710935120[41] = 0.0;
   out_3992538829710935120[42] = 0.0;
   out_3992538829710935120[43] = 0.0;
   out_3992538829710935120[44] = 0.0;
   out_3992538829710935120[45] = 0.0;
   out_3992538829710935120[46] = 0.0;
   out_3992538829710935120[47] = 0.0;
   out_3992538829710935120[48] = 0.0;
   out_3992538829710935120[49] = 0.0;
   out_3992538829710935120[50] = 0.0;
   out_3992538829710935120[51] = 0.0;
   out_3992538829710935120[52] = 0.0;
   out_3992538829710935120[53] = 0.0;
   out_3992538829710935120[54] = 0.0;
   out_3992538829710935120[55] = 0.0;
   out_3992538829710935120[56] = 0.0;
   out_3992538829710935120[57] = 1.0;
   out_3992538829710935120[58] = 0.0;
   out_3992538829710935120[59] = 0.0;
   out_3992538829710935120[60] = 0.0;
   out_3992538829710935120[61] = 0.0;
   out_3992538829710935120[62] = 0.0;
   out_3992538829710935120[63] = 0.0;
   out_3992538829710935120[64] = 0.0;
   out_3992538829710935120[65] = 0.0;
   out_3992538829710935120[66] = 0.0;
   out_3992538829710935120[67] = 0.0;
   out_3992538829710935120[68] = 0.0;
   out_3992538829710935120[69] = 0.0;
   out_3992538829710935120[70] = 0.0;
   out_3992538829710935120[71] = 0.0;
   out_3992538829710935120[72] = 0.0;
   out_3992538829710935120[73] = 0.0;
   out_3992538829710935120[74] = 0.0;
   out_3992538829710935120[75] = 0.0;
   out_3992538829710935120[76] = 1.0;
   out_3992538829710935120[77] = 0.0;
   out_3992538829710935120[78] = 0.0;
   out_3992538829710935120[79] = 0.0;
   out_3992538829710935120[80] = 0.0;
   out_3992538829710935120[81] = 0.0;
   out_3992538829710935120[82] = 0.0;
   out_3992538829710935120[83] = 0.0;
   out_3992538829710935120[84] = 0.0;
   out_3992538829710935120[85] = 0.0;
   out_3992538829710935120[86] = 0.0;
   out_3992538829710935120[87] = 0.0;
   out_3992538829710935120[88] = 0.0;
   out_3992538829710935120[89] = 0.0;
   out_3992538829710935120[90] = 0.0;
   out_3992538829710935120[91] = 0.0;
   out_3992538829710935120[92] = 0.0;
   out_3992538829710935120[93] = 0.0;
   out_3992538829710935120[94] = 0.0;
   out_3992538829710935120[95] = 1.0;
   out_3992538829710935120[96] = 0.0;
   out_3992538829710935120[97] = 0.0;
   out_3992538829710935120[98] = 0.0;
   out_3992538829710935120[99] = 0.0;
   out_3992538829710935120[100] = 0.0;
   out_3992538829710935120[101] = 0.0;
   out_3992538829710935120[102] = 0.0;
   out_3992538829710935120[103] = 0.0;
   out_3992538829710935120[104] = 0.0;
   out_3992538829710935120[105] = 0.0;
   out_3992538829710935120[106] = 0.0;
   out_3992538829710935120[107] = 0.0;
   out_3992538829710935120[108] = 0.0;
   out_3992538829710935120[109] = 0.0;
   out_3992538829710935120[110] = 0.0;
   out_3992538829710935120[111] = 0.0;
   out_3992538829710935120[112] = 0.0;
   out_3992538829710935120[113] = 0.0;
   out_3992538829710935120[114] = 1.0;
   out_3992538829710935120[115] = 0.0;
   out_3992538829710935120[116] = 0.0;
   out_3992538829710935120[117] = 0.0;
   out_3992538829710935120[118] = 0.0;
   out_3992538829710935120[119] = 0.0;
   out_3992538829710935120[120] = 0.0;
   out_3992538829710935120[121] = 0.0;
   out_3992538829710935120[122] = 0.0;
   out_3992538829710935120[123] = 0.0;
   out_3992538829710935120[124] = 0.0;
   out_3992538829710935120[125] = 0.0;
   out_3992538829710935120[126] = 0.0;
   out_3992538829710935120[127] = 0.0;
   out_3992538829710935120[128] = 0.0;
   out_3992538829710935120[129] = 0.0;
   out_3992538829710935120[130] = 0.0;
   out_3992538829710935120[131] = 0.0;
   out_3992538829710935120[132] = 0.0;
   out_3992538829710935120[133] = 1.0;
   out_3992538829710935120[134] = 0.0;
   out_3992538829710935120[135] = 0.0;
   out_3992538829710935120[136] = 0.0;
   out_3992538829710935120[137] = 0.0;
   out_3992538829710935120[138] = 0.0;
   out_3992538829710935120[139] = 0.0;
   out_3992538829710935120[140] = 0.0;
   out_3992538829710935120[141] = 0.0;
   out_3992538829710935120[142] = 0.0;
   out_3992538829710935120[143] = 0.0;
   out_3992538829710935120[144] = 0.0;
   out_3992538829710935120[145] = 0.0;
   out_3992538829710935120[146] = 0.0;
   out_3992538829710935120[147] = 0.0;
   out_3992538829710935120[148] = 0.0;
   out_3992538829710935120[149] = 0.0;
   out_3992538829710935120[150] = 0.0;
   out_3992538829710935120[151] = 0.0;
   out_3992538829710935120[152] = 1.0;
   out_3992538829710935120[153] = 0.0;
   out_3992538829710935120[154] = 0.0;
   out_3992538829710935120[155] = 0.0;
   out_3992538829710935120[156] = 0.0;
   out_3992538829710935120[157] = 0.0;
   out_3992538829710935120[158] = 0.0;
   out_3992538829710935120[159] = 0.0;
   out_3992538829710935120[160] = 0.0;
   out_3992538829710935120[161] = 0.0;
   out_3992538829710935120[162] = 0.0;
   out_3992538829710935120[163] = 0.0;
   out_3992538829710935120[164] = 0.0;
   out_3992538829710935120[165] = 0.0;
   out_3992538829710935120[166] = 0.0;
   out_3992538829710935120[167] = 0.0;
   out_3992538829710935120[168] = 0.0;
   out_3992538829710935120[169] = 0.0;
   out_3992538829710935120[170] = 0.0;
   out_3992538829710935120[171] = 1.0;
   out_3992538829710935120[172] = 0.0;
   out_3992538829710935120[173] = 0.0;
   out_3992538829710935120[174] = 0.0;
   out_3992538829710935120[175] = 0.0;
   out_3992538829710935120[176] = 0.0;
   out_3992538829710935120[177] = 0.0;
   out_3992538829710935120[178] = 0.0;
   out_3992538829710935120[179] = 0.0;
   out_3992538829710935120[180] = 0.0;
   out_3992538829710935120[181] = 0.0;
   out_3992538829710935120[182] = 0.0;
   out_3992538829710935120[183] = 0.0;
   out_3992538829710935120[184] = 0.0;
   out_3992538829710935120[185] = 0.0;
   out_3992538829710935120[186] = 0.0;
   out_3992538829710935120[187] = 0.0;
   out_3992538829710935120[188] = 0.0;
   out_3992538829710935120[189] = 0.0;
   out_3992538829710935120[190] = 1.0;
   out_3992538829710935120[191] = 0.0;
   out_3992538829710935120[192] = 0.0;
   out_3992538829710935120[193] = 0.0;
   out_3992538829710935120[194] = 0.0;
   out_3992538829710935120[195] = 0.0;
   out_3992538829710935120[196] = 0.0;
   out_3992538829710935120[197] = 0.0;
   out_3992538829710935120[198] = 0.0;
   out_3992538829710935120[199] = 0.0;
   out_3992538829710935120[200] = 0.0;
   out_3992538829710935120[201] = 0.0;
   out_3992538829710935120[202] = 0.0;
   out_3992538829710935120[203] = 0.0;
   out_3992538829710935120[204] = 0.0;
   out_3992538829710935120[205] = 0.0;
   out_3992538829710935120[206] = 0.0;
   out_3992538829710935120[207] = 0.0;
   out_3992538829710935120[208] = 0.0;
   out_3992538829710935120[209] = 1.0;
   out_3992538829710935120[210] = 0.0;
   out_3992538829710935120[211] = 0.0;
   out_3992538829710935120[212] = 0.0;
   out_3992538829710935120[213] = 0.0;
   out_3992538829710935120[214] = 0.0;
   out_3992538829710935120[215] = 0.0;
   out_3992538829710935120[216] = 0.0;
   out_3992538829710935120[217] = 0.0;
   out_3992538829710935120[218] = 0.0;
   out_3992538829710935120[219] = 0.0;
   out_3992538829710935120[220] = 0.0;
   out_3992538829710935120[221] = 0.0;
   out_3992538829710935120[222] = 0.0;
   out_3992538829710935120[223] = 0.0;
   out_3992538829710935120[224] = 0.0;
   out_3992538829710935120[225] = 0.0;
   out_3992538829710935120[226] = 0.0;
   out_3992538829710935120[227] = 0.0;
   out_3992538829710935120[228] = 1.0;
   out_3992538829710935120[229] = 0.0;
   out_3992538829710935120[230] = 0.0;
   out_3992538829710935120[231] = 0.0;
   out_3992538829710935120[232] = 0.0;
   out_3992538829710935120[233] = 0.0;
   out_3992538829710935120[234] = 0.0;
   out_3992538829710935120[235] = 0.0;
   out_3992538829710935120[236] = 0.0;
   out_3992538829710935120[237] = 0.0;
   out_3992538829710935120[238] = 0.0;
   out_3992538829710935120[239] = 0.0;
   out_3992538829710935120[240] = 0.0;
   out_3992538829710935120[241] = 0.0;
   out_3992538829710935120[242] = 0.0;
   out_3992538829710935120[243] = 0.0;
   out_3992538829710935120[244] = 0.0;
   out_3992538829710935120[245] = 0.0;
   out_3992538829710935120[246] = 0.0;
   out_3992538829710935120[247] = 1.0;
   out_3992538829710935120[248] = 0.0;
   out_3992538829710935120[249] = 0.0;
   out_3992538829710935120[250] = 0.0;
   out_3992538829710935120[251] = 0.0;
   out_3992538829710935120[252] = 0.0;
   out_3992538829710935120[253] = 0.0;
   out_3992538829710935120[254] = 0.0;
   out_3992538829710935120[255] = 0.0;
   out_3992538829710935120[256] = 0.0;
   out_3992538829710935120[257] = 0.0;
   out_3992538829710935120[258] = 0.0;
   out_3992538829710935120[259] = 0.0;
   out_3992538829710935120[260] = 0.0;
   out_3992538829710935120[261] = 0.0;
   out_3992538829710935120[262] = 0.0;
   out_3992538829710935120[263] = 0.0;
   out_3992538829710935120[264] = 0.0;
   out_3992538829710935120[265] = 0.0;
   out_3992538829710935120[266] = 1.0;
   out_3992538829710935120[267] = 0.0;
   out_3992538829710935120[268] = 0.0;
   out_3992538829710935120[269] = 0.0;
   out_3992538829710935120[270] = 0.0;
   out_3992538829710935120[271] = 0.0;
   out_3992538829710935120[272] = 0.0;
   out_3992538829710935120[273] = 0.0;
   out_3992538829710935120[274] = 0.0;
   out_3992538829710935120[275] = 0.0;
   out_3992538829710935120[276] = 0.0;
   out_3992538829710935120[277] = 0.0;
   out_3992538829710935120[278] = 0.0;
   out_3992538829710935120[279] = 0.0;
   out_3992538829710935120[280] = 0.0;
   out_3992538829710935120[281] = 0.0;
   out_3992538829710935120[282] = 0.0;
   out_3992538829710935120[283] = 0.0;
   out_3992538829710935120[284] = 0.0;
   out_3992538829710935120[285] = 1.0;
   out_3992538829710935120[286] = 0.0;
   out_3992538829710935120[287] = 0.0;
   out_3992538829710935120[288] = 0.0;
   out_3992538829710935120[289] = 0.0;
   out_3992538829710935120[290] = 0.0;
   out_3992538829710935120[291] = 0.0;
   out_3992538829710935120[292] = 0.0;
   out_3992538829710935120[293] = 0.0;
   out_3992538829710935120[294] = 0.0;
   out_3992538829710935120[295] = 0.0;
   out_3992538829710935120[296] = 0.0;
   out_3992538829710935120[297] = 0.0;
   out_3992538829710935120[298] = 0.0;
   out_3992538829710935120[299] = 0.0;
   out_3992538829710935120[300] = 0.0;
   out_3992538829710935120[301] = 0.0;
   out_3992538829710935120[302] = 0.0;
   out_3992538829710935120[303] = 0.0;
   out_3992538829710935120[304] = 1.0;
   out_3992538829710935120[305] = 0.0;
   out_3992538829710935120[306] = 0.0;
   out_3992538829710935120[307] = 0.0;
   out_3992538829710935120[308] = 0.0;
   out_3992538829710935120[309] = 0.0;
   out_3992538829710935120[310] = 0.0;
   out_3992538829710935120[311] = 0.0;
   out_3992538829710935120[312] = 0.0;
   out_3992538829710935120[313] = 0.0;
   out_3992538829710935120[314] = 0.0;
   out_3992538829710935120[315] = 0.0;
   out_3992538829710935120[316] = 0.0;
   out_3992538829710935120[317] = 0.0;
   out_3992538829710935120[318] = 0.0;
   out_3992538829710935120[319] = 0.0;
   out_3992538829710935120[320] = 0.0;
   out_3992538829710935120[321] = 0.0;
   out_3992538829710935120[322] = 0.0;
   out_3992538829710935120[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8224128290291442758) {
   out_8224128290291442758[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8224128290291442758[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8224128290291442758[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8224128290291442758[3] = dt*state[12] + state[3];
   out_8224128290291442758[4] = dt*state[13] + state[4];
   out_8224128290291442758[5] = dt*state[14] + state[5];
   out_8224128290291442758[6] = state[6];
   out_8224128290291442758[7] = state[7];
   out_8224128290291442758[8] = state[8];
   out_8224128290291442758[9] = state[9];
   out_8224128290291442758[10] = state[10];
   out_8224128290291442758[11] = state[11];
   out_8224128290291442758[12] = state[12];
   out_8224128290291442758[13] = state[13];
   out_8224128290291442758[14] = state[14];
   out_8224128290291442758[15] = state[15];
   out_8224128290291442758[16] = state[16];
   out_8224128290291442758[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4173313334813114557) {
   out_4173313334813114557[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4173313334813114557[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4173313334813114557[2] = 0;
   out_4173313334813114557[3] = 0;
   out_4173313334813114557[4] = 0;
   out_4173313334813114557[5] = 0;
   out_4173313334813114557[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4173313334813114557[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4173313334813114557[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4173313334813114557[9] = 0;
   out_4173313334813114557[10] = 0;
   out_4173313334813114557[11] = 0;
   out_4173313334813114557[12] = 0;
   out_4173313334813114557[13] = 0;
   out_4173313334813114557[14] = 0;
   out_4173313334813114557[15] = 0;
   out_4173313334813114557[16] = 0;
   out_4173313334813114557[17] = 0;
   out_4173313334813114557[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4173313334813114557[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4173313334813114557[20] = 0;
   out_4173313334813114557[21] = 0;
   out_4173313334813114557[22] = 0;
   out_4173313334813114557[23] = 0;
   out_4173313334813114557[24] = 0;
   out_4173313334813114557[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4173313334813114557[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4173313334813114557[27] = 0;
   out_4173313334813114557[28] = 0;
   out_4173313334813114557[29] = 0;
   out_4173313334813114557[30] = 0;
   out_4173313334813114557[31] = 0;
   out_4173313334813114557[32] = 0;
   out_4173313334813114557[33] = 0;
   out_4173313334813114557[34] = 0;
   out_4173313334813114557[35] = 0;
   out_4173313334813114557[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4173313334813114557[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4173313334813114557[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4173313334813114557[39] = 0;
   out_4173313334813114557[40] = 0;
   out_4173313334813114557[41] = 0;
   out_4173313334813114557[42] = 0;
   out_4173313334813114557[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4173313334813114557[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4173313334813114557[45] = 0;
   out_4173313334813114557[46] = 0;
   out_4173313334813114557[47] = 0;
   out_4173313334813114557[48] = 0;
   out_4173313334813114557[49] = 0;
   out_4173313334813114557[50] = 0;
   out_4173313334813114557[51] = 0;
   out_4173313334813114557[52] = 0;
   out_4173313334813114557[53] = 0;
   out_4173313334813114557[54] = 0;
   out_4173313334813114557[55] = 0;
   out_4173313334813114557[56] = 0;
   out_4173313334813114557[57] = 1;
   out_4173313334813114557[58] = 0;
   out_4173313334813114557[59] = 0;
   out_4173313334813114557[60] = 0;
   out_4173313334813114557[61] = 0;
   out_4173313334813114557[62] = 0;
   out_4173313334813114557[63] = 0;
   out_4173313334813114557[64] = 0;
   out_4173313334813114557[65] = 0;
   out_4173313334813114557[66] = dt;
   out_4173313334813114557[67] = 0;
   out_4173313334813114557[68] = 0;
   out_4173313334813114557[69] = 0;
   out_4173313334813114557[70] = 0;
   out_4173313334813114557[71] = 0;
   out_4173313334813114557[72] = 0;
   out_4173313334813114557[73] = 0;
   out_4173313334813114557[74] = 0;
   out_4173313334813114557[75] = 0;
   out_4173313334813114557[76] = 1;
   out_4173313334813114557[77] = 0;
   out_4173313334813114557[78] = 0;
   out_4173313334813114557[79] = 0;
   out_4173313334813114557[80] = 0;
   out_4173313334813114557[81] = 0;
   out_4173313334813114557[82] = 0;
   out_4173313334813114557[83] = 0;
   out_4173313334813114557[84] = 0;
   out_4173313334813114557[85] = dt;
   out_4173313334813114557[86] = 0;
   out_4173313334813114557[87] = 0;
   out_4173313334813114557[88] = 0;
   out_4173313334813114557[89] = 0;
   out_4173313334813114557[90] = 0;
   out_4173313334813114557[91] = 0;
   out_4173313334813114557[92] = 0;
   out_4173313334813114557[93] = 0;
   out_4173313334813114557[94] = 0;
   out_4173313334813114557[95] = 1;
   out_4173313334813114557[96] = 0;
   out_4173313334813114557[97] = 0;
   out_4173313334813114557[98] = 0;
   out_4173313334813114557[99] = 0;
   out_4173313334813114557[100] = 0;
   out_4173313334813114557[101] = 0;
   out_4173313334813114557[102] = 0;
   out_4173313334813114557[103] = 0;
   out_4173313334813114557[104] = dt;
   out_4173313334813114557[105] = 0;
   out_4173313334813114557[106] = 0;
   out_4173313334813114557[107] = 0;
   out_4173313334813114557[108] = 0;
   out_4173313334813114557[109] = 0;
   out_4173313334813114557[110] = 0;
   out_4173313334813114557[111] = 0;
   out_4173313334813114557[112] = 0;
   out_4173313334813114557[113] = 0;
   out_4173313334813114557[114] = 1;
   out_4173313334813114557[115] = 0;
   out_4173313334813114557[116] = 0;
   out_4173313334813114557[117] = 0;
   out_4173313334813114557[118] = 0;
   out_4173313334813114557[119] = 0;
   out_4173313334813114557[120] = 0;
   out_4173313334813114557[121] = 0;
   out_4173313334813114557[122] = 0;
   out_4173313334813114557[123] = 0;
   out_4173313334813114557[124] = 0;
   out_4173313334813114557[125] = 0;
   out_4173313334813114557[126] = 0;
   out_4173313334813114557[127] = 0;
   out_4173313334813114557[128] = 0;
   out_4173313334813114557[129] = 0;
   out_4173313334813114557[130] = 0;
   out_4173313334813114557[131] = 0;
   out_4173313334813114557[132] = 0;
   out_4173313334813114557[133] = 1;
   out_4173313334813114557[134] = 0;
   out_4173313334813114557[135] = 0;
   out_4173313334813114557[136] = 0;
   out_4173313334813114557[137] = 0;
   out_4173313334813114557[138] = 0;
   out_4173313334813114557[139] = 0;
   out_4173313334813114557[140] = 0;
   out_4173313334813114557[141] = 0;
   out_4173313334813114557[142] = 0;
   out_4173313334813114557[143] = 0;
   out_4173313334813114557[144] = 0;
   out_4173313334813114557[145] = 0;
   out_4173313334813114557[146] = 0;
   out_4173313334813114557[147] = 0;
   out_4173313334813114557[148] = 0;
   out_4173313334813114557[149] = 0;
   out_4173313334813114557[150] = 0;
   out_4173313334813114557[151] = 0;
   out_4173313334813114557[152] = 1;
   out_4173313334813114557[153] = 0;
   out_4173313334813114557[154] = 0;
   out_4173313334813114557[155] = 0;
   out_4173313334813114557[156] = 0;
   out_4173313334813114557[157] = 0;
   out_4173313334813114557[158] = 0;
   out_4173313334813114557[159] = 0;
   out_4173313334813114557[160] = 0;
   out_4173313334813114557[161] = 0;
   out_4173313334813114557[162] = 0;
   out_4173313334813114557[163] = 0;
   out_4173313334813114557[164] = 0;
   out_4173313334813114557[165] = 0;
   out_4173313334813114557[166] = 0;
   out_4173313334813114557[167] = 0;
   out_4173313334813114557[168] = 0;
   out_4173313334813114557[169] = 0;
   out_4173313334813114557[170] = 0;
   out_4173313334813114557[171] = 1;
   out_4173313334813114557[172] = 0;
   out_4173313334813114557[173] = 0;
   out_4173313334813114557[174] = 0;
   out_4173313334813114557[175] = 0;
   out_4173313334813114557[176] = 0;
   out_4173313334813114557[177] = 0;
   out_4173313334813114557[178] = 0;
   out_4173313334813114557[179] = 0;
   out_4173313334813114557[180] = 0;
   out_4173313334813114557[181] = 0;
   out_4173313334813114557[182] = 0;
   out_4173313334813114557[183] = 0;
   out_4173313334813114557[184] = 0;
   out_4173313334813114557[185] = 0;
   out_4173313334813114557[186] = 0;
   out_4173313334813114557[187] = 0;
   out_4173313334813114557[188] = 0;
   out_4173313334813114557[189] = 0;
   out_4173313334813114557[190] = 1;
   out_4173313334813114557[191] = 0;
   out_4173313334813114557[192] = 0;
   out_4173313334813114557[193] = 0;
   out_4173313334813114557[194] = 0;
   out_4173313334813114557[195] = 0;
   out_4173313334813114557[196] = 0;
   out_4173313334813114557[197] = 0;
   out_4173313334813114557[198] = 0;
   out_4173313334813114557[199] = 0;
   out_4173313334813114557[200] = 0;
   out_4173313334813114557[201] = 0;
   out_4173313334813114557[202] = 0;
   out_4173313334813114557[203] = 0;
   out_4173313334813114557[204] = 0;
   out_4173313334813114557[205] = 0;
   out_4173313334813114557[206] = 0;
   out_4173313334813114557[207] = 0;
   out_4173313334813114557[208] = 0;
   out_4173313334813114557[209] = 1;
   out_4173313334813114557[210] = 0;
   out_4173313334813114557[211] = 0;
   out_4173313334813114557[212] = 0;
   out_4173313334813114557[213] = 0;
   out_4173313334813114557[214] = 0;
   out_4173313334813114557[215] = 0;
   out_4173313334813114557[216] = 0;
   out_4173313334813114557[217] = 0;
   out_4173313334813114557[218] = 0;
   out_4173313334813114557[219] = 0;
   out_4173313334813114557[220] = 0;
   out_4173313334813114557[221] = 0;
   out_4173313334813114557[222] = 0;
   out_4173313334813114557[223] = 0;
   out_4173313334813114557[224] = 0;
   out_4173313334813114557[225] = 0;
   out_4173313334813114557[226] = 0;
   out_4173313334813114557[227] = 0;
   out_4173313334813114557[228] = 1;
   out_4173313334813114557[229] = 0;
   out_4173313334813114557[230] = 0;
   out_4173313334813114557[231] = 0;
   out_4173313334813114557[232] = 0;
   out_4173313334813114557[233] = 0;
   out_4173313334813114557[234] = 0;
   out_4173313334813114557[235] = 0;
   out_4173313334813114557[236] = 0;
   out_4173313334813114557[237] = 0;
   out_4173313334813114557[238] = 0;
   out_4173313334813114557[239] = 0;
   out_4173313334813114557[240] = 0;
   out_4173313334813114557[241] = 0;
   out_4173313334813114557[242] = 0;
   out_4173313334813114557[243] = 0;
   out_4173313334813114557[244] = 0;
   out_4173313334813114557[245] = 0;
   out_4173313334813114557[246] = 0;
   out_4173313334813114557[247] = 1;
   out_4173313334813114557[248] = 0;
   out_4173313334813114557[249] = 0;
   out_4173313334813114557[250] = 0;
   out_4173313334813114557[251] = 0;
   out_4173313334813114557[252] = 0;
   out_4173313334813114557[253] = 0;
   out_4173313334813114557[254] = 0;
   out_4173313334813114557[255] = 0;
   out_4173313334813114557[256] = 0;
   out_4173313334813114557[257] = 0;
   out_4173313334813114557[258] = 0;
   out_4173313334813114557[259] = 0;
   out_4173313334813114557[260] = 0;
   out_4173313334813114557[261] = 0;
   out_4173313334813114557[262] = 0;
   out_4173313334813114557[263] = 0;
   out_4173313334813114557[264] = 0;
   out_4173313334813114557[265] = 0;
   out_4173313334813114557[266] = 1;
   out_4173313334813114557[267] = 0;
   out_4173313334813114557[268] = 0;
   out_4173313334813114557[269] = 0;
   out_4173313334813114557[270] = 0;
   out_4173313334813114557[271] = 0;
   out_4173313334813114557[272] = 0;
   out_4173313334813114557[273] = 0;
   out_4173313334813114557[274] = 0;
   out_4173313334813114557[275] = 0;
   out_4173313334813114557[276] = 0;
   out_4173313334813114557[277] = 0;
   out_4173313334813114557[278] = 0;
   out_4173313334813114557[279] = 0;
   out_4173313334813114557[280] = 0;
   out_4173313334813114557[281] = 0;
   out_4173313334813114557[282] = 0;
   out_4173313334813114557[283] = 0;
   out_4173313334813114557[284] = 0;
   out_4173313334813114557[285] = 1;
   out_4173313334813114557[286] = 0;
   out_4173313334813114557[287] = 0;
   out_4173313334813114557[288] = 0;
   out_4173313334813114557[289] = 0;
   out_4173313334813114557[290] = 0;
   out_4173313334813114557[291] = 0;
   out_4173313334813114557[292] = 0;
   out_4173313334813114557[293] = 0;
   out_4173313334813114557[294] = 0;
   out_4173313334813114557[295] = 0;
   out_4173313334813114557[296] = 0;
   out_4173313334813114557[297] = 0;
   out_4173313334813114557[298] = 0;
   out_4173313334813114557[299] = 0;
   out_4173313334813114557[300] = 0;
   out_4173313334813114557[301] = 0;
   out_4173313334813114557[302] = 0;
   out_4173313334813114557[303] = 0;
   out_4173313334813114557[304] = 1;
   out_4173313334813114557[305] = 0;
   out_4173313334813114557[306] = 0;
   out_4173313334813114557[307] = 0;
   out_4173313334813114557[308] = 0;
   out_4173313334813114557[309] = 0;
   out_4173313334813114557[310] = 0;
   out_4173313334813114557[311] = 0;
   out_4173313334813114557[312] = 0;
   out_4173313334813114557[313] = 0;
   out_4173313334813114557[314] = 0;
   out_4173313334813114557[315] = 0;
   out_4173313334813114557[316] = 0;
   out_4173313334813114557[317] = 0;
   out_4173313334813114557[318] = 0;
   out_4173313334813114557[319] = 0;
   out_4173313334813114557[320] = 0;
   out_4173313334813114557[321] = 0;
   out_4173313334813114557[322] = 0;
   out_4173313334813114557[323] = 1;
}
void h_4(double *state, double *unused, double *out_8461717180408587044) {
   out_8461717180408587044[0] = state[6] + state[9];
   out_8461717180408587044[1] = state[7] + state[10];
   out_8461717180408587044[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2172840103804638259) {
   out_2172840103804638259[0] = 0;
   out_2172840103804638259[1] = 0;
   out_2172840103804638259[2] = 0;
   out_2172840103804638259[3] = 0;
   out_2172840103804638259[4] = 0;
   out_2172840103804638259[5] = 0;
   out_2172840103804638259[6] = 1;
   out_2172840103804638259[7] = 0;
   out_2172840103804638259[8] = 0;
   out_2172840103804638259[9] = 1;
   out_2172840103804638259[10] = 0;
   out_2172840103804638259[11] = 0;
   out_2172840103804638259[12] = 0;
   out_2172840103804638259[13] = 0;
   out_2172840103804638259[14] = 0;
   out_2172840103804638259[15] = 0;
   out_2172840103804638259[16] = 0;
   out_2172840103804638259[17] = 0;
   out_2172840103804638259[18] = 0;
   out_2172840103804638259[19] = 0;
   out_2172840103804638259[20] = 0;
   out_2172840103804638259[21] = 0;
   out_2172840103804638259[22] = 0;
   out_2172840103804638259[23] = 0;
   out_2172840103804638259[24] = 0;
   out_2172840103804638259[25] = 1;
   out_2172840103804638259[26] = 0;
   out_2172840103804638259[27] = 0;
   out_2172840103804638259[28] = 1;
   out_2172840103804638259[29] = 0;
   out_2172840103804638259[30] = 0;
   out_2172840103804638259[31] = 0;
   out_2172840103804638259[32] = 0;
   out_2172840103804638259[33] = 0;
   out_2172840103804638259[34] = 0;
   out_2172840103804638259[35] = 0;
   out_2172840103804638259[36] = 0;
   out_2172840103804638259[37] = 0;
   out_2172840103804638259[38] = 0;
   out_2172840103804638259[39] = 0;
   out_2172840103804638259[40] = 0;
   out_2172840103804638259[41] = 0;
   out_2172840103804638259[42] = 0;
   out_2172840103804638259[43] = 0;
   out_2172840103804638259[44] = 1;
   out_2172840103804638259[45] = 0;
   out_2172840103804638259[46] = 0;
   out_2172840103804638259[47] = 1;
   out_2172840103804638259[48] = 0;
   out_2172840103804638259[49] = 0;
   out_2172840103804638259[50] = 0;
   out_2172840103804638259[51] = 0;
   out_2172840103804638259[52] = 0;
   out_2172840103804638259[53] = 0;
}
void h_10(double *state, double *unused, double *out_2633265206766799101) {
   out_2633265206766799101[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2633265206766799101[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2633265206766799101[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3904041767468690216) {
   out_3904041767468690216[0] = 0;
   out_3904041767468690216[1] = 9.8100000000000005*cos(state[1]);
   out_3904041767468690216[2] = 0;
   out_3904041767468690216[3] = 0;
   out_3904041767468690216[4] = -state[8];
   out_3904041767468690216[5] = state[7];
   out_3904041767468690216[6] = 0;
   out_3904041767468690216[7] = state[5];
   out_3904041767468690216[8] = -state[4];
   out_3904041767468690216[9] = 0;
   out_3904041767468690216[10] = 0;
   out_3904041767468690216[11] = 0;
   out_3904041767468690216[12] = 1;
   out_3904041767468690216[13] = 0;
   out_3904041767468690216[14] = 0;
   out_3904041767468690216[15] = 1;
   out_3904041767468690216[16] = 0;
   out_3904041767468690216[17] = 0;
   out_3904041767468690216[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3904041767468690216[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3904041767468690216[20] = 0;
   out_3904041767468690216[21] = state[8];
   out_3904041767468690216[22] = 0;
   out_3904041767468690216[23] = -state[6];
   out_3904041767468690216[24] = -state[5];
   out_3904041767468690216[25] = 0;
   out_3904041767468690216[26] = state[3];
   out_3904041767468690216[27] = 0;
   out_3904041767468690216[28] = 0;
   out_3904041767468690216[29] = 0;
   out_3904041767468690216[30] = 0;
   out_3904041767468690216[31] = 1;
   out_3904041767468690216[32] = 0;
   out_3904041767468690216[33] = 0;
   out_3904041767468690216[34] = 1;
   out_3904041767468690216[35] = 0;
   out_3904041767468690216[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3904041767468690216[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3904041767468690216[38] = 0;
   out_3904041767468690216[39] = -state[7];
   out_3904041767468690216[40] = state[6];
   out_3904041767468690216[41] = 0;
   out_3904041767468690216[42] = state[4];
   out_3904041767468690216[43] = -state[3];
   out_3904041767468690216[44] = 0;
   out_3904041767468690216[45] = 0;
   out_3904041767468690216[46] = 0;
   out_3904041767468690216[47] = 0;
   out_3904041767468690216[48] = 0;
   out_3904041767468690216[49] = 0;
   out_3904041767468690216[50] = 1;
   out_3904041767468690216[51] = 0;
   out_3904041767468690216[52] = 0;
   out_3904041767468690216[53] = 1;
}
void h_13(double *state, double *unused, double *out_3680645971147336893) {
   out_3680645971147336893[0] = state[3];
   out_3680645971147336893[1] = state[4];
   out_3680645971147336893[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5385113929136971060) {
   out_5385113929136971060[0] = 0;
   out_5385113929136971060[1] = 0;
   out_5385113929136971060[2] = 0;
   out_5385113929136971060[3] = 1;
   out_5385113929136971060[4] = 0;
   out_5385113929136971060[5] = 0;
   out_5385113929136971060[6] = 0;
   out_5385113929136971060[7] = 0;
   out_5385113929136971060[8] = 0;
   out_5385113929136971060[9] = 0;
   out_5385113929136971060[10] = 0;
   out_5385113929136971060[11] = 0;
   out_5385113929136971060[12] = 0;
   out_5385113929136971060[13] = 0;
   out_5385113929136971060[14] = 0;
   out_5385113929136971060[15] = 0;
   out_5385113929136971060[16] = 0;
   out_5385113929136971060[17] = 0;
   out_5385113929136971060[18] = 0;
   out_5385113929136971060[19] = 0;
   out_5385113929136971060[20] = 0;
   out_5385113929136971060[21] = 0;
   out_5385113929136971060[22] = 1;
   out_5385113929136971060[23] = 0;
   out_5385113929136971060[24] = 0;
   out_5385113929136971060[25] = 0;
   out_5385113929136971060[26] = 0;
   out_5385113929136971060[27] = 0;
   out_5385113929136971060[28] = 0;
   out_5385113929136971060[29] = 0;
   out_5385113929136971060[30] = 0;
   out_5385113929136971060[31] = 0;
   out_5385113929136971060[32] = 0;
   out_5385113929136971060[33] = 0;
   out_5385113929136971060[34] = 0;
   out_5385113929136971060[35] = 0;
   out_5385113929136971060[36] = 0;
   out_5385113929136971060[37] = 0;
   out_5385113929136971060[38] = 0;
   out_5385113929136971060[39] = 0;
   out_5385113929136971060[40] = 0;
   out_5385113929136971060[41] = 1;
   out_5385113929136971060[42] = 0;
   out_5385113929136971060[43] = 0;
   out_5385113929136971060[44] = 0;
   out_5385113929136971060[45] = 0;
   out_5385113929136971060[46] = 0;
   out_5385113929136971060[47] = 0;
   out_5385113929136971060[48] = 0;
   out_5385113929136971060[49] = 0;
   out_5385113929136971060[50] = 0;
   out_5385113929136971060[51] = 0;
   out_5385113929136971060[52] = 0;
   out_5385113929136971060[53] = 0;
}
void h_14(double *state, double *unused, double *out_5848550976228580590) {
   out_5848550976228580590[0] = state[6];
   out_5848550976228580590[1] = state[7];
   out_5848550976228580590[2] = state[8];
}
void H_14(double *state, double *unused, double *out_909948328490734037) {
   out_909948328490734037[0] = 0;
   out_909948328490734037[1] = 0;
   out_909948328490734037[2] = 0;
   out_909948328490734037[3] = 0;
   out_909948328490734037[4] = 0;
   out_909948328490734037[5] = 0;
   out_909948328490734037[6] = 1;
   out_909948328490734037[7] = 0;
   out_909948328490734037[8] = 0;
   out_909948328490734037[9] = 0;
   out_909948328490734037[10] = 0;
   out_909948328490734037[11] = 0;
   out_909948328490734037[12] = 0;
   out_909948328490734037[13] = 0;
   out_909948328490734037[14] = 0;
   out_909948328490734037[15] = 0;
   out_909948328490734037[16] = 0;
   out_909948328490734037[17] = 0;
   out_909948328490734037[18] = 0;
   out_909948328490734037[19] = 0;
   out_909948328490734037[20] = 0;
   out_909948328490734037[21] = 0;
   out_909948328490734037[22] = 0;
   out_909948328490734037[23] = 0;
   out_909948328490734037[24] = 0;
   out_909948328490734037[25] = 1;
   out_909948328490734037[26] = 0;
   out_909948328490734037[27] = 0;
   out_909948328490734037[28] = 0;
   out_909948328490734037[29] = 0;
   out_909948328490734037[30] = 0;
   out_909948328490734037[31] = 0;
   out_909948328490734037[32] = 0;
   out_909948328490734037[33] = 0;
   out_909948328490734037[34] = 0;
   out_909948328490734037[35] = 0;
   out_909948328490734037[36] = 0;
   out_909948328490734037[37] = 0;
   out_909948328490734037[38] = 0;
   out_909948328490734037[39] = 0;
   out_909948328490734037[40] = 0;
   out_909948328490734037[41] = 0;
   out_909948328490734037[42] = 0;
   out_909948328490734037[43] = 0;
   out_909948328490734037[44] = 1;
   out_909948328490734037[45] = 0;
   out_909948328490734037[46] = 0;
   out_909948328490734037[47] = 0;
   out_909948328490734037[48] = 0;
   out_909948328490734037[49] = 0;
   out_909948328490734037[50] = 0;
   out_909948328490734037[51] = 0;
   out_909948328490734037[52] = 0;
   out_909948328490734037[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2550502777521953992) {
  err_fun(nom_x, delta_x, out_2550502777521953992);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2991013798952875835) {
  inv_err_fun(nom_x, true_x, out_2991013798952875835);
}
void pose_H_mod_fun(double *state, double *out_3992538829710935120) {
  H_mod_fun(state, out_3992538829710935120);
}
void pose_f_fun(double *state, double dt, double *out_8224128290291442758) {
  f_fun(state,  dt, out_8224128290291442758);
}
void pose_F_fun(double *state, double dt, double *out_4173313334813114557) {
  F_fun(state,  dt, out_4173313334813114557);
}
void pose_h_4(double *state, double *unused, double *out_8461717180408587044) {
  h_4(state, unused, out_8461717180408587044);
}
void pose_H_4(double *state, double *unused, double *out_2172840103804638259) {
  H_4(state, unused, out_2172840103804638259);
}
void pose_h_10(double *state, double *unused, double *out_2633265206766799101) {
  h_10(state, unused, out_2633265206766799101);
}
void pose_H_10(double *state, double *unused, double *out_3904041767468690216) {
  H_10(state, unused, out_3904041767468690216);
}
void pose_h_13(double *state, double *unused, double *out_3680645971147336893) {
  h_13(state, unused, out_3680645971147336893);
}
void pose_H_13(double *state, double *unused, double *out_5385113929136971060) {
  H_13(state, unused, out_5385113929136971060);
}
void pose_h_14(double *state, double *unused, double *out_5848550976228580590) {
  h_14(state, unused, out_5848550976228580590);
}
void pose_H_14(double *state, double *unused, double *out_909948328490734037) {
  H_14(state, unused, out_909948328490734037);
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
