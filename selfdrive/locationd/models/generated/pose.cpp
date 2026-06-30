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
void err_fun(double *nom_x, double *delta_x, double *out_1773490464841058211) {
   out_1773490464841058211[0] = delta_x[0] + nom_x[0];
   out_1773490464841058211[1] = delta_x[1] + nom_x[1];
   out_1773490464841058211[2] = delta_x[2] + nom_x[2];
   out_1773490464841058211[3] = delta_x[3] + nom_x[3];
   out_1773490464841058211[4] = delta_x[4] + nom_x[4];
   out_1773490464841058211[5] = delta_x[5] + nom_x[5];
   out_1773490464841058211[6] = delta_x[6] + nom_x[6];
   out_1773490464841058211[7] = delta_x[7] + nom_x[7];
   out_1773490464841058211[8] = delta_x[8] + nom_x[8];
   out_1773490464841058211[9] = delta_x[9] + nom_x[9];
   out_1773490464841058211[10] = delta_x[10] + nom_x[10];
   out_1773490464841058211[11] = delta_x[11] + nom_x[11];
   out_1773490464841058211[12] = delta_x[12] + nom_x[12];
   out_1773490464841058211[13] = delta_x[13] + nom_x[13];
   out_1773490464841058211[14] = delta_x[14] + nom_x[14];
   out_1773490464841058211[15] = delta_x[15] + nom_x[15];
   out_1773490464841058211[16] = delta_x[16] + nom_x[16];
   out_1773490464841058211[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3370820179269337821) {
   out_3370820179269337821[0] = -nom_x[0] + true_x[0];
   out_3370820179269337821[1] = -nom_x[1] + true_x[1];
   out_3370820179269337821[2] = -nom_x[2] + true_x[2];
   out_3370820179269337821[3] = -nom_x[3] + true_x[3];
   out_3370820179269337821[4] = -nom_x[4] + true_x[4];
   out_3370820179269337821[5] = -nom_x[5] + true_x[5];
   out_3370820179269337821[6] = -nom_x[6] + true_x[6];
   out_3370820179269337821[7] = -nom_x[7] + true_x[7];
   out_3370820179269337821[8] = -nom_x[8] + true_x[8];
   out_3370820179269337821[9] = -nom_x[9] + true_x[9];
   out_3370820179269337821[10] = -nom_x[10] + true_x[10];
   out_3370820179269337821[11] = -nom_x[11] + true_x[11];
   out_3370820179269337821[12] = -nom_x[12] + true_x[12];
   out_3370820179269337821[13] = -nom_x[13] + true_x[13];
   out_3370820179269337821[14] = -nom_x[14] + true_x[14];
   out_3370820179269337821[15] = -nom_x[15] + true_x[15];
   out_3370820179269337821[16] = -nom_x[16] + true_x[16];
   out_3370820179269337821[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8103172798179963867) {
   out_8103172798179963867[0] = 1.0;
   out_8103172798179963867[1] = 0.0;
   out_8103172798179963867[2] = 0.0;
   out_8103172798179963867[3] = 0.0;
   out_8103172798179963867[4] = 0.0;
   out_8103172798179963867[5] = 0.0;
   out_8103172798179963867[6] = 0.0;
   out_8103172798179963867[7] = 0.0;
   out_8103172798179963867[8] = 0.0;
   out_8103172798179963867[9] = 0.0;
   out_8103172798179963867[10] = 0.0;
   out_8103172798179963867[11] = 0.0;
   out_8103172798179963867[12] = 0.0;
   out_8103172798179963867[13] = 0.0;
   out_8103172798179963867[14] = 0.0;
   out_8103172798179963867[15] = 0.0;
   out_8103172798179963867[16] = 0.0;
   out_8103172798179963867[17] = 0.0;
   out_8103172798179963867[18] = 0.0;
   out_8103172798179963867[19] = 1.0;
   out_8103172798179963867[20] = 0.0;
   out_8103172798179963867[21] = 0.0;
   out_8103172798179963867[22] = 0.0;
   out_8103172798179963867[23] = 0.0;
   out_8103172798179963867[24] = 0.0;
   out_8103172798179963867[25] = 0.0;
   out_8103172798179963867[26] = 0.0;
   out_8103172798179963867[27] = 0.0;
   out_8103172798179963867[28] = 0.0;
   out_8103172798179963867[29] = 0.0;
   out_8103172798179963867[30] = 0.0;
   out_8103172798179963867[31] = 0.0;
   out_8103172798179963867[32] = 0.0;
   out_8103172798179963867[33] = 0.0;
   out_8103172798179963867[34] = 0.0;
   out_8103172798179963867[35] = 0.0;
   out_8103172798179963867[36] = 0.0;
   out_8103172798179963867[37] = 0.0;
   out_8103172798179963867[38] = 1.0;
   out_8103172798179963867[39] = 0.0;
   out_8103172798179963867[40] = 0.0;
   out_8103172798179963867[41] = 0.0;
   out_8103172798179963867[42] = 0.0;
   out_8103172798179963867[43] = 0.0;
   out_8103172798179963867[44] = 0.0;
   out_8103172798179963867[45] = 0.0;
   out_8103172798179963867[46] = 0.0;
   out_8103172798179963867[47] = 0.0;
   out_8103172798179963867[48] = 0.0;
   out_8103172798179963867[49] = 0.0;
   out_8103172798179963867[50] = 0.0;
   out_8103172798179963867[51] = 0.0;
   out_8103172798179963867[52] = 0.0;
   out_8103172798179963867[53] = 0.0;
   out_8103172798179963867[54] = 0.0;
   out_8103172798179963867[55] = 0.0;
   out_8103172798179963867[56] = 0.0;
   out_8103172798179963867[57] = 1.0;
   out_8103172798179963867[58] = 0.0;
   out_8103172798179963867[59] = 0.0;
   out_8103172798179963867[60] = 0.0;
   out_8103172798179963867[61] = 0.0;
   out_8103172798179963867[62] = 0.0;
   out_8103172798179963867[63] = 0.0;
   out_8103172798179963867[64] = 0.0;
   out_8103172798179963867[65] = 0.0;
   out_8103172798179963867[66] = 0.0;
   out_8103172798179963867[67] = 0.0;
   out_8103172798179963867[68] = 0.0;
   out_8103172798179963867[69] = 0.0;
   out_8103172798179963867[70] = 0.0;
   out_8103172798179963867[71] = 0.0;
   out_8103172798179963867[72] = 0.0;
   out_8103172798179963867[73] = 0.0;
   out_8103172798179963867[74] = 0.0;
   out_8103172798179963867[75] = 0.0;
   out_8103172798179963867[76] = 1.0;
   out_8103172798179963867[77] = 0.0;
   out_8103172798179963867[78] = 0.0;
   out_8103172798179963867[79] = 0.0;
   out_8103172798179963867[80] = 0.0;
   out_8103172798179963867[81] = 0.0;
   out_8103172798179963867[82] = 0.0;
   out_8103172798179963867[83] = 0.0;
   out_8103172798179963867[84] = 0.0;
   out_8103172798179963867[85] = 0.0;
   out_8103172798179963867[86] = 0.0;
   out_8103172798179963867[87] = 0.0;
   out_8103172798179963867[88] = 0.0;
   out_8103172798179963867[89] = 0.0;
   out_8103172798179963867[90] = 0.0;
   out_8103172798179963867[91] = 0.0;
   out_8103172798179963867[92] = 0.0;
   out_8103172798179963867[93] = 0.0;
   out_8103172798179963867[94] = 0.0;
   out_8103172798179963867[95] = 1.0;
   out_8103172798179963867[96] = 0.0;
   out_8103172798179963867[97] = 0.0;
   out_8103172798179963867[98] = 0.0;
   out_8103172798179963867[99] = 0.0;
   out_8103172798179963867[100] = 0.0;
   out_8103172798179963867[101] = 0.0;
   out_8103172798179963867[102] = 0.0;
   out_8103172798179963867[103] = 0.0;
   out_8103172798179963867[104] = 0.0;
   out_8103172798179963867[105] = 0.0;
   out_8103172798179963867[106] = 0.0;
   out_8103172798179963867[107] = 0.0;
   out_8103172798179963867[108] = 0.0;
   out_8103172798179963867[109] = 0.0;
   out_8103172798179963867[110] = 0.0;
   out_8103172798179963867[111] = 0.0;
   out_8103172798179963867[112] = 0.0;
   out_8103172798179963867[113] = 0.0;
   out_8103172798179963867[114] = 1.0;
   out_8103172798179963867[115] = 0.0;
   out_8103172798179963867[116] = 0.0;
   out_8103172798179963867[117] = 0.0;
   out_8103172798179963867[118] = 0.0;
   out_8103172798179963867[119] = 0.0;
   out_8103172798179963867[120] = 0.0;
   out_8103172798179963867[121] = 0.0;
   out_8103172798179963867[122] = 0.0;
   out_8103172798179963867[123] = 0.0;
   out_8103172798179963867[124] = 0.0;
   out_8103172798179963867[125] = 0.0;
   out_8103172798179963867[126] = 0.0;
   out_8103172798179963867[127] = 0.0;
   out_8103172798179963867[128] = 0.0;
   out_8103172798179963867[129] = 0.0;
   out_8103172798179963867[130] = 0.0;
   out_8103172798179963867[131] = 0.0;
   out_8103172798179963867[132] = 0.0;
   out_8103172798179963867[133] = 1.0;
   out_8103172798179963867[134] = 0.0;
   out_8103172798179963867[135] = 0.0;
   out_8103172798179963867[136] = 0.0;
   out_8103172798179963867[137] = 0.0;
   out_8103172798179963867[138] = 0.0;
   out_8103172798179963867[139] = 0.0;
   out_8103172798179963867[140] = 0.0;
   out_8103172798179963867[141] = 0.0;
   out_8103172798179963867[142] = 0.0;
   out_8103172798179963867[143] = 0.0;
   out_8103172798179963867[144] = 0.0;
   out_8103172798179963867[145] = 0.0;
   out_8103172798179963867[146] = 0.0;
   out_8103172798179963867[147] = 0.0;
   out_8103172798179963867[148] = 0.0;
   out_8103172798179963867[149] = 0.0;
   out_8103172798179963867[150] = 0.0;
   out_8103172798179963867[151] = 0.0;
   out_8103172798179963867[152] = 1.0;
   out_8103172798179963867[153] = 0.0;
   out_8103172798179963867[154] = 0.0;
   out_8103172798179963867[155] = 0.0;
   out_8103172798179963867[156] = 0.0;
   out_8103172798179963867[157] = 0.0;
   out_8103172798179963867[158] = 0.0;
   out_8103172798179963867[159] = 0.0;
   out_8103172798179963867[160] = 0.0;
   out_8103172798179963867[161] = 0.0;
   out_8103172798179963867[162] = 0.0;
   out_8103172798179963867[163] = 0.0;
   out_8103172798179963867[164] = 0.0;
   out_8103172798179963867[165] = 0.0;
   out_8103172798179963867[166] = 0.0;
   out_8103172798179963867[167] = 0.0;
   out_8103172798179963867[168] = 0.0;
   out_8103172798179963867[169] = 0.0;
   out_8103172798179963867[170] = 0.0;
   out_8103172798179963867[171] = 1.0;
   out_8103172798179963867[172] = 0.0;
   out_8103172798179963867[173] = 0.0;
   out_8103172798179963867[174] = 0.0;
   out_8103172798179963867[175] = 0.0;
   out_8103172798179963867[176] = 0.0;
   out_8103172798179963867[177] = 0.0;
   out_8103172798179963867[178] = 0.0;
   out_8103172798179963867[179] = 0.0;
   out_8103172798179963867[180] = 0.0;
   out_8103172798179963867[181] = 0.0;
   out_8103172798179963867[182] = 0.0;
   out_8103172798179963867[183] = 0.0;
   out_8103172798179963867[184] = 0.0;
   out_8103172798179963867[185] = 0.0;
   out_8103172798179963867[186] = 0.0;
   out_8103172798179963867[187] = 0.0;
   out_8103172798179963867[188] = 0.0;
   out_8103172798179963867[189] = 0.0;
   out_8103172798179963867[190] = 1.0;
   out_8103172798179963867[191] = 0.0;
   out_8103172798179963867[192] = 0.0;
   out_8103172798179963867[193] = 0.0;
   out_8103172798179963867[194] = 0.0;
   out_8103172798179963867[195] = 0.0;
   out_8103172798179963867[196] = 0.0;
   out_8103172798179963867[197] = 0.0;
   out_8103172798179963867[198] = 0.0;
   out_8103172798179963867[199] = 0.0;
   out_8103172798179963867[200] = 0.0;
   out_8103172798179963867[201] = 0.0;
   out_8103172798179963867[202] = 0.0;
   out_8103172798179963867[203] = 0.0;
   out_8103172798179963867[204] = 0.0;
   out_8103172798179963867[205] = 0.0;
   out_8103172798179963867[206] = 0.0;
   out_8103172798179963867[207] = 0.0;
   out_8103172798179963867[208] = 0.0;
   out_8103172798179963867[209] = 1.0;
   out_8103172798179963867[210] = 0.0;
   out_8103172798179963867[211] = 0.0;
   out_8103172798179963867[212] = 0.0;
   out_8103172798179963867[213] = 0.0;
   out_8103172798179963867[214] = 0.0;
   out_8103172798179963867[215] = 0.0;
   out_8103172798179963867[216] = 0.0;
   out_8103172798179963867[217] = 0.0;
   out_8103172798179963867[218] = 0.0;
   out_8103172798179963867[219] = 0.0;
   out_8103172798179963867[220] = 0.0;
   out_8103172798179963867[221] = 0.0;
   out_8103172798179963867[222] = 0.0;
   out_8103172798179963867[223] = 0.0;
   out_8103172798179963867[224] = 0.0;
   out_8103172798179963867[225] = 0.0;
   out_8103172798179963867[226] = 0.0;
   out_8103172798179963867[227] = 0.0;
   out_8103172798179963867[228] = 1.0;
   out_8103172798179963867[229] = 0.0;
   out_8103172798179963867[230] = 0.0;
   out_8103172798179963867[231] = 0.0;
   out_8103172798179963867[232] = 0.0;
   out_8103172798179963867[233] = 0.0;
   out_8103172798179963867[234] = 0.0;
   out_8103172798179963867[235] = 0.0;
   out_8103172798179963867[236] = 0.0;
   out_8103172798179963867[237] = 0.0;
   out_8103172798179963867[238] = 0.0;
   out_8103172798179963867[239] = 0.0;
   out_8103172798179963867[240] = 0.0;
   out_8103172798179963867[241] = 0.0;
   out_8103172798179963867[242] = 0.0;
   out_8103172798179963867[243] = 0.0;
   out_8103172798179963867[244] = 0.0;
   out_8103172798179963867[245] = 0.0;
   out_8103172798179963867[246] = 0.0;
   out_8103172798179963867[247] = 1.0;
   out_8103172798179963867[248] = 0.0;
   out_8103172798179963867[249] = 0.0;
   out_8103172798179963867[250] = 0.0;
   out_8103172798179963867[251] = 0.0;
   out_8103172798179963867[252] = 0.0;
   out_8103172798179963867[253] = 0.0;
   out_8103172798179963867[254] = 0.0;
   out_8103172798179963867[255] = 0.0;
   out_8103172798179963867[256] = 0.0;
   out_8103172798179963867[257] = 0.0;
   out_8103172798179963867[258] = 0.0;
   out_8103172798179963867[259] = 0.0;
   out_8103172798179963867[260] = 0.0;
   out_8103172798179963867[261] = 0.0;
   out_8103172798179963867[262] = 0.0;
   out_8103172798179963867[263] = 0.0;
   out_8103172798179963867[264] = 0.0;
   out_8103172798179963867[265] = 0.0;
   out_8103172798179963867[266] = 1.0;
   out_8103172798179963867[267] = 0.0;
   out_8103172798179963867[268] = 0.0;
   out_8103172798179963867[269] = 0.0;
   out_8103172798179963867[270] = 0.0;
   out_8103172798179963867[271] = 0.0;
   out_8103172798179963867[272] = 0.0;
   out_8103172798179963867[273] = 0.0;
   out_8103172798179963867[274] = 0.0;
   out_8103172798179963867[275] = 0.0;
   out_8103172798179963867[276] = 0.0;
   out_8103172798179963867[277] = 0.0;
   out_8103172798179963867[278] = 0.0;
   out_8103172798179963867[279] = 0.0;
   out_8103172798179963867[280] = 0.0;
   out_8103172798179963867[281] = 0.0;
   out_8103172798179963867[282] = 0.0;
   out_8103172798179963867[283] = 0.0;
   out_8103172798179963867[284] = 0.0;
   out_8103172798179963867[285] = 1.0;
   out_8103172798179963867[286] = 0.0;
   out_8103172798179963867[287] = 0.0;
   out_8103172798179963867[288] = 0.0;
   out_8103172798179963867[289] = 0.0;
   out_8103172798179963867[290] = 0.0;
   out_8103172798179963867[291] = 0.0;
   out_8103172798179963867[292] = 0.0;
   out_8103172798179963867[293] = 0.0;
   out_8103172798179963867[294] = 0.0;
   out_8103172798179963867[295] = 0.0;
   out_8103172798179963867[296] = 0.0;
   out_8103172798179963867[297] = 0.0;
   out_8103172798179963867[298] = 0.0;
   out_8103172798179963867[299] = 0.0;
   out_8103172798179963867[300] = 0.0;
   out_8103172798179963867[301] = 0.0;
   out_8103172798179963867[302] = 0.0;
   out_8103172798179963867[303] = 0.0;
   out_8103172798179963867[304] = 1.0;
   out_8103172798179963867[305] = 0.0;
   out_8103172798179963867[306] = 0.0;
   out_8103172798179963867[307] = 0.0;
   out_8103172798179963867[308] = 0.0;
   out_8103172798179963867[309] = 0.0;
   out_8103172798179963867[310] = 0.0;
   out_8103172798179963867[311] = 0.0;
   out_8103172798179963867[312] = 0.0;
   out_8103172798179963867[313] = 0.0;
   out_8103172798179963867[314] = 0.0;
   out_8103172798179963867[315] = 0.0;
   out_8103172798179963867[316] = 0.0;
   out_8103172798179963867[317] = 0.0;
   out_8103172798179963867[318] = 0.0;
   out_8103172798179963867[319] = 0.0;
   out_8103172798179963867[320] = 0.0;
   out_8103172798179963867[321] = 0.0;
   out_8103172798179963867[322] = 0.0;
   out_8103172798179963867[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4130745264458481066) {
   out_4130745264458481066[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4130745264458481066[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4130745264458481066[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4130745264458481066[3] = dt*state[12] + state[3];
   out_4130745264458481066[4] = dt*state[13] + state[4];
   out_4130745264458481066[5] = dt*state[14] + state[5];
   out_4130745264458481066[6] = state[6];
   out_4130745264458481066[7] = state[7];
   out_4130745264458481066[8] = state[8];
   out_4130745264458481066[9] = state[9];
   out_4130745264458481066[10] = state[10];
   out_4130745264458481066[11] = state[11];
   out_4130745264458481066[12] = state[12];
   out_4130745264458481066[13] = state[13];
   out_4130745264458481066[14] = state[14];
   out_4130745264458481066[15] = state[15];
   out_4130745264458481066[16] = state[16];
   out_4130745264458481066[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8817991526926240656) {
   out_8817991526926240656[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8817991526926240656[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8817991526926240656[2] = 0;
   out_8817991526926240656[3] = 0;
   out_8817991526926240656[4] = 0;
   out_8817991526926240656[5] = 0;
   out_8817991526926240656[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8817991526926240656[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8817991526926240656[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8817991526926240656[9] = 0;
   out_8817991526926240656[10] = 0;
   out_8817991526926240656[11] = 0;
   out_8817991526926240656[12] = 0;
   out_8817991526926240656[13] = 0;
   out_8817991526926240656[14] = 0;
   out_8817991526926240656[15] = 0;
   out_8817991526926240656[16] = 0;
   out_8817991526926240656[17] = 0;
   out_8817991526926240656[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8817991526926240656[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8817991526926240656[20] = 0;
   out_8817991526926240656[21] = 0;
   out_8817991526926240656[22] = 0;
   out_8817991526926240656[23] = 0;
   out_8817991526926240656[24] = 0;
   out_8817991526926240656[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8817991526926240656[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8817991526926240656[27] = 0;
   out_8817991526926240656[28] = 0;
   out_8817991526926240656[29] = 0;
   out_8817991526926240656[30] = 0;
   out_8817991526926240656[31] = 0;
   out_8817991526926240656[32] = 0;
   out_8817991526926240656[33] = 0;
   out_8817991526926240656[34] = 0;
   out_8817991526926240656[35] = 0;
   out_8817991526926240656[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8817991526926240656[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8817991526926240656[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8817991526926240656[39] = 0;
   out_8817991526926240656[40] = 0;
   out_8817991526926240656[41] = 0;
   out_8817991526926240656[42] = 0;
   out_8817991526926240656[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8817991526926240656[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8817991526926240656[45] = 0;
   out_8817991526926240656[46] = 0;
   out_8817991526926240656[47] = 0;
   out_8817991526926240656[48] = 0;
   out_8817991526926240656[49] = 0;
   out_8817991526926240656[50] = 0;
   out_8817991526926240656[51] = 0;
   out_8817991526926240656[52] = 0;
   out_8817991526926240656[53] = 0;
   out_8817991526926240656[54] = 0;
   out_8817991526926240656[55] = 0;
   out_8817991526926240656[56] = 0;
   out_8817991526926240656[57] = 1;
   out_8817991526926240656[58] = 0;
   out_8817991526926240656[59] = 0;
   out_8817991526926240656[60] = 0;
   out_8817991526926240656[61] = 0;
   out_8817991526926240656[62] = 0;
   out_8817991526926240656[63] = 0;
   out_8817991526926240656[64] = 0;
   out_8817991526926240656[65] = 0;
   out_8817991526926240656[66] = dt;
   out_8817991526926240656[67] = 0;
   out_8817991526926240656[68] = 0;
   out_8817991526926240656[69] = 0;
   out_8817991526926240656[70] = 0;
   out_8817991526926240656[71] = 0;
   out_8817991526926240656[72] = 0;
   out_8817991526926240656[73] = 0;
   out_8817991526926240656[74] = 0;
   out_8817991526926240656[75] = 0;
   out_8817991526926240656[76] = 1;
   out_8817991526926240656[77] = 0;
   out_8817991526926240656[78] = 0;
   out_8817991526926240656[79] = 0;
   out_8817991526926240656[80] = 0;
   out_8817991526926240656[81] = 0;
   out_8817991526926240656[82] = 0;
   out_8817991526926240656[83] = 0;
   out_8817991526926240656[84] = 0;
   out_8817991526926240656[85] = dt;
   out_8817991526926240656[86] = 0;
   out_8817991526926240656[87] = 0;
   out_8817991526926240656[88] = 0;
   out_8817991526926240656[89] = 0;
   out_8817991526926240656[90] = 0;
   out_8817991526926240656[91] = 0;
   out_8817991526926240656[92] = 0;
   out_8817991526926240656[93] = 0;
   out_8817991526926240656[94] = 0;
   out_8817991526926240656[95] = 1;
   out_8817991526926240656[96] = 0;
   out_8817991526926240656[97] = 0;
   out_8817991526926240656[98] = 0;
   out_8817991526926240656[99] = 0;
   out_8817991526926240656[100] = 0;
   out_8817991526926240656[101] = 0;
   out_8817991526926240656[102] = 0;
   out_8817991526926240656[103] = 0;
   out_8817991526926240656[104] = dt;
   out_8817991526926240656[105] = 0;
   out_8817991526926240656[106] = 0;
   out_8817991526926240656[107] = 0;
   out_8817991526926240656[108] = 0;
   out_8817991526926240656[109] = 0;
   out_8817991526926240656[110] = 0;
   out_8817991526926240656[111] = 0;
   out_8817991526926240656[112] = 0;
   out_8817991526926240656[113] = 0;
   out_8817991526926240656[114] = 1;
   out_8817991526926240656[115] = 0;
   out_8817991526926240656[116] = 0;
   out_8817991526926240656[117] = 0;
   out_8817991526926240656[118] = 0;
   out_8817991526926240656[119] = 0;
   out_8817991526926240656[120] = 0;
   out_8817991526926240656[121] = 0;
   out_8817991526926240656[122] = 0;
   out_8817991526926240656[123] = 0;
   out_8817991526926240656[124] = 0;
   out_8817991526926240656[125] = 0;
   out_8817991526926240656[126] = 0;
   out_8817991526926240656[127] = 0;
   out_8817991526926240656[128] = 0;
   out_8817991526926240656[129] = 0;
   out_8817991526926240656[130] = 0;
   out_8817991526926240656[131] = 0;
   out_8817991526926240656[132] = 0;
   out_8817991526926240656[133] = 1;
   out_8817991526926240656[134] = 0;
   out_8817991526926240656[135] = 0;
   out_8817991526926240656[136] = 0;
   out_8817991526926240656[137] = 0;
   out_8817991526926240656[138] = 0;
   out_8817991526926240656[139] = 0;
   out_8817991526926240656[140] = 0;
   out_8817991526926240656[141] = 0;
   out_8817991526926240656[142] = 0;
   out_8817991526926240656[143] = 0;
   out_8817991526926240656[144] = 0;
   out_8817991526926240656[145] = 0;
   out_8817991526926240656[146] = 0;
   out_8817991526926240656[147] = 0;
   out_8817991526926240656[148] = 0;
   out_8817991526926240656[149] = 0;
   out_8817991526926240656[150] = 0;
   out_8817991526926240656[151] = 0;
   out_8817991526926240656[152] = 1;
   out_8817991526926240656[153] = 0;
   out_8817991526926240656[154] = 0;
   out_8817991526926240656[155] = 0;
   out_8817991526926240656[156] = 0;
   out_8817991526926240656[157] = 0;
   out_8817991526926240656[158] = 0;
   out_8817991526926240656[159] = 0;
   out_8817991526926240656[160] = 0;
   out_8817991526926240656[161] = 0;
   out_8817991526926240656[162] = 0;
   out_8817991526926240656[163] = 0;
   out_8817991526926240656[164] = 0;
   out_8817991526926240656[165] = 0;
   out_8817991526926240656[166] = 0;
   out_8817991526926240656[167] = 0;
   out_8817991526926240656[168] = 0;
   out_8817991526926240656[169] = 0;
   out_8817991526926240656[170] = 0;
   out_8817991526926240656[171] = 1;
   out_8817991526926240656[172] = 0;
   out_8817991526926240656[173] = 0;
   out_8817991526926240656[174] = 0;
   out_8817991526926240656[175] = 0;
   out_8817991526926240656[176] = 0;
   out_8817991526926240656[177] = 0;
   out_8817991526926240656[178] = 0;
   out_8817991526926240656[179] = 0;
   out_8817991526926240656[180] = 0;
   out_8817991526926240656[181] = 0;
   out_8817991526926240656[182] = 0;
   out_8817991526926240656[183] = 0;
   out_8817991526926240656[184] = 0;
   out_8817991526926240656[185] = 0;
   out_8817991526926240656[186] = 0;
   out_8817991526926240656[187] = 0;
   out_8817991526926240656[188] = 0;
   out_8817991526926240656[189] = 0;
   out_8817991526926240656[190] = 1;
   out_8817991526926240656[191] = 0;
   out_8817991526926240656[192] = 0;
   out_8817991526926240656[193] = 0;
   out_8817991526926240656[194] = 0;
   out_8817991526926240656[195] = 0;
   out_8817991526926240656[196] = 0;
   out_8817991526926240656[197] = 0;
   out_8817991526926240656[198] = 0;
   out_8817991526926240656[199] = 0;
   out_8817991526926240656[200] = 0;
   out_8817991526926240656[201] = 0;
   out_8817991526926240656[202] = 0;
   out_8817991526926240656[203] = 0;
   out_8817991526926240656[204] = 0;
   out_8817991526926240656[205] = 0;
   out_8817991526926240656[206] = 0;
   out_8817991526926240656[207] = 0;
   out_8817991526926240656[208] = 0;
   out_8817991526926240656[209] = 1;
   out_8817991526926240656[210] = 0;
   out_8817991526926240656[211] = 0;
   out_8817991526926240656[212] = 0;
   out_8817991526926240656[213] = 0;
   out_8817991526926240656[214] = 0;
   out_8817991526926240656[215] = 0;
   out_8817991526926240656[216] = 0;
   out_8817991526926240656[217] = 0;
   out_8817991526926240656[218] = 0;
   out_8817991526926240656[219] = 0;
   out_8817991526926240656[220] = 0;
   out_8817991526926240656[221] = 0;
   out_8817991526926240656[222] = 0;
   out_8817991526926240656[223] = 0;
   out_8817991526926240656[224] = 0;
   out_8817991526926240656[225] = 0;
   out_8817991526926240656[226] = 0;
   out_8817991526926240656[227] = 0;
   out_8817991526926240656[228] = 1;
   out_8817991526926240656[229] = 0;
   out_8817991526926240656[230] = 0;
   out_8817991526926240656[231] = 0;
   out_8817991526926240656[232] = 0;
   out_8817991526926240656[233] = 0;
   out_8817991526926240656[234] = 0;
   out_8817991526926240656[235] = 0;
   out_8817991526926240656[236] = 0;
   out_8817991526926240656[237] = 0;
   out_8817991526926240656[238] = 0;
   out_8817991526926240656[239] = 0;
   out_8817991526926240656[240] = 0;
   out_8817991526926240656[241] = 0;
   out_8817991526926240656[242] = 0;
   out_8817991526926240656[243] = 0;
   out_8817991526926240656[244] = 0;
   out_8817991526926240656[245] = 0;
   out_8817991526926240656[246] = 0;
   out_8817991526926240656[247] = 1;
   out_8817991526926240656[248] = 0;
   out_8817991526926240656[249] = 0;
   out_8817991526926240656[250] = 0;
   out_8817991526926240656[251] = 0;
   out_8817991526926240656[252] = 0;
   out_8817991526926240656[253] = 0;
   out_8817991526926240656[254] = 0;
   out_8817991526926240656[255] = 0;
   out_8817991526926240656[256] = 0;
   out_8817991526926240656[257] = 0;
   out_8817991526926240656[258] = 0;
   out_8817991526926240656[259] = 0;
   out_8817991526926240656[260] = 0;
   out_8817991526926240656[261] = 0;
   out_8817991526926240656[262] = 0;
   out_8817991526926240656[263] = 0;
   out_8817991526926240656[264] = 0;
   out_8817991526926240656[265] = 0;
   out_8817991526926240656[266] = 1;
   out_8817991526926240656[267] = 0;
   out_8817991526926240656[268] = 0;
   out_8817991526926240656[269] = 0;
   out_8817991526926240656[270] = 0;
   out_8817991526926240656[271] = 0;
   out_8817991526926240656[272] = 0;
   out_8817991526926240656[273] = 0;
   out_8817991526926240656[274] = 0;
   out_8817991526926240656[275] = 0;
   out_8817991526926240656[276] = 0;
   out_8817991526926240656[277] = 0;
   out_8817991526926240656[278] = 0;
   out_8817991526926240656[279] = 0;
   out_8817991526926240656[280] = 0;
   out_8817991526926240656[281] = 0;
   out_8817991526926240656[282] = 0;
   out_8817991526926240656[283] = 0;
   out_8817991526926240656[284] = 0;
   out_8817991526926240656[285] = 1;
   out_8817991526926240656[286] = 0;
   out_8817991526926240656[287] = 0;
   out_8817991526926240656[288] = 0;
   out_8817991526926240656[289] = 0;
   out_8817991526926240656[290] = 0;
   out_8817991526926240656[291] = 0;
   out_8817991526926240656[292] = 0;
   out_8817991526926240656[293] = 0;
   out_8817991526926240656[294] = 0;
   out_8817991526926240656[295] = 0;
   out_8817991526926240656[296] = 0;
   out_8817991526926240656[297] = 0;
   out_8817991526926240656[298] = 0;
   out_8817991526926240656[299] = 0;
   out_8817991526926240656[300] = 0;
   out_8817991526926240656[301] = 0;
   out_8817991526926240656[302] = 0;
   out_8817991526926240656[303] = 0;
   out_8817991526926240656[304] = 1;
   out_8817991526926240656[305] = 0;
   out_8817991526926240656[306] = 0;
   out_8817991526926240656[307] = 0;
   out_8817991526926240656[308] = 0;
   out_8817991526926240656[309] = 0;
   out_8817991526926240656[310] = 0;
   out_8817991526926240656[311] = 0;
   out_8817991526926240656[312] = 0;
   out_8817991526926240656[313] = 0;
   out_8817991526926240656[314] = 0;
   out_8817991526926240656[315] = 0;
   out_8817991526926240656[316] = 0;
   out_8817991526926240656[317] = 0;
   out_8817991526926240656[318] = 0;
   out_8817991526926240656[319] = 0;
   out_8817991526926240656[320] = 0;
   out_8817991526926240656[321] = 0;
   out_8817991526926240656[322] = 0;
   out_8817991526926240656[323] = 1;
}
void h_4(double *state, double *unused, double *out_7394028133800952799) {
   out_7394028133800952799[0] = state[6] + state[9];
   out_7394028133800952799[1] = state[7] + state[10];
   out_7394028133800952799[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6283474072273667006) {
   out_6283474072273667006[0] = 0;
   out_6283474072273667006[1] = 0;
   out_6283474072273667006[2] = 0;
   out_6283474072273667006[3] = 0;
   out_6283474072273667006[4] = 0;
   out_6283474072273667006[5] = 0;
   out_6283474072273667006[6] = 1;
   out_6283474072273667006[7] = 0;
   out_6283474072273667006[8] = 0;
   out_6283474072273667006[9] = 1;
   out_6283474072273667006[10] = 0;
   out_6283474072273667006[11] = 0;
   out_6283474072273667006[12] = 0;
   out_6283474072273667006[13] = 0;
   out_6283474072273667006[14] = 0;
   out_6283474072273667006[15] = 0;
   out_6283474072273667006[16] = 0;
   out_6283474072273667006[17] = 0;
   out_6283474072273667006[18] = 0;
   out_6283474072273667006[19] = 0;
   out_6283474072273667006[20] = 0;
   out_6283474072273667006[21] = 0;
   out_6283474072273667006[22] = 0;
   out_6283474072273667006[23] = 0;
   out_6283474072273667006[24] = 0;
   out_6283474072273667006[25] = 1;
   out_6283474072273667006[26] = 0;
   out_6283474072273667006[27] = 0;
   out_6283474072273667006[28] = 1;
   out_6283474072273667006[29] = 0;
   out_6283474072273667006[30] = 0;
   out_6283474072273667006[31] = 0;
   out_6283474072273667006[32] = 0;
   out_6283474072273667006[33] = 0;
   out_6283474072273667006[34] = 0;
   out_6283474072273667006[35] = 0;
   out_6283474072273667006[36] = 0;
   out_6283474072273667006[37] = 0;
   out_6283474072273667006[38] = 0;
   out_6283474072273667006[39] = 0;
   out_6283474072273667006[40] = 0;
   out_6283474072273667006[41] = 0;
   out_6283474072273667006[42] = 0;
   out_6283474072273667006[43] = 0;
   out_6283474072273667006[44] = 1;
   out_6283474072273667006[45] = 0;
   out_6283474072273667006[46] = 0;
   out_6283474072273667006[47] = 1;
   out_6283474072273667006[48] = 0;
   out_6283474072273667006[49] = 0;
   out_6283474072273667006[50] = 0;
   out_6283474072273667006[51] = 0;
   out_6283474072273667006[52] = 0;
   out_6283474072273667006[53] = 0;
}
void h_10(double *state, double *unused, double *out_1632777674839787006) {
   out_1632777674839787006[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1632777674839787006[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1632777674839787006[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_761013637887660448) {
   out_761013637887660448[0] = 0;
   out_761013637887660448[1] = 9.8100000000000005*cos(state[1]);
   out_761013637887660448[2] = 0;
   out_761013637887660448[3] = 0;
   out_761013637887660448[4] = -state[8];
   out_761013637887660448[5] = state[7];
   out_761013637887660448[6] = 0;
   out_761013637887660448[7] = state[5];
   out_761013637887660448[8] = -state[4];
   out_761013637887660448[9] = 0;
   out_761013637887660448[10] = 0;
   out_761013637887660448[11] = 0;
   out_761013637887660448[12] = 1;
   out_761013637887660448[13] = 0;
   out_761013637887660448[14] = 0;
   out_761013637887660448[15] = 1;
   out_761013637887660448[16] = 0;
   out_761013637887660448[17] = 0;
   out_761013637887660448[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_761013637887660448[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_761013637887660448[20] = 0;
   out_761013637887660448[21] = state[8];
   out_761013637887660448[22] = 0;
   out_761013637887660448[23] = -state[6];
   out_761013637887660448[24] = -state[5];
   out_761013637887660448[25] = 0;
   out_761013637887660448[26] = state[3];
   out_761013637887660448[27] = 0;
   out_761013637887660448[28] = 0;
   out_761013637887660448[29] = 0;
   out_761013637887660448[30] = 0;
   out_761013637887660448[31] = 1;
   out_761013637887660448[32] = 0;
   out_761013637887660448[33] = 0;
   out_761013637887660448[34] = 1;
   out_761013637887660448[35] = 0;
   out_761013637887660448[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_761013637887660448[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_761013637887660448[38] = 0;
   out_761013637887660448[39] = -state[7];
   out_761013637887660448[40] = state[6];
   out_761013637887660448[41] = 0;
   out_761013637887660448[42] = state[4];
   out_761013637887660448[43] = -state[3];
   out_761013637887660448[44] = 0;
   out_761013637887660448[45] = 0;
   out_761013637887660448[46] = 0;
   out_761013637887660448[47] = 0;
   out_761013637887660448[48] = 0;
   out_761013637887660448[49] = 0;
   out_761013637887660448[50] = 1;
   out_761013637887660448[51] = 0;
   out_761013637887660448[52] = 0;
   out_761013637887660448[53] = 1;
}
void h_13(double *state, double *unused, double *out_4603793361074312483) {
   out_4603793361074312483[0] = state[3];
   out_4603793361074312483[1] = state[4];
   out_4603793361074312483[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8950996176103551809) {
   out_8950996176103551809[0] = 0;
   out_8950996176103551809[1] = 0;
   out_8950996176103551809[2] = 0;
   out_8950996176103551809[3] = 1;
   out_8950996176103551809[4] = 0;
   out_8950996176103551809[5] = 0;
   out_8950996176103551809[6] = 0;
   out_8950996176103551809[7] = 0;
   out_8950996176103551809[8] = 0;
   out_8950996176103551809[9] = 0;
   out_8950996176103551809[10] = 0;
   out_8950996176103551809[11] = 0;
   out_8950996176103551809[12] = 0;
   out_8950996176103551809[13] = 0;
   out_8950996176103551809[14] = 0;
   out_8950996176103551809[15] = 0;
   out_8950996176103551809[16] = 0;
   out_8950996176103551809[17] = 0;
   out_8950996176103551809[18] = 0;
   out_8950996176103551809[19] = 0;
   out_8950996176103551809[20] = 0;
   out_8950996176103551809[21] = 0;
   out_8950996176103551809[22] = 1;
   out_8950996176103551809[23] = 0;
   out_8950996176103551809[24] = 0;
   out_8950996176103551809[25] = 0;
   out_8950996176103551809[26] = 0;
   out_8950996176103551809[27] = 0;
   out_8950996176103551809[28] = 0;
   out_8950996176103551809[29] = 0;
   out_8950996176103551809[30] = 0;
   out_8950996176103551809[31] = 0;
   out_8950996176103551809[32] = 0;
   out_8950996176103551809[33] = 0;
   out_8950996176103551809[34] = 0;
   out_8950996176103551809[35] = 0;
   out_8950996176103551809[36] = 0;
   out_8950996176103551809[37] = 0;
   out_8950996176103551809[38] = 0;
   out_8950996176103551809[39] = 0;
   out_8950996176103551809[40] = 0;
   out_8950996176103551809[41] = 1;
   out_8950996176103551809[42] = 0;
   out_8950996176103551809[43] = 0;
   out_8950996176103551809[44] = 0;
   out_8950996176103551809[45] = 0;
   out_8950996176103551809[46] = 0;
   out_8950996176103551809[47] = 0;
   out_8950996176103551809[48] = 0;
   out_8950996176103551809[49] = 0;
   out_8950996176103551809[50] = 0;
   out_8950996176103551809[51] = 0;
   out_8950996176103551809[52] = 0;
   out_8950996176103551809[53] = 0;
}
void h_14(double *state, double *unused, double *out_5241449068668224266) {
   out_5241449068668224266[0] = state[6];
   out_5241449068668224266[1] = state[7];
   out_5241449068668224266[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3200685639978294710) {
   out_3200685639978294710[0] = 0;
   out_3200685639978294710[1] = 0;
   out_3200685639978294710[2] = 0;
   out_3200685639978294710[3] = 0;
   out_3200685639978294710[4] = 0;
   out_3200685639978294710[5] = 0;
   out_3200685639978294710[6] = 1;
   out_3200685639978294710[7] = 0;
   out_3200685639978294710[8] = 0;
   out_3200685639978294710[9] = 0;
   out_3200685639978294710[10] = 0;
   out_3200685639978294710[11] = 0;
   out_3200685639978294710[12] = 0;
   out_3200685639978294710[13] = 0;
   out_3200685639978294710[14] = 0;
   out_3200685639978294710[15] = 0;
   out_3200685639978294710[16] = 0;
   out_3200685639978294710[17] = 0;
   out_3200685639978294710[18] = 0;
   out_3200685639978294710[19] = 0;
   out_3200685639978294710[20] = 0;
   out_3200685639978294710[21] = 0;
   out_3200685639978294710[22] = 0;
   out_3200685639978294710[23] = 0;
   out_3200685639978294710[24] = 0;
   out_3200685639978294710[25] = 1;
   out_3200685639978294710[26] = 0;
   out_3200685639978294710[27] = 0;
   out_3200685639978294710[28] = 0;
   out_3200685639978294710[29] = 0;
   out_3200685639978294710[30] = 0;
   out_3200685639978294710[31] = 0;
   out_3200685639978294710[32] = 0;
   out_3200685639978294710[33] = 0;
   out_3200685639978294710[34] = 0;
   out_3200685639978294710[35] = 0;
   out_3200685639978294710[36] = 0;
   out_3200685639978294710[37] = 0;
   out_3200685639978294710[38] = 0;
   out_3200685639978294710[39] = 0;
   out_3200685639978294710[40] = 0;
   out_3200685639978294710[41] = 0;
   out_3200685639978294710[42] = 0;
   out_3200685639978294710[43] = 0;
   out_3200685639978294710[44] = 1;
   out_3200685639978294710[45] = 0;
   out_3200685639978294710[46] = 0;
   out_3200685639978294710[47] = 0;
   out_3200685639978294710[48] = 0;
   out_3200685639978294710[49] = 0;
   out_3200685639978294710[50] = 0;
   out_3200685639978294710[51] = 0;
   out_3200685639978294710[52] = 0;
   out_3200685639978294710[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1773490464841058211) {
  err_fun(nom_x, delta_x, out_1773490464841058211);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3370820179269337821) {
  inv_err_fun(nom_x, true_x, out_3370820179269337821);
}
void pose_H_mod_fun(double *state, double *out_8103172798179963867) {
  H_mod_fun(state, out_8103172798179963867);
}
void pose_f_fun(double *state, double dt, double *out_4130745264458481066) {
  f_fun(state,  dt, out_4130745264458481066);
}
void pose_F_fun(double *state, double dt, double *out_8817991526926240656) {
  F_fun(state,  dt, out_8817991526926240656);
}
void pose_h_4(double *state, double *unused, double *out_7394028133800952799) {
  h_4(state, unused, out_7394028133800952799);
}
void pose_H_4(double *state, double *unused, double *out_6283474072273667006) {
  H_4(state, unused, out_6283474072273667006);
}
void pose_h_10(double *state, double *unused, double *out_1632777674839787006) {
  h_10(state, unused, out_1632777674839787006);
}
void pose_H_10(double *state, double *unused, double *out_761013637887660448) {
  H_10(state, unused, out_761013637887660448);
}
void pose_h_13(double *state, double *unused, double *out_4603793361074312483) {
  h_13(state, unused, out_4603793361074312483);
}
void pose_H_13(double *state, double *unused, double *out_8950996176103551809) {
  H_13(state, unused, out_8950996176103551809);
}
void pose_h_14(double *state, double *unused, double *out_5241449068668224266) {
  h_14(state, unused, out_5241449068668224266);
}
void pose_H_14(double *state, double *unused, double *out_3200685639978294710) {
  H_14(state, unused, out_3200685639978294710);
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
