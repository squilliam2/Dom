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
void err_fun(double *nom_x, double *delta_x, double *out_3370172615713873468) {
   out_3370172615713873468[0] = delta_x[0] + nom_x[0];
   out_3370172615713873468[1] = delta_x[1] + nom_x[1];
   out_3370172615713873468[2] = delta_x[2] + nom_x[2];
   out_3370172615713873468[3] = delta_x[3] + nom_x[3];
   out_3370172615713873468[4] = delta_x[4] + nom_x[4];
   out_3370172615713873468[5] = delta_x[5] + nom_x[5];
   out_3370172615713873468[6] = delta_x[6] + nom_x[6];
   out_3370172615713873468[7] = delta_x[7] + nom_x[7];
   out_3370172615713873468[8] = delta_x[8] + nom_x[8];
   out_3370172615713873468[9] = delta_x[9] + nom_x[9];
   out_3370172615713873468[10] = delta_x[10] + nom_x[10];
   out_3370172615713873468[11] = delta_x[11] + nom_x[11];
   out_3370172615713873468[12] = delta_x[12] + nom_x[12];
   out_3370172615713873468[13] = delta_x[13] + nom_x[13];
   out_3370172615713873468[14] = delta_x[14] + nom_x[14];
   out_3370172615713873468[15] = delta_x[15] + nom_x[15];
   out_3370172615713873468[16] = delta_x[16] + nom_x[16];
   out_3370172615713873468[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3634672358247053874) {
   out_3634672358247053874[0] = -nom_x[0] + true_x[0];
   out_3634672358247053874[1] = -nom_x[1] + true_x[1];
   out_3634672358247053874[2] = -nom_x[2] + true_x[2];
   out_3634672358247053874[3] = -nom_x[3] + true_x[3];
   out_3634672358247053874[4] = -nom_x[4] + true_x[4];
   out_3634672358247053874[5] = -nom_x[5] + true_x[5];
   out_3634672358247053874[6] = -nom_x[6] + true_x[6];
   out_3634672358247053874[7] = -nom_x[7] + true_x[7];
   out_3634672358247053874[8] = -nom_x[8] + true_x[8];
   out_3634672358247053874[9] = -nom_x[9] + true_x[9];
   out_3634672358247053874[10] = -nom_x[10] + true_x[10];
   out_3634672358247053874[11] = -nom_x[11] + true_x[11];
   out_3634672358247053874[12] = -nom_x[12] + true_x[12];
   out_3634672358247053874[13] = -nom_x[13] + true_x[13];
   out_3634672358247053874[14] = -nom_x[14] + true_x[14];
   out_3634672358247053874[15] = -nom_x[15] + true_x[15];
   out_3634672358247053874[16] = -nom_x[16] + true_x[16];
   out_3634672358247053874[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4326808709061064235) {
   out_4326808709061064235[0] = 1.0;
   out_4326808709061064235[1] = 0.0;
   out_4326808709061064235[2] = 0.0;
   out_4326808709061064235[3] = 0.0;
   out_4326808709061064235[4] = 0.0;
   out_4326808709061064235[5] = 0.0;
   out_4326808709061064235[6] = 0.0;
   out_4326808709061064235[7] = 0.0;
   out_4326808709061064235[8] = 0.0;
   out_4326808709061064235[9] = 0.0;
   out_4326808709061064235[10] = 0.0;
   out_4326808709061064235[11] = 0.0;
   out_4326808709061064235[12] = 0.0;
   out_4326808709061064235[13] = 0.0;
   out_4326808709061064235[14] = 0.0;
   out_4326808709061064235[15] = 0.0;
   out_4326808709061064235[16] = 0.0;
   out_4326808709061064235[17] = 0.0;
   out_4326808709061064235[18] = 0.0;
   out_4326808709061064235[19] = 1.0;
   out_4326808709061064235[20] = 0.0;
   out_4326808709061064235[21] = 0.0;
   out_4326808709061064235[22] = 0.0;
   out_4326808709061064235[23] = 0.0;
   out_4326808709061064235[24] = 0.0;
   out_4326808709061064235[25] = 0.0;
   out_4326808709061064235[26] = 0.0;
   out_4326808709061064235[27] = 0.0;
   out_4326808709061064235[28] = 0.0;
   out_4326808709061064235[29] = 0.0;
   out_4326808709061064235[30] = 0.0;
   out_4326808709061064235[31] = 0.0;
   out_4326808709061064235[32] = 0.0;
   out_4326808709061064235[33] = 0.0;
   out_4326808709061064235[34] = 0.0;
   out_4326808709061064235[35] = 0.0;
   out_4326808709061064235[36] = 0.0;
   out_4326808709061064235[37] = 0.0;
   out_4326808709061064235[38] = 1.0;
   out_4326808709061064235[39] = 0.0;
   out_4326808709061064235[40] = 0.0;
   out_4326808709061064235[41] = 0.0;
   out_4326808709061064235[42] = 0.0;
   out_4326808709061064235[43] = 0.0;
   out_4326808709061064235[44] = 0.0;
   out_4326808709061064235[45] = 0.0;
   out_4326808709061064235[46] = 0.0;
   out_4326808709061064235[47] = 0.0;
   out_4326808709061064235[48] = 0.0;
   out_4326808709061064235[49] = 0.0;
   out_4326808709061064235[50] = 0.0;
   out_4326808709061064235[51] = 0.0;
   out_4326808709061064235[52] = 0.0;
   out_4326808709061064235[53] = 0.0;
   out_4326808709061064235[54] = 0.0;
   out_4326808709061064235[55] = 0.0;
   out_4326808709061064235[56] = 0.0;
   out_4326808709061064235[57] = 1.0;
   out_4326808709061064235[58] = 0.0;
   out_4326808709061064235[59] = 0.0;
   out_4326808709061064235[60] = 0.0;
   out_4326808709061064235[61] = 0.0;
   out_4326808709061064235[62] = 0.0;
   out_4326808709061064235[63] = 0.0;
   out_4326808709061064235[64] = 0.0;
   out_4326808709061064235[65] = 0.0;
   out_4326808709061064235[66] = 0.0;
   out_4326808709061064235[67] = 0.0;
   out_4326808709061064235[68] = 0.0;
   out_4326808709061064235[69] = 0.0;
   out_4326808709061064235[70] = 0.0;
   out_4326808709061064235[71] = 0.0;
   out_4326808709061064235[72] = 0.0;
   out_4326808709061064235[73] = 0.0;
   out_4326808709061064235[74] = 0.0;
   out_4326808709061064235[75] = 0.0;
   out_4326808709061064235[76] = 1.0;
   out_4326808709061064235[77] = 0.0;
   out_4326808709061064235[78] = 0.0;
   out_4326808709061064235[79] = 0.0;
   out_4326808709061064235[80] = 0.0;
   out_4326808709061064235[81] = 0.0;
   out_4326808709061064235[82] = 0.0;
   out_4326808709061064235[83] = 0.0;
   out_4326808709061064235[84] = 0.0;
   out_4326808709061064235[85] = 0.0;
   out_4326808709061064235[86] = 0.0;
   out_4326808709061064235[87] = 0.0;
   out_4326808709061064235[88] = 0.0;
   out_4326808709061064235[89] = 0.0;
   out_4326808709061064235[90] = 0.0;
   out_4326808709061064235[91] = 0.0;
   out_4326808709061064235[92] = 0.0;
   out_4326808709061064235[93] = 0.0;
   out_4326808709061064235[94] = 0.0;
   out_4326808709061064235[95] = 1.0;
   out_4326808709061064235[96] = 0.0;
   out_4326808709061064235[97] = 0.0;
   out_4326808709061064235[98] = 0.0;
   out_4326808709061064235[99] = 0.0;
   out_4326808709061064235[100] = 0.0;
   out_4326808709061064235[101] = 0.0;
   out_4326808709061064235[102] = 0.0;
   out_4326808709061064235[103] = 0.0;
   out_4326808709061064235[104] = 0.0;
   out_4326808709061064235[105] = 0.0;
   out_4326808709061064235[106] = 0.0;
   out_4326808709061064235[107] = 0.0;
   out_4326808709061064235[108] = 0.0;
   out_4326808709061064235[109] = 0.0;
   out_4326808709061064235[110] = 0.0;
   out_4326808709061064235[111] = 0.0;
   out_4326808709061064235[112] = 0.0;
   out_4326808709061064235[113] = 0.0;
   out_4326808709061064235[114] = 1.0;
   out_4326808709061064235[115] = 0.0;
   out_4326808709061064235[116] = 0.0;
   out_4326808709061064235[117] = 0.0;
   out_4326808709061064235[118] = 0.0;
   out_4326808709061064235[119] = 0.0;
   out_4326808709061064235[120] = 0.0;
   out_4326808709061064235[121] = 0.0;
   out_4326808709061064235[122] = 0.0;
   out_4326808709061064235[123] = 0.0;
   out_4326808709061064235[124] = 0.0;
   out_4326808709061064235[125] = 0.0;
   out_4326808709061064235[126] = 0.0;
   out_4326808709061064235[127] = 0.0;
   out_4326808709061064235[128] = 0.0;
   out_4326808709061064235[129] = 0.0;
   out_4326808709061064235[130] = 0.0;
   out_4326808709061064235[131] = 0.0;
   out_4326808709061064235[132] = 0.0;
   out_4326808709061064235[133] = 1.0;
   out_4326808709061064235[134] = 0.0;
   out_4326808709061064235[135] = 0.0;
   out_4326808709061064235[136] = 0.0;
   out_4326808709061064235[137] = 0.0;
   out_4326808709061064235[138] = 0.0;
   out_4326808709061064235[139] = 0.0;
   out_4326808709061064235[140] = 0.0;
   out_4326808709061064235[141] = 0.0;
   out_4326808709061064235[142] = 0.0;
   out_4326808709061064235[143] = 0.0;
   out_4326808709061064235[144] = 0.0;
   out_4326808709061064235[145] = 0.0;
   out_4326808709061064235[146] = 0.0;
   out_4326808709061064235[147] = 0.0;
   out_4326808709061064235[148] = 0.0;
   out_4326808709061064235[149] = 0.0;
   out_4326808709061064235[150] = 0.0;
   out_4326808709061064235[151] = 0.0;
   out_4326808709061064235[152] = 1.0;
   out_4326808709061064235[153] = 0.0;
   out_4326808709061064235[154] = 0.0;
   out_4326808709061064235[155] = 0.0;
   out_4326808709061064235[156] = 0.0;
   out_4326808709061064235[157] = 0.0;
   out_4326808709061064235[158] = 0.0;
   out_4326808709061064235[159] = 0.0;
   out_4326808709061064235[160] = 0.0;
   out_4326808709061064235[161] = 0.0;
   out_4326808709061064235[162] = 0.0;
   out_4326808709061064235[163] = 0.0;
   out_4326808709061064235[164] = 0.0;
   out_4326808709061064235[165] = 0.0;
   out_4326808709061064235[166] = 0.0;
   out_4326808709061064235[167] = 0.0;
   out_4326808709061064235[168] = 0.0;
   out_4326808709061064235[169] = 0.0;
   out_4326808709061064235[170] = 0.0;
   out_4326808709061064235[171] = 1.0;
   out_4326808709061064235[172] = 0.0;
   out_4326808709061064235[173] = 0.0;
   out_4326808709061064235[174] = 0.0;
   out_4326808709061064235[175] = 0.0;
   out_4326808709061064235[176] = 0.0;
   out_4326808709061064235[177] = 0.0;
   out_4326808709061064235[178] = 0.0;
   out_4326808709061064235[179] = 0.0;
   out_4326808709061064235[180] = 0.0;
   out_4326808709061064235[181] = 0.0;
   out_4326808709061064235[182] = 0.0;
   out_4326808709061064235[183] = 0.0;
   out_4326808709061064235[184] = 0.0;
   out_4326808709061064235[185] = 0.0;
   out_4326808709061064235[186] = 0.0;
   out_4326808709061064235[187] = 0.0;
   out_4326808709061064235[188] = 0.0;
   out_4326808709061064235[189] = 0.0;
   out_4326808709061064235[190] = 1.0;
   out_4326808709061064235[191] = 0.0;
   out_4326808709061064235[192] = 0.0;
   out_4326808709061064235[193] = 0.0;
   out_4326808709061064235[194] = 0.0;
   out_4326808709061064235[195] = 0.0;
   out_4326808709061064235[196] = 0.0;
   out_4326808709061064235[197] = 0.0;
   out_4326808709061064235[198] = 0.0;
   out_4326808709061064235[199] = 0.0;
   out_4326808709061064235[200] = 0.0;
   out_4326808709061064235[201] = 0.0;
   out_4326808709061064235[202] = 0.0;
   out_4326808709061064235[203] = 0.0;
   out_4326808709061064235[204] = 0.0;
   out_4326808709061064235[205] = 0.0;
   out_4326808709061064235[206] = 0.0;
   out_4326808709061064235[207] = 0.0;
   out_4326808709061064235[208] = 0.0;
   out_4326808709061064235[209] = 1.0;
   out_4326808709061064235[210] = 0.0;
   out_4326808709061064235[211] = 0.0;
   out_4326808709061064235[212] = 0.0;
   out_4326808709061064235[213] = 0.0;
   out_4326808709061064235[214] = 0.0;
   out_4326808709061064235[215] = 0.0;
   out_4326808709061064235[216] = 0.0;
   out_4326808709061064235[217] = 0.0;
   out_4326808709061064235[218] = 0.0;
   out_4326808709061064235[219] = 0.0;
   out_4326808709061064235[220] = 0.0;
   out_4326808709061064235[221] = 0.0;
   out_4326808709061064235[222] = 0.0;
   out_4326808709061064235[223] = 0.0;
   out_4326808709061064235[224] = 0.0;
   out_4326808709061064235[225] = 0.0;
   out_4326808709061064235[226] = 0.0;
   out_4326808709061064235[227] = 0.0;
   out_4326808709061064235[228] = 1.0;
   out_4326808709061064235[229] = 0.0;
   out_4326808709061064235[230] = 0.0;
   out_4326808709061064235[231] = 0.0;
   out_4326808709061064235[232] = 0.0;
   out_4326808709061064235[233] = 0.0;
   out_4326808709061064235[234] = 0.0;
   out_4326808709061064235[235] = 0.0;
   out_4326808709061064235[236] = 0.0;
   out_4326808709061064235[237] = 0.0;
   out_4326808709061064235[238] = 0.0;
   out_4326808709061064235[239] = 0.0;
   out_4326808709061064235[240] = 0.0;
   out_4326808709061064235[241] = 0.0;
   out_4326808709061064235[242] = 0.0;
   out_4326808709061064235[243] = 0.0;
   out_4326808709061064235[244] = 0.0;
   out_4326808709061064235[245] = 0.0;
   out_4326808709061064235[246] = 0.0;
   out_4326808709061064235[247] = 1.0;
   out_4326808709061064235[248] = 0.0;
   out_4326808709061064235[249] = 0.0;
   out_4326808709061064235[250] = 0.0;
   out_4326808709061064235[251] = 0.0;
   out_4326808709061064235[252] = 0.0;
   out_4326808709061064235[253] = 0.0;
   out_4326808709061064235[254] = 0.0;
   out_4326808709061064235[255] = 0.0;
   out_4326808709061064235[256] = 0.0;
   out_4326808709061064235[257] = 0.0;
   out_4326808709061064235[258] = 0.0;
   out_4326808709061064235[259] = 0.0;
   out_4326808709061064235[260] = 0.0;
   out_4326808709061064235[261] = 0.0;
   out_4326808709061064235[262] = 0.0;
   out_4326808709061064235[263] = 0.0;
   out_4326808709061064235[264] = 0.0;
   out_4326808709061064235[265] = 0.0;
   out_4326808709061064235[266] = 1.0;
   out_4326808709061064235[267] = 0.0;
   out_4326808709061064235[268] = 0.0;
   out_4326808709061064235[269] = 0.0;
   out_4326808709061064235[270] = 0.0;
   out_4326808709061064235[271] = 0.0;
   out_4326808709061064235[272] = 0.0;
   out_4326808709061064235[273] = 0.0;
   out_4326808709061064235[274] = 0.0;
   out_4326808709061064235[275] = 0.0;
   out_4326808709061064235[276] = 0.0;
   out_4326808709061064235[277] = 0.0;
   out_4326808709061064235[278] = 0.0;
   out_4326808709061064235[279] = 0.0;
   out_4326808709061064235[280] = 0.0;
   out_4326808709061064235[281] = 0.0;
   out_4326808709061064235[282] = 0.0;
   out_4326808709061064235[283] = 0.0;
   out_4326808709061064235[284] = 0.0;
   out_4326808709061064235[285] = 1.0;
   out_4326808709061064235[286] = 0.0;
   out_4326808709061064235[287] = 0.0;
   out_4326808709061064235[288] = 0.0;
   out_4326808709061064235[289] = 0.0;
   out_4326808709061064235[290] = 0.0;
   out_4326808709061064235[291] = 0.0;
   out_4326808709061064235[292] = 0.0;
   out_4326808709061064235[293] = 0.0;
   out_4326808709061064235[294] = 0.0;
   out_4326808709061064235[295] = 0.0;
   out_4326808709061064235[296] = 0.0;
   out_4326808709061064235[297] = 0.0;
   out_4326808709061064235[298] = 0.0;
   out_4326808709061064235[299] = 0.0;
   out_4326808709061064235[300] = 0.0;
   out_4326808709061064235[301] = 0.0;
   out_4326808709061064235[302] = 0.0;
   out_4326808709061064235[303] = 0.0;
   out_4326808709061064235[304] = 1.0;
   out_4326808709061064235[305] = 0.0;
   out_4326808709061064235[306] = 0.0;
   out_4326808709061064235[307] = 0.0;
   out_4326808709061064235[308] = 0.0;
   out_4326808709061064235[309] = 0.0;
   out_4326808709061064235[310] = 0.0;
   out_4326808709061064235[311] = 0.0;
   out_4326808709061064235[312] = 0.0;
   out_4326808709061064235[313] = 0.0;
   out_4326808709061064235[314] = 0.0;
   out_4326808709061064235[315] = 0.0;
   out_4326808709061064235[316] = 0.0;
   out_4326808709061064235[317] = 0.0;
   out_4326808709061064235[318] = 0.0;
   out_4326808709061064235[319] = 0.0;
   out_4326808709061064235[320] = 0.0;
   out_4326808709061064235[321] = 0.0;
   out_4326808709061064235[322] = 0.0;
   out_4326808709061064235[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4276772873746558675) {
   out_4276772873746558675[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4276772873746558675[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4276772873746558675[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4276772873746558675[3] = dt*state[12] + state[3];
   out_4276772873746558675[4] = dt*state[13] + state[4];
   out_4276772873746558675[5] = dt*state[14] + state[5];
   out_4276772873746558675[6] = state[6];
   out_4276772873746558675[7] = state[7];
   out_4276772873746558675[8] = state[8];
   out_4276772873746558675[9] = state[9];
   out_4276772873746558675[10] = state[10];
   out_4276772873746558675[11] = state[11];
   out_4276772873746558675[12] = state[12];
   out_4276772873746558675[13] = state[13];
   out_4276772873746558675[14] = state[14];
   out_4276772873746558675[15] = state[15];
   out_4276772873746558675[16] = state[16];
   out_4276772873746558675[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4500717382901464499) {
   out_4500717382901464499[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4500717382901464499[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4500717382901464499[2] = 0;
   out_4500717382901464499[3] = 0;
   out_4500717382901464499[4] = 0;
   out_4500717382901464499[5] = 0;
   out_4500717382901464499[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4500717382901464499[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4500717382901464499[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4500717382901464499[9] = 0;
   out_4500717382901464499[10] = 0;
   out_4500717382901464499[11] = 0;
   out_4500717382901464499[12] = 0;
   out_4500717382901464499[13] = 0;
   out_4500717382901464499[14] = 0;
   out_4500717382901464499[15] = 0;
   out_4500717382901464499[16] = 0;
   out_4500717382901464499[17] = 0;
   out_4500717382901464499[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4500717382901464499[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4500717382901464499[20] = 0;
   out_4500717382901464499[21] = 0;
   out_4500717382901464499[22] = 0;
   out_4500717382901464499[23] = 0;
   out_4500717382901464499[24] = 0;
   out_4500717382901464499[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4500717382901464499[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4500717382901464499[27] = 0;
   out_4500717382901464499[28] = 0;
   out_4500717382901464499[29] = 0;
   out_4500717382901464499[30] = 0;
   out_4500717382901464499[31] = 0;
   out_4500717382901464499[32] = 0;
   out_4500717382901464499[33] = 0;
   out_4500717382901464499[34] = 0;
   out_4500717382901464499[35] = 0;
   out_4500717382901464499[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4500717382901464499[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4500717382901464499[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4500717382901464499[39] = 0;
   out_4500717382901464499[40] = 0;
   out_4500717382901464499[41] = 0;
   out_4500717382901464499[42] = 0;
   out_4500717382901464499[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4500717382901464499[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4500717382901464499[45] = 0;
   out_4500717382901464499[46] = 0;
   out_4500717382901464499[47] = 0;
   out_4500717382901464499[48] = 0;
   out_4500717382901464499[49] = 0;
   out_4500717382901464499[50] = 0;
   out_4500717382901464499[51] = 0;
   out_4500717382901464499[52] = 0;
   out_4500717382901464499[53] = 0;
   out_4500717382901464499[54] = 0;
   out_4500717382901464499[55] = 0;
   out_4500717382901464499[56] = 0;
   out_4500717382901464499[57] = 1;
   out_4500717382901464499[58] = 0;
   out_4500717382901464499[59] = 0;
   out_4500717382901464499[60] = 0;
   out_4500717382901464499[61] = 0;
   out_4500717382901464499[62] = 0;
   out_4500717382901464499[63] = 0;
   out_4500717382901464499[64] = 0;
   out_4500717382901464499[65] = 0;
   out_4500717382901464499[66] = dt;
   out_4500717382901464499[67] = 0;
   out_4500717382901464499[68] = 0;
   out_4500717382901464499[69] = 0;
   out_4500717382901464499[70] = 0;
   out_4500717382901464499[71] = 0;
   out_4500717382901464499[72] = 0;
   out_4500717382901464499[73] = 0;
   out_4500717382901464499[74] = 0;
   out_4500717382901464499[75] = 0;
   out_4500717382901464499[76] = 1;
   out_4500717382901464499[77] = 0;
   out_4500717382901464499[78] = 0;
   out_4500717382901464499[79] = 0;
   out_4500717382901464499[80] = 0;
   out_4500717382901464499[81] = 0;
   out_4500717382901464499[82] = 0;
   out_4500717382901464499[83] = 0;
   out_4500717382901464499[84] = 0;
   out_4500717382901464499[85] = dt;
   out_4500717382901464499[86] = 0;
   out_4500717382901464499[87] = 0;
   out_4500717382901464499[88] = 0;
   out_4500717382901464499[89] = 0;
   out_4500717382901464499[90] = 0;
   out_4500717382901464499[91] = 0;
   out_4500717382901464499[92] = 0;
   out_4500717382901464499[93] = 0;
   out_4500717382901464499[94] = 0;
   out_4500717382901464499[95] = 1;
   out_4500717382901464499[96] = 0;
   out_4500717382901464499[97] = 0;
   out_4500717382901464499[98] = 0;
   out_4500717382901464499[99] = 0;
   out_4500717382901464499[100] = 0;
   out_4500717382901464499[101] = 0;
   out_4500717382901464499[102] = 0;
   out_4500717382901464499[103] = 0;
   out_4500717382901464499[104] = dt;
   out_4500717382901464499[105] = 0;
   out_4500717382901464499[106] = 0;
   out_4500717382901464499[107] = 0;
   out_4500717382901464499[108] = 0;
   out_4500717382901464499[109] = 0;
   out_4500717382901464499[110] = 0;
   out_4500717382901464499[111] = 0;
   out_4500717382901464499[112] = 0;
   out_4500717382901464499[113] = 0;
   out_4500717382901464499[114] = 1;
   out_4500717382901464499[115] = 0;
   out_4500717382901464499[116] = 0;
   out_4500717382901464499[117] = 0;
   out_4500717382901464499[118] = 0;
   out_4500717382901464499[119] = 0;
   out_4500717382901464499[120] = 0;
   out_4500717382901464499[121] = 0;
   out_4500717382901464499[122] = 0;
   out_4500717382901464499[123] = 0;
   out_4500717382901464499[124] = 0;
   out_4500717382901464499[125] = 0;
   out_4500717382901464499[126] = 0;
   out_4500717382901464499[127] = 0;
   out_4500717382901464499[128] = 0;
   out_4500717382901464499[129] = 0;
   out_4500717382901464499[130] = 0;
   out_4500717382901464499[131] = 0;
   out_4500717382901464499[132] = 0;
   out_4500717382901464499[133] = 1;
   out_4500717382901464499[134] = 0;
   out_4500717382901464499[135] = 0;
   out_4500717382901464499[136] = 0;
   out_4500717382901464499[137] = 0;
   out_4500717382901464499[138] = 0;
   out_4500717382901464499[139] = 0;
   out_4500717382901464499[140] = 0;
   out_4500717382901464499[141] = 0;
   out_4500717382901464499[142] = 0;
   out_4500717382901464499[143] = 0;
   out_4500717382901464499[144] = 0;
   out_4500717382901464499[145] = 0;
   out_4500717382901464499[146] = 0;
   out_4500717382901464499[147] = 0;
   out_4500717382901464499[148] = 0;
   out_4500717382901464499[149] = 0;
   out_4500717382901464499[150] = 0;
   out_4500717382901464499[151] = 0;
   out_4500717382901464499[152] = 1;
   out_4500717382901464499[153] = 0;
   out_4500717382901464499[154] = 0;
   out_4500717382901464499[155] = 0;
   out_4500717382901464499[156] = 0;
   out_4500717382901464499[157] = 0;
   out_4500717382901464499[158] = 0;
   out_4500717382901464499[159] = 0;
   out_4500717382901464499[160] = 0;
   out_4500717382901464499[161] = 0;
   out_4500717382901464499[162] = 0;
   out_4500717382901464499[163] = 0;
   out_4500717382901464499[164] = 0;
   out_4500717382901464499[165] = 0;
   out_4500717382901464499[166] = 0;
   out_4500717382901464499[167] = 0;
   out_4500717382901464499[168] = 0;
   out_4500717382901464499[169] = 0;
   out_4500717382901464499[170] = 0;
   out_4500717382901464499[171] = 1;
   out_4500717382901464499[172] = 0;
   out_4500717382901464499[173] = 0;
   out_4500717382901464499[174] = 0;
   out_4500717382901464499[175] = 0;
   out_4500717382901464499[176] = 0;
   out_4500717382901464499[177] = 0;
   out_4500717382901464499[178] = 0;
   out_4500717382901464499[179] = 0;
   out_4500717382901464499[180] = 0;
   out_4500717382901464499[181] = 0;
   out_4500717382901464499[182] = 0;
   out_4500717382901464499[183] = 0;
   out_4500717382901464499[184] = 0;
   out_4500717382901464499[185] = 0;
   out_4500717382901464499[186] = 0;
   out_4500717382901464499[187] = 0;
   out_4500717382901464499[188] = 0;
   out_4500717382901464499[189] = 0;
   out_4500717382901464499[190] = 1;
   out_4500717382901464499[191] = 0;
   out_4500717382901464499[192] = 0;
   out_4500717382901464499[193] = 0;
   out_4500717382901464499[194] = 0;
   out_4500717382901464499[195] = 0;
   out_4500717382901464499[196] = 0;
   out_4500717382901464499[197] = 0;
   out_4500717382901464499[198] = 0;
   out_4500717382901464499[199] = 0;
   out_4500717382901464499[200] = 0;
   out_4500717382901464499[201] = 0;
   out_4500717382901464499[202] = 0;
   out_4500717382901464499[203] = 0;
   out_4500717382901464499[204] = 0;
   out_4500717382901464499[205] = 0;
   out_4500717382901464499[206] = 0;
   out_4500717382901464499[207] = 0;
   out_4500717382901464499[208] = 0;
   out_4500717382901464499[209] = 1;
   out_4500717382901464499[210] = 0;
   out_4500717382901464499[211] = 0;
   out_4500717382901464499[212] = 0;
   out_4500717382901464499[213] = 0;
   out_4500717382901464499[214] = 0;
   out_4500717382901464499[215] = 0;
   out_4500717382901464499[216] = 0;
   out_4500717382901464499[217] = 0;
   out_4500717382901464499[218] = 0;
   out_4500717382901464499[219] = 0;
   out_4500717382901464499[220] = 0;
   out_4500717382901464499[221] = 0;
   out_4500717382901464499[222] = 0;
   out_4500717382901464499[223] = 0;
   out_4500717382901464499[224] = 0;
   out_4500717382901464499[225] = 0;
   out_4500717382901464499[226] = 0;
   out_4500717382901464499[227] = 0;
   out_4500717382901464499[228] = 1;
   out_4500717382901464499[229] = 0;
   out_4500717382901464499[230] = 0;
   out_4500717382901464499[231] = 0;
   out_4500717382901464499[232] = 0;
   out_4500717382901464499[233] = 0;
   out_4500717382901464499[234] = 0;
   out_4500717382901464499[235] = 0;
   out_4500717382901464499[236] = 0;
   out_4500717382901464499[237] = 0;
   out_4500717382901464499[238] = 0;
   out_4500717382901464499[239] = 0;
   out_4500717382901464499[240] = 0;
   out_4500717382901464499[241] = 0;
   out_4500717382901464499[242] = 0;
   out_4500717382901464499[243] = 0;
   out_4500717382901464499[244] = 0;
   out_4500717382901464499[245] = 0;
   out_4500717382901464499[246] = 0;
   out_4500717382901464499[247] = 1;
   out_4500717382901464499[248] = 0;
   out_4500717382901464499[249] = 0;
   out_4500717382901464499[250] = 0;
   out_4500717382901464499[251] = 0;
   out_4500717382901464499[252] = 0;
   out_4500717382901464499[253] = 0;
   out_4500717382901464499[254] = 0;
   out_4500717382901464499[255] = 0;
   out_4500717382901464499[256] = 0;
   out_4500717382901464499[257] = 0;
   out_4500717382901464499[258] = 0;
   out_4500717382901464499[259] = 0;
   out_4500717382901464499[260] = 0;
   out_4500717382901464499[261] = 0;
   out_4500717382901464499[262] = 0;
   out_4500717382901464499[263] = 0;
   out_4500717382901464499[264] = 0;
   out_4500717382901464499[265] = 0;
   out_4500717382901464499[266] = 1;
   out_4500717382901464499[267] = 0;
   out_4500717382901464499[268] = 0;
   out_4500717382901464499[269] = 0;
   out_4500717382901464499[270] = 0;
   out_4500717382901464499[271] = 0;
   out_4500717382901464499[272] = 0;
   out_4500717382901464499[273] = 0;
   out_4500717382901464499[274] = 0;
   out_4500717382901464499[275] = 0;
   out_4500717382901464499[276] = 0;
   out_4500717382901464499[277] = 0;
   out_4500717382901464499[278] = 0;
   out_4500717382901464499[279] = 0;
   out_4500717382901464499[280] = 0;
   out_4500717382901464499[281] = 0;
   out_4500717382901464499[282] = 0;
   out_4500717382901464499[283] = 0;
   out_4500717382901464499[284] = 0;
   out_4500717382901464499[285] = 1;
   out_4500717382901464499[286] = 0;
   out_4500717382901464499[287] = 0;
   out_4500717382901464499[288] = 0;
   out_4500717382901464499[289] = 0;
   out_4500717382901464499[290] = 0;
   out_4500717382901464499[291] = 0;
   out_4500717382901464499[292] = 0;
   out_4500717382901464499[293] = 0;
   out_4500717382901464499[294] = 0;
   out_4500717382901464499[295] = 0;
   out_4500717382901464499[296] = 0;
   out_4500717382901464499[297] = 0;
   out_4500717382901464499[298] = 0;
   out_4500717382901464499[299] = 0;
   out_4500717382901464499[300] = 0;
   out_4500717382901464499[301] = 0;
   out_4500717382901464499[302] = 0;
   out_4500717382901464499[303] = 0;
   out_4500717382901464499[304] = 1;
   out_4500717382901464499[305] = 0;
   out_4500717382901464499[306] = 0;
   out_4500717382901464499[307] = 0;
   out_4500717382901464499[308] = 0;
   out_4500717382901464499[309] = 0;
   out_4500717382901464499[310] = 0;
   out_4500717382901464499[311] = 0;
   out_4500717382901464499[312] = 0;
   out_4500717382901464499[313] = 0;
   out_4500717382901464499[314] = 0;
   out_4500717382901464499[315] = 0;
   out_4500717382901464499[316] = 0;
   out_4500717382901464499[317] = 0;
   out_4500717382901464499[318] = 0;
   out_4500717382901464499[319] = 0;
   out_4500717382901464499[320] = 0;
   out_4500717382901464499[321] = 0;
   out_4500717382901464499[322] = 0;
   out_4500717382901464499[323] = 1;
}
void h_4(double *state, double *unused, double *out_5593213153040418665) {
   out_5593213153040418665[0] = state[6] + state[9];
   out_5593213153040418665[1] = state[7] + state[10];
   out_5593213153040418665[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8098615918904971807) {
   out_8098615918904971807[0] = 0;
   out_8098615918904971807[1] = 0;
   out_8098615918904971807[2] = 0;
   out_8098615918904971807[3] = 0;
   out_8098615918904971807[4] = 0;
   out_8098615918904971807[5] = 0;
   out_8098615918904971807[6] = 1;
   out_8098615918904971807[7] = 0;
   out_8098615918904971807[8] = 0;
   out_8098615918904971807[9] = 1;
   out_8098615918904971807[10] = 0;
   out_8098615918904971807[11] = 0;
   out_8098615918904971807[12] = 0;
   out_8098615918904971807[13] = 0;
   out_8098615918904971807[14] = 0;
   out_8098615918904971807[15] = 0;
   out_8098615918904971807[16] = 0;
   out_8098615918904971807[17] = 0;
   out_8098615918904971807[18] = 0;
   out_8098615918904971807[19] = 0;
   out_8098615918904971807[20] = 0;
   out_8098615918904971807[21] = 0;
   out_8098615918904971807[22] = 0;
   out_8098615918904971807[23] = 0;
   out_8098615918904971807[24] = 0;
   out_8098615918904971807[25] = 1;
   out_8098615918904971807[26] = 0;
   out_8098615918904971807[27] = 0;
   out_8098615918904971807[28] = 1;
   out_8098615918904971807[29] = 0;
   out_8098615918904971807[30] = 0;
   out_8098615918904971807[31] = 0;
   out_8098615918904971807[32] = 0;
   out_8098615918904971807[33] = 0;
   out_8098615918904971807[34] = 0;
   out_8098615918904971807[35] = 0;
   out_8098615918904971807[36] = 0;
   out_8098615918904971807[37] = 0;
   out_8098615918904971807[38] = 0;
   out_8098615918904971807[39] = 0;
   out_8098615918904971807[40] = 0;
   out_8098615918904971807[41] = 0;
   out_8098615918904971807[42] = 0;
   out_8098615918904971807[43] = 0;
   out_8098615918904971807[44] = 1;
   out_8098615918904971807[45] = 0;
   out_8098615918904971807[46] = 0;
   out_8098615918904971807[47] = 1;
   out_8098615918904971807[48] = 0;
   out_8098615918904971807[49] = 0;
   out_8098615918904971807[50] = 0;
   out_8098615918904971807[51] = 0;
   out_8098615918904971807[52] = 0;
   out_8098615918904971807[53] = 0;
}
void h_10(double *state, double *unused, double *out_665779804057694470) {
   out_665779804057694470[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_665779804057694470[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_665779804057694470[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1520950660944493368) {
   out_1520950660944493368[0] = 0;
   out_1520950660944493368[1] = 9.8100000000000005*cos(state[1]);
   out_1520950660944493368[2] = 0;
   out_1520950660944493368[3] = 0;
   out_1520950660944493368[4] = -state[8];
   out_1520950660944493368[5] = state[7];
   out_1520950660944493368[6] = 0;
   out_1520950660944493368[7] = state[5];
   out_1520950660944493368[8] = -state[4];
   out_1520950660944493368[9] = 0;
   out_1520950660944493368[10] = 0;
   out_1520950660944493368[11] = 0;
   out_1520950660944493368[12] = 1;
   out_1520950660944493368[13] = 0;
   out_1520950660944493368[14] = 0;
   out_1520950660944493368[15] = 1;
   out_1520950660944493368[16] = 0;
   out_1520950660944493368[17] = 0;
   out_1520950660944493368[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1520950660944493368[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1520950660944493368[20] = 0;
   out_1520950660944493368[21] = state[8];
   out_1520950660944493368[22] = 0;
   out_1520950660944493368[23] = -state[6];
   out_1520950660944493368[24] = -state[5];
   out_1520950660944493368[25] = 0;
   out_1520950660944493368[26] = state[3];
   out_1520950660944493368[27] = 0;
   out_1520950660944493368[28] = 0;
   out_1520950660944493368[29] = 0;
   out_1520950660944493368[30] = 0;
   out_1520950660944493368[31] = 1;
   out_1520950660944493368[32] = 0;
   out_1520950660944493368[33] = 0;
   out_1520950660944493368[34] = 1;
   out_1520950660944493368[35] = 0;
   out_1520950660944493368[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1520950660944493368[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1520950660944493368[38] = 0;
   out_1520950660944493368[39] = -state[7];
   out_1520950660944493368[40] = state[6];
   out_1520950660944493368[41] = 0;
   out_1520950660944493368[42] = state[4];
   out_1520950660944493368[43] = -state[3];
   out_1520950660944493368[44] = 0;
   out_1520950660944493368[45] = 0;
   out_1520950660944493368[46] = 0;
   out_1520950660944493368[47] = 0;
   out_1520950660944493368[48] = 0;
   out_1520950660944493368[49] = 0;
   out_1520950660944493368[50] = 1;
   out_1520950660944493368[51] = 0;
   out_1520950660944493368[52] = 0;
   out_1520950660944493368[53] = 1;
}
void h_13(double *state, double *unused, double *out_1559309075612614656) {
   out_1559309075612614656[0] = state[3];
   out_1559309075612614656[1] = state[4];
   out_1559309075612614656[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8663217838586815911) {
   out_8663217838586815911[0] = 0;
   out_8663217838586815911[1] = 0;
   out_8663217838586815911[2] = 0;
   out_8663217838586815911[3] = 1;
   out_8663217838586815911[4] = 0;
   out_8663217838586815911[5] = 0;
   out_8663217838586815911[6] = 0;
   out_8663217838586815911[7] = 0;
   out_8663217838586815911[8] = 0;
   out_8663217838586815911[9] = 0;
   out_8663217838586815911[10] = 0;
   out_8663217838586815911[11] = 0;
   out_8663217838586815911[12] = 0;
   out_8663217838586815911[13] = 0;
   out_8663217838586815911[14] = 0;
   out_8663217838586815911[15] = 0;
   out_8663217838586815911[16] = 0;
   out_8663217838586815911[17] = 0;
   out_8663217838586815911[18] = 0;
   out_8663217838586815911[19] = 0;
   out_8663217838586815911[20] = 0;
   out_8663217838586815911[21] = 0;
   out_8663217838586815911[22] = 1;
   out_8663217838586815911[23] = 0;
   out_8663217838586815911[24] = 0;
   out_8663217838586815911[25] = 0;
   out_8663217838586815911[26] = 0;
   out_8663217838586815911[27] = 0;
   out_8663217838586815911[28] = 0;
   out_8663217838586815911[29] = 0;
   out_8663217838586815911[30] = 0;
   out_8663217838586815911[31] = 0;
   out_8663217838586815911[32] = 0;
   out_8663217838586815911[33] = 0;
   out_8663217838586815911[34] = 0;
   out_8663217838586815911[35] = 0;
   out_8663217838586815911[36] = 0;
   out_8663217838586815911[37] = 0;
   out_8663217838586815911[38] = 0;
   out_8663217838586815911[39] = 0;
   out_8663217838586815911[40] = 0;
   out_8663217838586815911[41] = 1;
   out_8663217838586815911[42] = 0;
   out_8663217838586815911[43] = 0;
   out_8663217838586815911[44] = 0;
   out_8663217838586815911[45] = 0;
   out_8663217838586815911[46] = 0;
   out_8663217838586815911[47] = 0;
   out_8663217838586815911[48] = 0;
   out_8663217838586815911[49] = 0;
   out_8663217838586815911[50] = 0;
   out_8663217838586815911[51] = 0;
   out_8663217838586815911[52] = 0;
   out_8663217838586815911[53] = 0;
}
void h_14(double *state, double *unused, double *out_3210315045012193153) {
   out_3210315045012193153[0] = state[6];
   out_3210315045012193153[1] = state[7];
   out_3210315045012193153[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5015827486609599511) {
   out_5015827486609599511[0] = 0;
   out_5015827486609599511[1] = 0;
   out_5015827486609599511[2] = 0;
   out_5015827486609599511[3] = 0;
   out_5015827486609599511[4] = 0;
   out_5015827486609599511[5] = 0;
   out_5015827486609599511[6] = 1;
   out_5015827486609599511[7] = 0;
   out_5015827486609599511[8] = 0;
   out_5015827486609599511[9] = 0;
   out_5015827486609599511[10] = 0;
   out_5015827486609599511[11] = 0;
   out_5015827486609599511[12] = 0;
   out_5015827486609599511[13] = 0;
   out_5015827486609599511[14] = 0;
   out_5015827486609599511[15] = 0;
   out_5015827486609599511[16] = 0;
   out_5015827486609599511[17] = 0;
   out_5015827486609599511[18] = 0;
   out_5015827486609599511[19] = 0;
   out_5015827486609599511[20] = 0;
   out_5015827486609599511[21] = 0;
   out_5015827486609599511[22] = 0;
   out_5015827486609599511[23] = 0;
   out_5015827486609599511[24] = 0;
   out_5015827486609599511[25] = 1;
   out_5015827486609599511[26] = 0;
   out_5015827486609599511[27] = 0;
   out_5015827486609599511[28] = 0;
   out_5015827486609599511[29] = 0;
   out_5015827486609599511[30] = 0;
   out_5015827486609599511[31] = 0;
   out_5015827486609599511[32] = 0;
   out_5015827486609599511[33] = 0;
   out_5015827486609599511[34] = 0;
   out_5015827486609599511[35] = 0;
   out_5015827486609599511[36] = 0;
   out_5015827486609599511[37] = 0;
   out_5015827486609599511[38] = 0;
   out_5015827486609599511[39] = 0;
   out_5015827486609599511[40] = 0;
   out_5015827486609599511[41] = 0;
   out_5015827486609599511[42] = 0;
   out_5015827486609599511[43] = 0;
   out_5015827486609599511[44] = 1;
   out_5015827486609599511[45] = 0;
   out_5015827486609599511[46] = 0;
   out_5015827486609599511[47] = 0;
   out_5015827486609599511[48] = 0;
   out_5015827486609599511[49] = 0;
   out_5015827486609599511[50] = 0;
   out_5015827486609599511[51] = 0;
   out_5015827486609599511[52] = 0;
   out_5015827486609599511[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3370172615713873468) {
  err_fun(nom_x, delta_x, out_3370172615713873468);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3634672358247053874) {
  inv_err_fun(nom_x, true_x, out_3634672358247053874);
}
void pose_H_mod_fun(double *state, double *out_4326808709061064235) {
  H_mod_fun(state, out_4326808709061064235);
}
void pose_f_fun(double *state, double dt, double *out_4276772873746558675) {
  f_fun(state,  dt, out_4276772873746558675);
}
void pose_F_fun(double *state, double dt, double *out_4500717382901464499) {
  F_fun(state,  dt, out_4500717382901464499);
}
void pose_h_4(double *state, double *unused, double *out_5593213153040418665) {
  h_4(state, unused, out_5593213153040418665);
}
void pose_H_4(double *state, double *unused, double *out_8098615918904971807) {
  H_4(state, unused, out_8098615918904971807);
}
void pose_h_10(double *state, double *unused, double *out_665779804057694470) {
  h_10(state, unused, out_665779804057694470);
}
void pose_H_10(double *state, double *unused, double *out_1520950660944493368) {
  H_10(state, unused, out_1520950660944493368);
}
void pose_h_13(double *state, double *unused, double *out_1559309075612614656) {
  h_13(state, unused, out_1559309075612614656);
}
void pose_H_13(double *state, double *unused, double *out_8663217838586815911) {
  H_13(state, unused, out_8663217838586815911);
}
void pose_h_14(double *state, double *unused, double *out_3210315045012193153) {
  h_14(state, unused, out_3210315045012193153);
}
void pose_H_14(double *state, double *unused, double *out_5015827486609599511) {
  H_14(state, unused, out_5015827486609599511);
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
