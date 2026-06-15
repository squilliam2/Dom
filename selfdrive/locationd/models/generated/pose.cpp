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
void err_fun(double *nom_x, double *delta_x, double *out_6990659364596708462) {
   out_6990659364596708462[0] = delta_x[0] + nom_x[0];
   out_6990659364596708462[1] = delta_x[1] + nom_x[1];
   out_6990659364596708462[2] = delta_x[2] + nom_x[2];
   out_6990659364596708462[3] = delta_x[3] + nom_x[3];
   out_6990659364596708462[4] = delta_x[4] + nom_x[4];
   out_6990659364596708462[5] = delta_x[5] + nom_x[5];
   out_6990659364596708462[6] = delta_x[6] + nom_x[6];
   out_6990659364596708462[7] = delta_x[7] + nom_x[7];
   out_6990659364596708462[8] = delta_x[8] + nom_x[8];
   out_6990659364596708462[9] = delta_x[9] + nom_x[9];
   out_6990659364596708462[10] = delta_x[10] + nom_x[10];
   out_6990659364596708462[11] = delta_x[11] + nom_x[11];
   out_6990659364596708462[12] = delta_x[12] + nom_x[12];
   out_6990659364596708462[13] = delta_x[13] + nom_x[13];
   out_6990659364596708462[14] = delta_x[14] + nom_x[14];
   out_6990659364596708462[15] = delta_x[15] + nom_x[15];
   out_6990659364596708462[16] = delta_x[16] + nom_x[16];
   out_6990659364596708462[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1561026677999837058) {
   out_1561026677999837058[0] = -nom_x[0] + true_x[0];
   out_1561026677999837058[1] = -nom_x[1] + true_x[1];
   out_1561026677999837058[2] = -nom_x[2] + true_x[2];
   out_1561026677999837058[3] = -nom_x[3] + true_x[3];
   out_1561026677999837058[4] = -nom_x[4] + true_x[4];
   out_1561026677999837058[5] = -nom_x[5] + true_x[5];
   out_1561026677999837058[6] = -nom_x[6] + true_x[6];
   out_1561026677999837058[7] = -nom_x[7] + true_x[7];
   out_1561026677999837058[8] = -nom_x[8] + true_x[8];
   out_1561026677999837058[9] = -nom_x[9] + true_x[9];
   out_1561026677999837058[10] = -nom_x[10] + true_x[10];
   out_1561026677999837058[11] = -nom_x[11] + true_x[11];
   out_1561026677999837058[12] = -nom_x[12] + true_x[12];
   out_1561026677999837058[13] = -nom_x[13] + true_x[13];
   out_1561026677999837058[14] = -nom_x[14] + true_x[14];
   out_1561026677999837058[15] = -nom_x[15] + true_x[15];
   out_1561026677999837058[16] = -nom_x[16] + true_x[16];
   out_1561026677999837058[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_308647198819961252) {
   out_308647198819961252[0] = 1.0;
   out_308647198819961252[1] = 0.0;
   out_308647198819961252[2] = 0.0;
   out_308647198819961252[3] = 0.0;
   out_308647198819961252[4] = 0.0;
   out_308647198819961252[5] = 0.0;
   out_308647198819961252[6] = 0.0;
   out_308647198819961252[7] = 0.0;
   out_308647198819961252[8] = 0.0;
   out_308647198819961252[9] = 0.0;
   out_308647198819961252[10] = 0.0;
   out_308647198819961252[11] = 0.0;
   out_308647198819961252[12] = 0.0;
   out_308647198819961252[13] = 0.0;
   out_308647198819961252[14] = 0.0;
   out_308647198819961252[15] = 0.0;
   out_308647198819961252[16] = 0.0;
   out_308647198819961252[17] = 0.0;
   out_308647198819961252[18] = 0.0;
   out_308647198819961252[19] = 1.0;
   out_308647198819961252[20] = 0.0;
   out_308647198819961252[21] = 0.0;
   out_308647198819961252[22] = 0.0;
   out_308647198819961252[23] = 0.0;
   out_308647198819961252[24] = 0.0;
   out_308647198819961252[25] = 0.0;
   out_308647198819961252[26] = 0.0;
   out_308647198819961252[27] = 0.0;
   out_308647198819961252[28] = 0.0;
   out_308647198819961252[29] = 0.0;
   out_308647198819961252[30] = 0.0;
   out_308647198819961252[31] = 0.0;
   out_308647198819961252[32] = 0.0;
   out_308647198819961252[33] = 0.0;
   out_308647198819961252[34] = 0.0;
   out_308647198819961252[35] = 0.0;
   out_308647198819961252[36] = 0.0;
   out_308647198819961252[37] = 0.0;
   out_308647198819961252[38] = 1.0;
   out_308647198819961252[39] = 0.0;
   out_308647198819961252[40] = 0.0;
   out_308647198819961252[41] = 0.0;
   out_308647198819961252[42] = 0.0;
   out_308647198819961252[43] = 0.0;
   out_308647198819961252[44] = 0.0;
   out_308647198819961252[45] = 0.0;
   out_308647198819961252[46] = 0.0;
   out_308647198819961252[47] = 0.0;
   out_308647198819961252[48] = 0.0;
   out_308647198819961252[49] = 0.0;
   out_308647198819961252[50] = 0.0;
   out_308647198819961252[51] = 0.0;
   out_308647198819961252[52] = 0.0;
   out_308647198819961252[53] = 0.0;
   out_308647198819961252[54] = 0.0;
   out_308647198819961252[55] = 0.0;
   out_308647198819961252[56] = 0.0;
   out_308647198819961252[57] = 1.0;
   out_308647198819961252[58] = 0.0;
   out_308647198819961252[59] = 0.0;
   out_308647198819961252[60] = 0.0;
   out_308647198819961252[61] = 0.0;
   out_308647198819961252[62] = 0.0;
   out_308647198819961252[63] = 0.0;
   out_308647198819961252[64] = 0.0;
   out_308647198819961252[65] = 0.0;
   out_308647198819961252[66] = 0.0;
   out_308647198819961252[67] = 0.0;
   out_308647198819961252[68] = 0.0;
   out_308647198819961252[69] = 0.0;
   out_308647198819961252[70] = 0.0;
   out_308647198819961252[71] = 0.0;
   out_308647198819961252[72] = 0.0;
   out_308647198819961252[73] = 0.0;
   out_308647198819961252[74] = 0.0;
   out_308647198819961252[75] = 0.0;
   out_308647198819961252[76] = 1.0;
   out_308647198819961252[77] = 0.0;
   out_308647198819961252[78] = 0.0;
   out_308647198819961252[79] = 0.0;
   out_308647198819961252[80] = 0.0;
   out_308647198819961252[81] = 0.0;
   out_308647198819961252[82] = 0.0;
   out_308647198819961252[83] = 0.0;
   out_308647198819961252[84] = 0.0;
   out_308647198819961252[85] = 0.0;
   out_308647198819961252[86] = 0.0;
   out_308647198819961252[87] = 0.0;
   out_308647198819961252[88] = 0.0;
   out_308647198819961252[89] = 0.0;
   out_308647198819961252[90] = 0.0;
   out_308647198819961252[91] = 0.0;
   out_308647198819961252[92] = 0.0;
   out_308647198819961252[93] = 0.0;
   out_308647198819961252[94] = 0.0;
   out_308647198819961252[95] = 1.0;
   out_308647198819961252[96] = 0.0;
   out_308647198819961252[97] = 0.0;
   out_308647198819961252[98] = 0.0;
   out_308647198819961252[99] = 0.0;
   out_308647198819961252[100] = 0.0;
   out_308647198819961252[101] = 0.0;
   out_308647198819961252[102] = 0.0;
   out_308647198819961252[103] = 0.0;
   out_308647198819961252[104] = 0.0;
   out_308647198819961252[105] = 0.0;
   out_308647198819961252[106] = 0.0;
   out_308647198819961252[107] = 0.0;
   out_308647198819961252[108] = 0.0;
   out_308647198819961252[109] = 0.0;
   out_308647198819961252[110] = 0.0;
   out_308647198819961252[111] = 0.0;
   out_308647198819961252[112] = 0.0;
   out_308647198819961252[113] = 0.0;
   out_308647198819961252[114] = 1.0;
   out_308647198819961252[115] = 0.0;
   out_308647198819961252[116] = 0.0;
   out_308647198819961252[117] = 0.0;
   out_308647198819961252[118] = 0.0;
   out_308647198819961252[119] = 0.0;
   out_308647198819961252[120] = 0.0;
   out_308647198819961252[121] = 0.0;
   out_308647198819961252[122] = 0.0;
   out_308647198819961252[123] = 0.0;
   out_308647198819961252[124] = 0.0;
   out_308647198819961252[125] = 0.0;
   out_308647198819961252[126] = 0.0;
   out_308647198819961252[127] = 0.0;
   out_308647198819961252[128] = 0.0;
   out_308647198819961252[129] = 0.0;
   out_308647198819961252[130] = 0.0;
   out_308647198819961252[131] = 0.0;
   out_308647198819961252[132] = 0.0;
   out_308647198819961252[133] = 1.0;
   out_308647198819961252[134] = 0.0;
   out_308647198819961252[135] = 0.0;
   out_308647198819961252[136] = 0.0;
   out_308647198819961252[137] = 0.0;
   out_308647198819961252[138] = 0.0;
   out_308647198819961252[139] = 0.0;
   out_308647198819961252[140] = 0.0;
   out_308647198819961252[141] = 0.0;
   out_308647198819961252[142] = 0.0;
   out_308647198819961252[143] = 0.0;
   out_308647198819961252[144] = 0.0;
   out_308647198819961252[145] = 0.0;
   out_308647198819961252[146] = 0.0;
   out_308647198819961252[147] = 0.0;
   out_308647198819961252[148] = 0.0;
   out_308647198819961252[149] = 0.0;
   out_308647198819961252[150] = 0.0;
   out_308647198819961252[151] = 0.0;
   out_308647198819961252[152] = 1.0;
   out_308647198819961252[153] = 0.0;
   out_308647198819961252[154] = 0.0;
   out_308647198819961252[155] = 0.0;
   out_308647198819961252[156] = 0.0;
   out_308647198819961252[157] = 0.0;
   out_308647198819961252[158] = 0.0;
   out_308647198819961252[159] = 0.0;
   out_308647198819961252[160] = 0.0;
   out_308647198819961252[161] = 0.0;
   out_308647198819961252[162] = 0.0;
   out_308647198819961252[163] = 0.0;
   out_308647198819961252[164] = 0.0;
   out_308647198819961252[165] = 0.0;
   out_308647198819961252[166] = 0.0;
   out_308647198819961252[167] = 0.0;
   out_308647198819961252[168] = 0.0;
   out_308647198819961252[169] = 0.0;
   out_308647198819961252[170] = 0.0;
   out_308647198819961252[171] = 1.0;
   out_308647198819961252[172] = 0.0;
   out_308647198819961252[173] = 0.0;
   out_308647198819961252[174] = 0.0;
   out_308647198819961252[175] = 0.0;
   out_308647198819961252[176] = 0.0;
   out_308647198819961252[177] = 0.0;
   out_308647198819961252[178] = 0.0;
   out_308647198819961252[179] = 0.0;
   out_308647198819961252[180] = 0.0;
   out_308647198819961252[181] = 0.0;
   out_308647198819961252[182] = 0.0;
   out_308647198819961252[183] = 0.0;
   out_308647198819961252[184] = 0.0;
   out_308647198819961252[185] = 0.0;
   out_308647198819961252[186] = 0.0;
   out_308647198819961252[187] = 0.0;
   out_308647198819961252[188] = 0.0;
   out_308647198819961252[189] = 0.0;
   out_308647198819961252[190] = 1.0;
   out_308647198819961252[191] = 0.0;
   out_308647198819961252[192] = 0.0;
   out_308647198819961252[193] = 0.0;
   out_308647198819961252[194] = 0.0;
   out_308647198819961252[195] = 0.0;
   out_308647198819961252[196] = 0.0;
   out_308647198819961252[197] = 0.0;
   out_308647198819961252[198] = 0.0;
   out_308647198819961252[199] = 0.0;
   out_308647198819961252[200] = 0.0;
   out_308647198819961252[201] = 0.0;
   out_308647198819961252[202] = 0.0;
   out_308647198819961252[203] = 0.0;
   out_308647198819961252[204] = 0.0;
   out_308647198819961252[205] = 0.0;
   out_308647198819961252[206] = 0.0;
   out_308647198819961252[207] = 0.0;
   out_308647198819961252[208] = 0.0;
   out_308647198819961252[209] = 1.0;
   out_308647198819961252[210] = 0.0;
   out_308647198819961252[211] = 0.0;
   out_308647198819961252[212] = 0.0;
   out_308647198819961252[213] = 0.0;
   out_308647198819961252[214] = 0.0;
   out_308647198819961252[215] = 0.0;
   out_308647198819961252[216] = 0.0;
   out_308647198819961252[217] = 0.0;
   out_308647198819961252[218] = 0.0;
   out_308647198819961252[219] = 0.0;
   out_308647198819961252[220] = 0.0;
   out_308647198819961252[221] = 0.0;
   out_308647198819961252[222] = 0.0;
   out_308647198819961252[223] = 0.0;
   out_308647198819961252[224] = 0.0;
   out_308647198819961252[225] = 0.0;
   out_308647198819961252[226] = 0.0;
   out_308647198819961252[227] = 0.0;
   out_308647198819961252[228] = 1.0;
   out_308647198819961252[229] = 0.0;
   out_308647198819961252[230] = 0.0;
   out_308647198819961252[231] = 0.0;
   out_308647198819961252[232] = 0.0;
   out_308647198819961252[233] = 0.0;
   out_308647198819961252[234] = 0.0;
   out_308647198819961252[235] = 0.0;
   out_308647198819961252[236] = 0.0;
   out_308647198819961252[237] = 0.0;
   out_308647198819961252[238] = 0.0;
   out_308647198819961252[239] = 0.0;
   out_308647198819961252[240] = 0.0;
   out_308647198819961252[241] = 0.0;
   out_308647198819961252[242] = 0.0;
   out_308647198819961252[243] = 0.0;
   out_308647198819961252[244] = 0.0;
   out_308647198819961252[245] = 0.0;
   out_308647198819961252[246] = 0.0;
   out_308647198819961252[247] = 1.0;
   out_308647198819961252[248] = 0.0;
   out_308647198819961252[249] = 0.0;
   out_308647198819961252[250] = 0.0;
   out_308647198819961252[251] = 0.0;
   out_308647198819961252[252] = 0.0;
   out_308647198819961252[253] = 0.0;
   out_308647198819961252[254] = 0.0;
   out_308647198819961252[255] = 0.0;
   out_308647198819961252[256] = 0.0;
   out_308647198819961252[257] = 0.0;
   out_308647198819961252[258] = 0.0;
   out_308647198819961252[259] = 0.0;
   out_308647198819961252[260] = 0.0;
   out_308647198819961252[261] = 0.0;
   out_308647198819961252[262] = 0.0;
   out_308647198819961252[263] = 0.0;
   out_308647198819961252[264] = 0.0;
   out_308647198819961252[265] = 0.0;
   out_308647198819961252[266] = 1.0;
   out_308647198819961252[267] = 0.0;
   out_308647198819961252[268] = 0.0;
   out_308647198819961252[269] = 0.0;
   out_308647198819961252[270] = 0.0;
   out_308647198819961252[271] = 0.0;
   out_308647198819961252[272] = 0.0;
   out_308647198819961252[273] = 0.0;
   out_308647198819961252[274] = 0.0;
   out_308647198819961252[275] = 0.0;
   out_308647198819961252[276] = 0.0;
   out_308647198819961252[277] = 0.0;
   out_308647198819961252[278] = 0.0;
   out_308647198819961252[279] = 0.0;
   out_308647198819961252[280] = 0.0;
   out_308647198819961252[281] = 0.0;
   out_308647198819961252[282] = 0.0;
   out_308647198819961252[283] = 0.0;
   out_308647198819961252[284] = 0.0;
   out_308647198819961252[285] = 1.0;
   out_308647198819961252[286] = 0.0;
   out_308647198819961252[287] = 0.0;
   out_308647198819961252[288] = 0.0;
   out_308647198819961252[289] = 0.0;
   out_308647198819961252[290] = 0.0;
   out_308647198819961252[291] = 0.0;
   out_308647198819961252[292] = 0.0;
   out_308647198819961252[293] = 0.0;
   out_308647198819961252[294] = 0.0;
   out_308647198819961252[295] = 0.0;
   out_308647198819961252[296] = 0.0;
   out_308647198819961252[297] = 0.0;
   out_308647198819961252[298] = 0.0;
   out_308647198819961252[299] = 0.0;
   out_308647198819961252[300] = 0.0;
   out_308647198819961252[301] = 0.0;
   out_308647198819961252[302] = 0.0;
   out_308647198819961252[303] = 0.0;
   out_308647198819961252[304] = 1.0;
   out_308647198819961252[305] = 0.0;
   out_308647198819961252[306] = 0.0;
   out_308647198819961252[307] = 0.0;
   out_308647198819961252[308] = 0.0;
   out_308647198819961252[309] = 0.0;
   out_308647198819961252[310] = 0.0;
   out_308647198819961252[311] = 0.0;
   out_308647198819961252[312] = 0.0;
   out_308647198819961252[313] = 0.0;
   out_308647198819961252[314] = 0.0;
   out_308647198819961252[315] = 0.0;
   out_308647198819961252[316] = 0.0;
   out_308647198819961252[317] = 0.0;
   out_308647198819961252[318] = 0.0;
   out_308647198819961252[319] = 0.0;
   out_308647198819961252[320] = 0.0;
   out_308647198819961252[321] = 0.0;
   out_308647198819961252[322] = 0.0;
   out_308647198819961252[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7010110275742074957) {
   out_7010110275742074957[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7010110275742074957[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7010110275742074957[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7010110275742074957[3] = dt*state[12] + state[3];
   out_7010110275742074957[4] = dt*state[13] + state[4];
   out_7010110275742074957[5] = dt*state[14] + state[5];
   out_7010110275742074957[6] = state[6];
   out_7010110275742074957[7] = state[7];
   out_7010110275742074957[8] = state[8];
   out_7010110275742074957[9] = state[9];
   out_7010110275742074957[10] = state[10];
   out_7010110275742074957[11] = state[11];
   out_7010110275742074957[12] = state[12];
   out_7010110275742074957[13] = state[13];
   out_7010110275742074957[14] = state[14];
   out_7010110275742074957[15] = state[15];
   out_7010110275742074957[16] = state[16];
   out_7010110275742074957[17] = state[17];
}
void F_fun(double *state, double dt, double *out_321710036859700647) {
   out_321710036859700647[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_321710036859700647[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_321710036859700647[2] = 0;
   out_321710036859700647[3] = 0;
   out_321710036859700647[4] = 0;
   out_321710036859700647[5] = 0;
   out_321710036859700647[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_321710036859700647[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_321710036859700647[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_321710036859700647[9] = 0;
   out_321710036859700647[10] = 0;
   out_321710036859700647[11] = 0;
   out_321710036859700647[12] = 0;
   out_321710036859700647[13] = 0;
   out_321710036859700647[14] = 0;
   out_321710036859700647[15] = 0;
   out_321710036859700647[16] = 0;
   out_321710036859700647[17] = 0;
   out_321710036859700647[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_321710036859700647[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_321710036859700647[20] = 0;
   out_321710036859700647[21] = 0;
   out_321710036859700647[22] = 0;
   out_321710036859700647[23] = 0;
   out_321710036859700647[24] = 0;
   out_321710036859700647[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_321710036859700647[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_321710036859700647[27] = 0;
   out_321710036859700647[28] = 0;
   out_321710036859700647[29] = 0;
   out_321710036859700647[30] = 0;
   out_321710036859700647[31] = 0;
   out_321710036859700647[32] = 0;
   out_321710036859700647[33] = 0;
   out_321710036859700647[34] = 0;
   out_321710036859700647[35] = 0;
   out_321710036859700647[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_321710036859700647[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_321710036859700647[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_321710036859700647[39] = 0;
   out_321710036859700647[40] = 0;
   out_321710036859700647[41] = 0;
   out_321710036859700647[42] = 0;
   out_321710036859700647[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_321710036859700647[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_321710036859700647[45] = 0;
   out_321710036859700647[46] = 0;
   out_321710036859700647[47] = 0;
   out_321710036859700647[48] = 0;
   out_321710036859700647[49] = 0;
   out_321710036859700647[50] = 0;
   out_321710036859700647[51] = 0;
   out_321710036859700647[52] = 0;
   out_321710036859700647[53] = 0;
   out_321710036859700647[54] = 0;
   out_321710036859700647[55] = 0;
   out_321710036859700647[56] = 0;
   out_321710036859700647[57] = 1;
   out_321710036859700647[58] = 0;
   out_321710036859700647[59] = 0;
   out_321710036859700647[60] = 0;
   out_321710036859700647[61] = 0;
   out_321710036859700647[62] = 0;
   out_321710036859700647[63] = 0;
   out_321710036859700647[64] = 0;
   out_321710036859700647[65] = 0;
   out_321710036859700647[66] = dt;
   out_321710036859700647[67] = 0;
   out_321710036859700647[68] = 0;
   out_321710036859700647[69] = 0;
   out_321710036859700647[70] = 0;
   out_321710036859700647[71] = 0;
   out_321710036859700647[72] = 0;
   out_321710036859700647[73] = 0;
   out_321710036859700647[74] = 0;
   out_321710036859700647[75] = 0;
   out_321710036859700647[76] = 1;
   out_321710036859700647[77] = 0;
   out_321710036859700647[78] = 0;
   out_321710036859700647[79] = 0;
   out_321710036859700647[80] = 0;
   out_321710036859700647[81] = 0;
   out_321710036859700647[82] = 0;
   out_321710036859700647[83] = 0;
   out_321710036859700647[84] = 0;
   out_321710036859700647[85] = dt;
   out_321710036859700647[86] = 0;
   out_321710036859700647[87] = 0;
   out_321710036859700647[88] = 0;
   out_321710036859700647[89] = 0;
   out_321710036859700647[90] = 0;
   out_321710036859700647[91] = 0;
   out_321710036859700647[92] = 0;
   out_321710036859700647[93] = 0;
   out_321710036859700647[94] = 0;
   out_321710036859700647[95] = 1;
   out_321710036859700647[96] = 0;
   out_321710036859700647[97] = 0;
   out_321710036859700647[98] = 0;
   out_321710036859700647[99] = 0;
   out_321710036859700647[100] = 0;
   out_321710036859700647[101] = 0;
   out_321710036859700647[102] = 0;
   out_321710036859700647[103] = 0;
   out_321710036859700647[104] = dt;
   out_321710036859700647[105] = 0;
   out_321710036859700647[106] = 0;
   out_321710036859700647[107] = 0;
   out_321710036859700647[108] = 0;
   out_321710036859700647[109] = 0;
   out_321710036859700647[110] = 0;
   out_321710036859700647[111] = 0;
   out_321710036859700647[112] = 0;
   out_321710036859700647[113] = 0;
   out_321710036859700647[114] = 1;
   out_321710036859700647[115] = 0;
   out_321710036859700647[116] = 0;
   out_321710036859700647[117] = 0;
   out_321710036859700647[118] = 0;
   out_321710036859700647[119] = 0;
   out_321710036859700647[120] = 0;
   out_321710036859700647[121] = 0;
   out_321710036859700647[122] = 0;
   out_321710036859700647[123] = 0;
   out_321710036859700647[124] = 0;
   out_321710036859700647[125] = 0;
   out_321710036859700647[126] = 0;
   out_321710036859700647[127] = 0;
   out_321710036859700647[128] = 0;
   out_321710036859700647[129] = 0;
   out_321710036859700647[130] = 0;
   out_321710036859700647[131] = 0;
   out_321710036859700647[132] = 0;
   out_321710036859700647[133] = 1;
   out_321710036859700647[134] = 0;
   out_321710036859700647[135] = 0;
   out_321710036859700647[136] = 0;
   out_321710036859700647[137] = 0;
   out_321710036859700647[138] = 0;
   out_321710036859700647[139] = 0;
   out_321710036859700647[140] = 0;
   out_321710036859700647[141] = 0;
   out_321710036859700647[142] = 0;
   out_321710036859700647[143] = 0;
   out_321710036859700647[144] = 0;
   out_321710036859700647[145] = 0;
   out_321710036859700647[146] = 0;
   out_321710036859700647[147] = 0;
   out_321710036859700647[148] = 0;
   out_321710036859700647[149] = 0;
   out_321710036859700647[150] = 0;
   out_321710036859700647[151] = 0;
   out_321710036859700647[152] = 1;
   out_321710036859700647[153] = 0;
   out_321710036859700647[154] = 0;
   out_321710036859700647[155] = 0;
   out_321710036859700647[156] = 0;
   out_321710036859700647[157] = 0;
   out_321710036859700647[158] = 0;
   out_321710036859700647[159] = 0;
   out_321710036859700647[160] = 0;
   out_321710036859700647[161] = 0;
   out_321710036859700647[162] = 0;
   out_321710036859700647[163] = 0;
   out_321710036859700647[164] = 0;
   out_321710036859700647[165] = 0;
   out_321710036859700647[166] = 0;
   out_321710036859700647[167] = 0;
   out_321710036859700647[168] = 0;
   out_321710036859700647[169] = 0;
   out_321710036859700647[170] = 0;
   out_321710036859700647[171] = 1;
   out_321710036859700647[172] = 0;
   out_321710036859700647[173] = 0;
   out_321710036859700647[174] = 0;
   out_321710036859700647[175] = 0;
   out_321710036859700647[176] = 0;
   out_321710036859700647[177] = 0;
   out_321710036859700647[178] = 0;
   out_321710036859700647[179] = 0;
   out_321710036859700647[180] = 0;
   out_321710036859700647[181] = 0;
   out_321710036859700647[182] = 0;
   out_321710036859700647[183] = 0;
   out_321710036859700647[184] = 0;
   out_321710036859700647[185] = 0;
   out_321710036859700647[186] = 0;
   out_321710036859700647[187] = 0;
   out_321710036859700647[188] = 0;
   out_321710036859700647[189] = 0;
   out_321710036859700647[190] = 1;
   out_321710036859700647[191] = 0;
   out_321710036859700647[192] = 0;
   out_321710036859700647[193] = 0;
   out_321710036859700647[194] = 0;
   out_321710036859700647[195] = 0;
   out_321710036859700647[196] = 0;
   out_321710036859700647[197] = 0;
   out_321710036859700647[198] = 0;
   out_321710036859700647[199] = 0;
   out_321710036859700647[200] = 0;
   out_321710036859700647[201] = 0;
   out_321710036859700647[202] = 0;
   out_321710036859700647[203] = 0;
   out_321710036859700647[204] = 0;
   out_321710036859700647[205] = 0;
   out_321710036859700647[206] = 0;
   out_321710036859700647[207] = 0;
   out_321710036859700647[208] = 0;
   out_321710036859700647[209] = 1;
   out_321710036859700647[210] = 0;
   out_321710036859700647[211] = 0;
   out_321710036859700647[212] = 0;
   out_321710036859700647[213] = 0;
   out_321710036859700647[214] = 0;
   out_321710036859700647[215] = 0;
   out_321710036859700647[216] = 0;
   out_321710036859700647[217] = 0;
   out_321710036859700647[218] = 0;
   out_321710036859700647[219] = 0;
   out_321710036859700647[220] = 0;
   out_321710036859700647[221] = 0;
   out_321710036859700647[222] = 0;
   out_321710036859700647[223] = 0;
   out_321710036859700647[224] = 0;
   out_321710036859700647[225] = 0;
   out_321710036859700647[226] = 0;
   out_321710036859700647[227] = 0;
   out_321710036859700647[228] = 1;
   out_321710036859700647[229] = 0;
   out_321710036859700647[230] = 0;
   out_321710036859700647[231] = 0;
   out_321710036859700647[232] = 0;
   out_321710036859700647[233] = 0;
   out_321710036859700647[234] = 0;
   out_321710036859700647[235] = 0;
   out_321710036859700647[236] = 0;
   out_321710036859700647[237] = 0;
   out_321710036859700647[238] = 0;
   out_321710036859700647[239] = 0;
   out_321710036859700647[240] = 0;
   out_321710036859700647[241] = 0;
   out_321710036859700647[242] = 0;
   out_321710036859700647[243] = 0;
   out_321710036859700647[244] = 0;
   out_321710036859700647[245] = 0;
   out_321710036859700647[246] = 0;
   out_321710036859700647[247] = 1;
   out_321710036859700647[248] = 0;
   out_321710036859700647[249] = 0;
   out_321710036859700647[250] = 0;
   out_321710036859700647[251] = 0;
   out_321710036859700647[252] = 0;
   out_321710036859700647[253] = 0;
   out_321710036859700647[254] = 0;
   out_321710036859700647[255] = 0;
   out_321710036859700647[256] = 0;
   out_321710036859700647[257] = 0;
   out_321710036859700647[258] = 0;
   out_321710036859700647[259] = 0;
   out_321710036859700647[260] = 0;
   out_321710036859700647[261] = 0;
   out_321710036859700647[262] = 0;
   out_321710036859700647[263] = 0;
   out_321710036859700647[264] = 0;
   out_321710036859700647[265] = 0;
   out_321710036859700647[266] = 1;
   out_321710036859700647[267] = 0;
   out_321710036859700647[268] = 0;
   out_321710036859700647[269] = 0;
   out_321710036859700647[270] = 0;
   out_321710036859700647[271] = 0;
   out_321710036859700647[272] = 0;
   out_321710036859700647[273] = 0;
   out_321710036859700647[274] = 0;
   out_321710036859700647[275] = 0;
   out_321710036859700647[276] = 0;
   out_321710036859700647[277] = 0;
   out_321710036859700647[278] = 0;
   out_321710036859700647[279] = 0;
   out_321710036859700647[280] = 0;
   out_321710036859700647[281] = 0;
   out_321710036859700647[282] = 0;
   out_321710036859700647[283] = 0;
   out_321710036859700647[284] = 0;
   out_321710036859700647[285] = 1;
   out_321710036859700647[286] = 0;
   out_321710036859700647[287] = 0;
   out_321710036859700647[288] = 0;
   out_321710036859700647[289] = 0;
   out_321710036859700647[290] = 0;
   out_321710036859700647[291] = 0;
   out_321710036859700647[292] = 0;
   out_321710036859700647[293] = 0;
   out_321710036859700647[294] = 0;
   out_321710036859700647[295] = 0;
   out_321710036859700647[296] = 0;
   out_321710036859700647[297] = 0;
   out_321710036859700647[298] = 0;
   out_321710036859700647[299] = 0;
   out_321710036859700647[300] = 0;
   out_321710036859700647[301] = 0;
   out_321710036859700647[302] = 0;
   out_321710036859700647[303] = 0;
   out_321710036859700647[304] = 1;
   out_321710036859700647[305] = 0;
   out_321710036859700647[306] = 0;
   out_321710036859700647[307] = 0;
   out_321710036859700647[308] = 0;
   out_321710036859700647[309] = 0;
   out_321710036859700647[310] = 0;
   out_321710036859700647[311] = 0;
   out_321710036859700647[312] = 0;
   out_321710036859700647[313] = 0;
   out_321710036859700647[314] = 0;
   out_321710036859700647[315] = 0;
   out_321710036859700647[316] = 0;
   out_321710036859700647[317] = 0;
   out_321710036859700647[318] = 0;
   out_321710036859700647[319] = 0;
   out_321710036859700647[320] = 0;
   out_321710036859700647[321] = 0;
   out_321710036859700647[322] = 0;
   out_321710036859700647[323] = 1;
}
void h_4(double *state, double *unused, double *out_8984471206441981160) {
   out_8984471206441981160[0] = state[6] + state[9];
   out_8984471206441981160[1] = state[7] + state[10];
   out_8984471206441981160[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1511051527086335609) {
   out_1511051527086335609[0] = 0;
   out_1511051527086335609[1] = 0;
   out_1511051527086335609[2] = 0;
   out_1511051527086335609[3] = 0;
   out_1511051527086335609[4] = 0;
   out_1511051527086335609[5] = 0;
   out_1511051527086335609[6] = 1;
   out_1511051527086335609[7] = 0;
   out_1511051527086335609[8] = 0;
   out_1511051527086335609[9] = 1;
   out_1511051527086335609[10] = 0;
   out_1511051527086335609[11] = 0;
   out_1511051527086335609[12] = 0;
   out_1511051527086335609[13] = 0;
   out_1511051527086335609[14] = 0;
   out_1511051527086335609[15] = 0;
   out_1511051527086335609[16] = 0;
   out_1511051527086335609[17] = 0;
   out_1511051527086335609[18] = 0;
   out_1511051527086335609[19] = 0;
   out_1511051527086335609[20] = 0;
   out_1511051527086335609[21] = 0;
   out_1511051527086335609[22] = 0;
   out_1511051527086335609[23] = 0;
   out_1511051527086335609[24] = 0;
   out_1511051527086335609[25] = 1;
   out_1511051527086335609[26] = 0;
   out_1511051527086335609[27] = 0;
   out_1511051527086335609[28] = 1;
   out_1511051527086335609[29] = 0;
   out_1511051527086335609[30] = 0;
   out_1511051527086335609[31] = 0;
   out_1511051527086335609[32] = 0;
   out_1511051527086335609[33] = 0;
   out_1511051527086335609[34] = 0;
   out_1511051527086335609[35] = 0;
   out_1511051527086335609[36] = 0;
   out_1511051527086335609[37] = 0;
   out_1511051527086335609[38] = 0;
   out_1511051527086335609[39] = 0;
   out_1511051527086335609[40] = 0;
   out_1511051527086335609[41] = 0;
   out_1511051527086335609[42] = 0;
   out_1511051527086335609[43] = 0;
   out_1511051527086335609[44] = 1;
   out_1511051527086335609[45] = 0;
   out_1511051527086335609[46] = 0;
   out_1511051527086335609[47] = 1;
   out_1511051527086335609[48] = 0;
   out_1511051527086335609[49] = 0;
   out_1511051527086335609[50] = 0;
   out_1511051527086335609[51] = 0;
   out_1511051527086335609[52] = 0;
   out_1511051527086335609[53] = 0;
}
void h_10(double *state, double *unused, double *out_1160903693658888330) {
   out_1160903693658888330[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1160903693658888330[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1160903693658888330[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8626357209504260991) {
   out_8626357209504260991[0] = 0;
   out_8626357209504260991[1] = 9.8100000000000005*cos(state[1]);
   out_8626357209504260991[2] = 0;
   out_8626357209504260991[3] = 0;
   out_8626357209504260991[4] = -state[8];
   out_8626357209504260991[5] = state[7];
   out_8626357209504260991[6] = 0;
   out_8626357209504260991[7] = state[5];
   out_8626357209504260991[8] = -state[4];
   out_8626357209504260991[9] = 0;
   out_8626357209504260991[10] = 0;
   out_8626357209504260991[11] = 0;
   out_8626357209504260991[12] = 1;
   out_8626357209504260991[13] = 0;
   out_8626357209504260991[14] = 0;
   out_8626357209504260991[15] = 1;
   out_8626357209504260991[16] = 0;
   out_8626357209504260991[17] = 0;
   out_8626357209504260991[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8626357209504260991[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8626357209504260991[20] = 0;
   out_8626357209504260991[21] = state[8];
   out_8626357209504260991[22] = 0;
   out_8626357209504260991[23] = -state[6];
   out_8626357209504260991[24] = -state[5];
   out_8626357209504260991[25] = 0;
   out_8626357209504260991[26] = state[3];
   out_8626357209504260991[27] = 0;
   out_8626357209504260991[28] = 0;
   out_8626357209504260991[29] = 0;
   out_8626357209504260991[30] = 0;
   out_8626357209504260991[31] = 1;
   out_8626357209504260991[32] = 0;
   out_8626357209504260991[33] = 0;
   out_8626357209504260991[34] = 1;
   out_8626357209504260991[35] = 0;
   out_8626357209504260991[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8626357209504260991[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8626357209504260991[38] = 0;
   out_8626357209504260991[39] = -state[7];
   out_8626357209504260991[40] = state[6];
   out_8626357209504260991[41] = 0;
   out_8626357209504260991[42] = state[4];
   out_8626357209504260991[43] = -state[3];
   out_8626357209504260991[44] = 0;
   out_8626357209504260991[45] = 0;
   out_8626357209504260991[46] = 0;
   out_8626357209504260991[47] = 0;
   out_8626357209504260991[48] = 0;
   out_8626357209504260991[49] = 0;
   out_8626357209504260991[50] = 1;
   out_8626357209504260991[51] = 0;
   out_8626357209504260991[52] = 0;
   out_8626357209504260991[53] = 1;
}
void h_13(double *state, double *unused, double *out_8776526610688936203) {
   out_8776526610688936203[0] = state[3];
   out_8776526610688936203[1] = state[4];
   out_8776526610688936203[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6099579681230365320) {
   out_6099579681230365320[0] = 0;
   out_6099579681230365320[1] = 0;
   out_6099579681230365320[2] = 0;
   out_6099579681230365320[3] = 1;
   out_6099579681230365320[4] = 0;
   out_6099579681230365320[5] = 0;
   out_6099579681230365320[6] = 0;
   out_6099579681230365320[7] = 0;
   out_6099579681230365320[8] = 0;
   out_6099579681230365320[9] = 0;
   out_6099579681230365320[10] = 0;
   out_6099579681230365320[11] = 0;
   out_6099579681230365320[12] = 0;
   out_6099579681230365320[13] = 0;
   out_6099579681230365320[14] = 0;
   out_6099579681230365320[15] = 0;
   out_6099579681230365320[16] = 0;
   out_6099579681230365320[17] = 0;
   out_6099579681230365320[18] = 0;
   out_6099579681230365320[19] = 0;
   out_6099579681230365320[20] = 0;
   out_6099579681230365320[21] = 0;
   out_6099579681230365320[22] = 1;
   out_6099579681230365320[23] = 0;
   out_6099579681230365320[24] = 0;
   out_6099579681230365320[25] = 0;
   out_6099579681230365320[26] = 0;
   out_6099579681230365320[27] = 0;
   out_6099579681230365320[28] = 0;
   out_6099579681230365320[29] = 0;
   out_6099579681230365320[30] = 0;
   out_6099579681230365320[31] = 0;
   out_6099579681230365320[32] = 0;
   out_6099579681230365320[33] = 0;
   out_6099579681230365320[34] = 0;
   out_6099579681230365320[35] = 0;
   out_6099579681230365320[36] = 0;
   out_6099579681230365320[37] = 0;
   out_6099579681230365320[38] = 0;
   out_6099579681230365320[39] = 0;
   out_6099579681230365320[40] = 0;
   out_6099579681230365320[41] = 1;
   out_6099579681230365320[42] = 0;
   out_6099579681230365320[43] = 0;
   out_6099579681230365320[44] = 0;
   out_6099579681230365320[45] = 0;
   out_6099579681230365320[46] = 0;
   out_6099579681230365320[47] = 0;
   out_6099579681230365320[48] = 0;
   out_6099579681230365320[49] = 0;
   out_6099579681230365320[50] = 0;
   out_6099579681230365320[51] = 0;
   out_6099579681230365320[52] = 0;
   out_6099579681230365320[53] = 0;
}
void h_14(double *state, double *unused, double *out_3918582584245710569) {
   out_3918582584245710569[0] = state[6];
   out_3918582584245710569[1] = state[7];
   out_3918582584245710569[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2452189329253148920) {
   out_2452189329253148920[0] = 0;
   out_2452189329253148920[1] = 0;
   out_2452189329253148920[2] = 0;
   out_2452189329253148920[3] = 0;
   out_2452189329253148920[4] = 0;
   out_2452189329253148920[5] = 0;
   out_2452189329253148920[6] = 1;
   out_2452189329253148920[7] = 0;
   out_2452189329253148920[8] = 0;
   out_2452189329253148920[9] = 0;
   out_2452189329253148920[10] = 0;
   out_2452189329253148920[11] = 0;
   out_2452189329253148920[12] = 0;
   out_2452189329253148920[13] = 0;
   out_2452189329253148920[14] = 0;
   out_2452189329253148920[15] = 0;
   out_2452189329253148920[16] = 0;
   out_2452189329253148920[17] = 0;
   out_2452189329253148920[18] = 0;
   out_2452189329253148920[19] = 0;
   out_2452189329253148920[20] = 0;
   out_2452189329253148920[21] = 0;
   out_2452189329253148920[22] = 0;
   out_2452189329253148920[23] = 0;
   out_2452189329253148920[24] = 0;
   out_2452189329253148920[25] = 1;
   out_2452189329253148920[26] = 0;
   out_2452189329253148920[27] = 0;
   out_2452189329253148920[28] = 0;
   out_2452189329253148920[29] = 0;
   out_2452189329253148920[30] = 0;
   out_2452189329253148920[31] = 0;
   out_2452189329253148920[32] = 0;
   out_2452189329253148920[33] = 0;
   out_2452189329253148920[34] = 0;
   out_2452189329253148920[35] = 0;
   out_2452189329253148920[36] = 0;
   out_2452189329253148920[37] = 0;
   out_2452189329253148920[38] = 0;
   out_2452189329253148920[39] = 0;
   out_2452189329253148920[40] = 0;
   out_2452189329253148920[41] = 0;
   out_2452189329253148920[42] = 0;
   out_2452189329253148920[43] = 0;
   out_2452189329253148920[44] = 1;
   out_2452189329253148920[45] = 0;
   out_2452189329253148920[46] = 0;
   out_2452189329253148920[47] = 0;
   out_2452189329253148920[48] = 0;
   out_2452189329253148920[49] = 0;
   out_2452189329253148920[50] = 0;
   out_2452189329253148920[51] = 0;
   out_2452189329253148920[52] = 0;
   out_2452189329253148920[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6990659364596708462) {
  err_fun(nom_x, delta_x, out_6990659364596708462);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1561026677999837058) {
  inv_err_fun(nom_x, true_x, out_1561026677999837058);
}
void pose_H_mod_fun(double *state, double *out_308647198819961252) {
  H_mod_fun(state, out_308647198819961252);
}
void pose_f_fun(double *state, double dt, double *out_7010110275742074957) {
  f_fun(state,  dt, out_7010110275742074957);
}
void pose_F_fun(double *state, double dt, double *out_321710036859700647) {
  F_fun(state,  dt, out_321710036859700647);
}
void pose_h_4(double *state, double *unused, double *out_8984471206441981160) {
  h_4(state, unused, out_8984471206441981160);
}
void pose_H_4(double *state, double *unused, double *out_1511051527086335609) {
  H_4(state, unused, out_1511051527086335609);
}
void pose_h_10(double *state, double *unused, double *out_1160903693658888330) {
  h_10(state, unused, out_1160903693658888330);
}
void pose_H_10(double *state, double *unused, double *out_8626357209504260991) {
  H_10(state, unused, out_8626357209504260991);
}
void pose_h_13(double *state, double *unused, double *out_8776526610688936203) {
  h_13(state, unused, out_8776526610688936203);
}
void pose_H_13(double *state, double *unused, double *out_6099579681230365320) {
  H_13(state, unused, out_6099579681230365320);
}
void pose_h_14(double *state, double *unused, double *out_3918582584245710569) {
  h_14(state, unused, out_3918582584245710569);
}
void pose_H_14(double *state, double *unused, double *out_2452189329253148920) {
  H_14(state, unused, out_2452189329253148920);
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
