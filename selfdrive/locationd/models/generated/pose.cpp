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
void err_fun(double *nom_x, double *delta_x, double *out_6408835186344628642) {
   out_6408835186344628642[0] = delta_x[0] + nom_x[0];
   out_6408835186344628642[1] = delta_x[1] + nom_x[1];
   out_6408835186344628642[2] = delta_x[2] + nom_x[2];
   out_6408835186344628642[3] = delta_x[3] + nom_x[3];
   out_6408835186344628642[4] = delta_x[4] + nom_x[4];
   out_6408835186344628642[5] = delta_x[5] + nom_x[5];
   out_6408835186344628642[6] = delta_x[6] + nom_x[6];
   out_6408835186344628642[7] = delta_x[7] + nom_x[7];
   out_6408835186344628642[8] = delta_x[8] + nom_x[8];
   out_6408835186344628642[9] = delta_x[9] + nom_x[9];
   out_6408835186344628642[10] = delta_x[10] + nom_x[10];
   out_6408835186344628642[11] = delta_x[11] + nom_x[11];
   out_6408835186344628642[12] = delta_x[12] + nom_x[12];
   out_6408835186344628642[13] = delta_x[13] + nom_x[13];
   out_6408835186344628642[14] = delta_x[14] + nom_x[14];
   out_6408835186344628642[15] = delta_x[15] + nom_x[15];
   out_6408835186344628642[16] = delta_x[16] + nom_x[16];
   out_6408835186344628642[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4488020327469491521) {
   out_4488020327469491521[0] = -nom_x[0] + true_x[0];
   out_4488020327469491521[1] = -nom_x[1] + true_x[1];
   out_4488020327469491521[2] = -nom_x[2] + true_x[2];
   out_4488020327469491521[3] = -nom_x[3] + true_x[3];
   out_4488020327469491521[4] = -nom_x[4] + true_x[4];
   out_4488020327469491521[5] = -nom_x[5] + true_x[5];
   out_4488020327469491521[6] = -nom_x[6] + true_x[6];
   out_4488020327469491521[7] = -nom_x[7] + true_x[7];
   out_4488020327469491521[8] = -nom_x[8] + true_x[8];
   out_4488020327469491521[9] = -nom_x[9] + true_x[9];
   out_4488020327469491521[10] = -nom_x[10] + true_x[10];
   out_4488020327469491521[11] = -nom_x[11] + true_x[11];
   out_4488020327469491521[12] = -nom_x[12] + true_x[12];
   out_4488020327469491521[13] = -nom_x[13] + true_x[13];
   out_4488020327469491521[14] = -nom_x[14] + true_x[14];
   out_4488020327469491521[15] = -nom_x[15] + true_x[15];
   out_4488020327469491521[16] = -nom_x[16] + true_x[16];
   out_4488020327469491521[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8565439984289443181) {
   out_8565439984289443181[0] = 1.0;
   out_8565439984289443181[1] = 0.0;
   out_8565439984289443181[2] = 0.0;
   out_8565439984289443181[3] = 0.0;
   out_8565439984289443181[4] = 0.0;
   out_8565439984289443181[5] = 0.0;
   out_8565439984289443181[6] = 0.0;
   out_8565439984289443181[7] = 0.0;
   out_8565439984289443181[8] = 0.0;
   out_8565439984289443181[9] = 0.0;
   out_8565439984289443181[10] = 0.0;
   out_8565439984289443181[11] = 0.0;
   out_8565439984289443181[12] = 0.0;
   out_8565439984289443181[13] = 0.0;
   out_8565439984289443181[14] = 0.0;
   out_8565439984289443181[15] = 0.0;
   out_8565439984289443181[16] = 0.0;
   out_8565439984289443181[17] = 0.0;
   out_8565439984289443181[18] = 0.0;
   out_8565439984289443181[19] = 1.0;
   out_8565439984289443181[20] = 0.0;
   out_8565439984289443181[21] = 0.0;
   out_8565439984289443181[22] = 0.0;
   out_8565439984289443181[23] = 0.0;
   out_8565439984289443181[24] = 0.0;
   out_8565439984289443181[25] = 0.0;
   out_8565439984289443181[26] = 0.0;
   out_8565439984289443181[27] = 0.0;
   out_8565439984289443181[28] = 0.0;
   out_8565439984289443181[29] = 0.0;
   out_8565439984289443181[30] = 0.0;
   out_8565439984289443181[31] = 0.0;
   out_8565439984289443181[32] = 0.0;
   out_8565439984289443181[33] = 0.0;
   out_8565439984289443181[34] = 0.0;
   out_8565439984289443181[35] = 0.0;
   out_8565439984289443181[36] = 0.0;
   out_8565439984289443181[37] = 0.0;
   out_8565439984289443181[38] = 1.0;
   out_8565439984289443181[39] = 0.0;
   out_8565439984289443181[40] = 0.0;
   out_8565439984289443181[41] = 0.0;
   out_8565439984289443181[42] = 0.0;
   out_8565439984289443181[43] = 0.0;
   out_8565439984289443181[44] = 0.0;
   out_8565439984289443181[45] = 0.0;
   out_8565439984289443181[46] = 0.0;
   out_8565439984289443181[47] = 0.0;
   out_8565439984289443181[48] = 0.0;
   out_8565439984289443181[49] = 0.0;
   out_8565439984289443181[50] = 0.0;
   out_8565439984289443181[51] = 0.0;
   out_8565439984289443181[52] = 0.0;
   out_8565439984289443181[53] = 0.0;
   out_8565439984289443181[54] = 0.0;
   out_8565439984289443181[55] = 0.0;
   out_8565439984289443181[56] = 0.0;
   out_8565439984289443181[57] = 1.0;
   out_8565439984289443181[58] = 0.0;
   out_8565439984289443181[59] = 0.0;
   out_8565439984289443181[60] = 0.0;
   out_8565439984289443181[61] = 0.0;
   out_8565439984289443181[62] = 0.0;
   out_8565439984289443181[63] = 0.0;
   out_8565439984289443181[64] = 0.0;
   out_8565439984289443181[65] = 0.0;
   out_8565439984289443181[66] = 0.0;
   out_8565439984289443181[67] = 0.0;
   out_8565439984289443181[68] = 0.0;
   out_8565439984289443181[69] = 0.0;
   out_8565439984289443181[70] = 0.0;
   out_8565439984289443181[71] = 0.0;
   out_8565439984289443181[72] = 0.0;
   out_8565439984289443181[73] = 0.0;
   out_8565439984289443181[74] = 0.0;
   out_8565439984289443181[75] = 0.0;
   out_8565439984289443181[76] = 1.0;
   out_8565439984289443181[77] = 0.0;
   out_8565439984289443181[78] = 0.0;
   out_8565439984289443181[79] = 0.0;
   out_8565439984289443181[80] = 0.0;
   out_8565439984289443181[81] = 0.0;
   out_8565439984289443181[82] = 0.0;
   out_8565439984289443181[83] = 0.0;
   out_8565439984289443181[84] = 0.0;
   out_8565439984289443181[85] = 0.0;
   out_8565439984289443181[86] = 0.0;
   out_8565439984289443181[87] = 0.0;
   out_8565439984289443181[88] = 0.0;
   out_8565439984289443181[89] = 0.0;
   out_8565439984289443181[90] = 0.0;
   out_8565439984289443181[91] = 0.0;
   out_8565439984289443181[92] = 0.0;
   out_8565439984289443181[93] = 0.0;
   out_8565439984289443181[94] = 0.0;
   out_8565439984289443181[95] = 1.0;
   out_8565439984289443181[96] = 0.0;
   out_8565439984289443181[97] = 0.0;
   out_8565439984289443181[98] = 0.0;
   out_8565439984289443181[99] = 0.0;
   out_8565439984289443181[100] = 0.0;
   out_8565439984289443181[101] = 0.0;
   out_8565439984289443181[102] = 0.0;
   out_8565439984289443181[103] = 0.0;
   out_8565439984289443181[104] = 0.0;
   out_8565439984289443181[105] = 0.0;
   out_8565439984289443181[106] = 0.0;
   out_8565439984289443181[107] = 0.0;
   out_8565439984289443181[108] = 0.0;
   out_8565439984289443181[109] = 0.0;
   out_8565439984289443181[110] = 0.0;
   out_8565439984289443181[111] = 0.0;
   out_8565439984289443181[112] = 0.0;
   out_8565439984289443181[113] = 0.0;
   out_8565439984289443181[114] = 1.0;
   out_8565439984289443181[115] = 0.0;
   out_8565439984289443181[116] = 0.0;
   out_8565439984289443181[117] = 0.0;
   out_8565439984289443181[118] = 0.0;
   out_8565439984289443181[119] = 0.0;
   out_8565439984289443181[120] = 0.0;
   out_8565439984289443181[121] = 0.0;
   out_8565439984289443181[122] = 0.0;
   out_8565439984289443181[123] = 0.0;
   out_8565439984289443181[124] = 0.0;
   out_8565439984289443181[125] = 0.0;
   out_8565439984289443181[126] = 0.0;
   out_8565439984289443181[127] = 0.0;
   out_8565439984289443181[128] = 0.0;
   out_8565439984289443181[129] = 0.0;
   out_8565439984289443181[130] = 0.0;
   out_8565439984289443181[131] = 0.0;
   out_8565439984289443181[132] = 0.0;
   out_8565439984289443181[133] = 1.0;
   out_8565439984289443181[134] = 0.0;
   out_8565439984289443181[135] = 0.0;
   out_8565439984289443181[136] = 0.0;
   out_8565439984289443181[137] = 0.0;
   out_8565439984289443181[138] = 0.0;
   out_8565439984289443181[139] = 0.0;
   out_8565439984289443181[140] = 0.0;
   out_8565439984289443181[141] = 0.0;
   out_8565439984289443181[142] = 0.0;
   out_8565439984289443181[143] = 0.0;
   out_8565439984289443181[144] = 0.0;
   out_8565439984289443181[145] = 0.0;
   out_8565439984289443181[146] = 0.0;
   out_8565439984289443181[147] = 0.0;
   out_8565439984289443181[148] = 0.0;
   out_8565439984289443181[149] = 0.0;
   out_8565439984289443181[150] = 0.0;
   out_8565439984289443181[151] = 0.0;
   out_8565439984289443181[152] = 1.0;
   out_8565439984289443181[153] = 0.0;
   out_8565439984289443181[154] = 0.0;
   out_8565439984289443181[155] = 0.0;
   out_8565439984289443181[156] = 0.0;
   out_8565439984289443181[157] = 0.0;
   out_8565439984289443181[158] = 0.0;
   out_8565439984289443181[159] = 0.0;
   out_8565439984289443181[160] = 0.0;
   out_8565439984289443181[161] = 0.0;
   out_8565439984289443181[162] = 0.0;
   out_8565439984289443181[163] = 0.0;
   out_8565439984289443181[164] = 0.0;
   out_8565439984289443181[165] = 0.0;
   out_8565439984289443181[166] = 0.0;
   out_8565439984289443181[167] = 0.0;
   out_8565439984289443181[168] = 0.0;
   out_8565439984289443181[169] = 0.0;
   out_8565439984289443181[170] = 0.0;
   out_8565439984289443181[171] = 1.0;
   out_8565439984289443181[172] = 0.0;
   out_8565439984289443181[173] = 0.0;
   out_8565439984289443181[174] = 0.0;
   out_8565439984289443181[175] = 0.0;
   out_8565439984289443181[176] = 0.0;
   out_8565439984289443181[177] = 0.0;
   out_8565439984289443181[178] = 0.0;
   out_8565439984289443181[179] = 0.0;
   out_8565439984289443181[180] = 0.0;
   out_8565439984289443181[181] = 0.0;
   out_8565439984289443181[182] = 0.0;
   out_8565439984289443181[183] = 0.0;
   out_8565439984289443181[184] = 0.0;
   out_8565439984289443181[185] = 0.0;
   out_8565439984289443181[186] = 0.0;
   out_8565439984289443181[187] = 0.0;
   out_8565439984289443181[188] = 0.0;
   out_8565439984289443181[189] = 0.0;
   out_8565439984289443181[190] = 1.0;
   out_8565439984289443181[191] = 0.0;
   out_8565439984289443181[192] = 0.0;
   out_8565439984289443181[193] = 0.0;
   out_8565439984289443181[194] = 0.0;
   out_8565439984289443181[195] = 0.0;
   out_8565439984289443181[196] = 0.0;
   out_8565439984289443181[197] = 0.0;
   out_8565439984289443181[198] = 0.0;
   out_8565439984289443181[199] = 0.0;
   out_8565439984289443181[200] = 0.0;
   out_8565439984289443181[201] = 0.0;
   out_8565439984289443181[202] = 0.0;
   out_8565439984289443181[203] = 0.0;
   out_8565439984289443181[204] = 0.0;
   out_8565439984289443181[205] = 0.0;
   out_8565439984289443181[206] = 0.0;
   out_8565439984289443181[207] = 0.0;
   out_8565439984289443181[208] = 0.0;
   out_8565439984289443181[209] = 1.0;
   out_8565439984289443181[210] = 0.0;
   out_8565439984289443181[211] = 0.0;
   out_8565439984289443181[212] = 0.0;
   out_8565439984289443181[213] = 0.0;
   out_8565439984289443181[214] = 0.0;
   out_8565439984289443181[215] = 0.0;
   out_8565439984289443181[216] = 0.0;
   out_8565439984289443181[217] = 0.0;
   out_8565439984289443181[218] = 0.0;
   out_8565439984289443181[219] = 0.0;
   out_8565439984289443181[220] = 0.0;
   out_8565439984289443181[221] = 0.0;
   out_8565439984289443181[222] = 0.0;
   out_8565439984289443181[223] = 0.0;
   out_8565439984289443181[224] = 0.0;
   out_8565439984289443181[225] = 0.0;
   out_8565439984289443181[226] = 0.0;
   out_8565439984289443181[227] = 0.0;
   out_8565439984289443181[228] = 1.0;
   out_8565439984289443181[229] = 0.0;
   out_8565439984289443181[230] = 0.0;
   out_8565439984289443181[231] = 0.0;
   out_8565439984289443181[232] = 0.0;
   out_8565439984289443181[233] = 0.0;
   out_8565439984289443181[234] = 0.0;
   out_8565439984289443181[235] = 0.0;
   out_8565439984289443181[236] = 0.0;
   out_8565439984289443181[237] = 0.0;
   out_8565439984289443181[238] = 0.0;
   out_8565439984289443181[239] = 0.0;
   out_8565439984289443181[240] = 0.0;
   out_8565439984289443181[241] = 0.0;
   out_8565439984289443181[242] = 0.0;
   out_8565439984289443181[243] = 0.0;
   out_8565439984289443181[244] = 0.0;
   out_8565439984289443181[245] = 0.0;
   out_8565439984289443181[246] = 0.0;
   out_8565439984289443181[247] = 1.0;
   out_8565439984289443181[248] = 0.0;
   out_8565439984289443181[249] = 0.0;
   out_8565439984289443181[250] = 0.0;
   out_8565439984289443181[251] = 0.0;
   out_8565439984289443181[252] = 0.0;
   out_8565439984289443181[253] = 0.0;
   out_8565439984289443181[254] = 0.0;
   out_8565439984289443181[255] = 0.0;
   out_8565439984289443181[256] = 0.0;
   out_8565439984289443181[257] = 0.0;
   out_8565439984289443181[258] = 0.0;
   out_8565439984289443181[259] = 0.0;
   out_8565439984289443181[260] = 0.0;
   out_8565439984289443181[261] = 0.0;
   out_8565439984289443181[262] = 0.0;
   out_8565439984289443181[263] = 0.0;
   out_8565439984289443181[264] = 0.0;
   out_8565439984289443181[265] = 0.0;
   out_8565439984289443181[266] = 1.0;
   out_8565439984289443181[267] = 0.0;
   out_8565439984289443181[268] = 0.0;
   out_8565439984289443181[269] = 0.0;
   out_8565439984289443181[270] = 0.0;
   out_8565439984289443181[271] = 0.0;
   out_8565439984289443181[272] = 0.0;
   out_8565439984289443181[273] = 0.0;
   out_8565439984289443181[274] = 0.0;
   out_8565439984289443181[275] = 0.0;
   out_8565439984289443181[276] = 0.0;
   out_8565439984289443181[277] = 0.0;
   out_8565439984289443181[278] = 0.0;
   out_8565439984289443181[279] = 0.0;
   out_8565439984289443181[280] = 0.0;
   out_8565439984289443181[281] = 0.0;
   out_8565439984289443181[282] = 0.0;
   out_8565439984289443181[283] = 0.0;
   out_8565439984289443181[284] = 0.0;
   out_8565439984289443181[285] = 1.0;
   out_8565439984289443181[286] = 0.0;
   out_8565439984289443181[287] = 0.0;
   out_8565439984289443181[288] = 0.0;
   out_8565439984289443181[289] = 0.0;
   out_8565439984289443181[290] = 0.0;
   out_8565439984289443181[291] = 0.0;
   out_8565439984289443181[292] = 0.0;
   out_8565439984289443181[293] = 0.0;
   out_8565439984289443181[294] = 0.0;
   out_8565439984289443181[295] = 0.0;
   out_8565439984289443181[296] = 0.0;
   out_8565439984289443181[297] = 0.0;
   out_8565439984289443181[298] = 0.0;
   out_8565439984289443181[299] = 0.0;
   out_8565439984289443181[300] = 0.0;
   out_8565439984289443181[301] = 0.0;
   out_8565439984289443181[302] = 0.0;
   out_8565439984289443181[303] = 0.0;
   out_8565439984289443181[304] = 1.0;
   out_8565439984289443181[305] = 0.0;
   out_8565439984289443181[306] = 0.0;
   out_8565439984289443181[307] = 0.0;
   out_8565439984289443181[308] = 0.0;
   out_8565439984289443181[309] = 0.0;
   out_8565439984289443181[310] = 0.0;
   out_8565439984289443181[311] = 0.0;
   out_8565439984289443181[312] = 0.0;
   out_8565439984289443181[313] = 0.0;
   out_8565439984289443181[314] = 0.0;
   out_8565439984289443181[315] = 0.0;
   out_8565439984289443181[316] = 0.0;
   out_8565439984289443181[317] = 0.0;
   out_8565439984289443181[318] = 0.0;
   out_8565439984289443181[319] = 0.0;
   out_8565439984289443181[320] = 0.0;
   out_8565439984289443181[321] = 0.0;
   out_8565439984289443181[322] = 0.0;
   out_8565439984289443181[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4570281413344882742) {
   out_4570281413344882742[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4570281413344882742[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4570281413344882742[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4570281413344882742[3] = dt*state[12] + state[3];
   out_4570281413344882742[4] = dt*state[13] + state[4];
   out_4570281413344882742[5] = dt*state[14] + state[5];
   out_4570281413344882742[6] = state[6];
   out_4570281413344882742[7] = state[7];
   out_4570281413344882742[8] = state[8];
   out_4570281413344882742[9] = state[9];
   out_4570281413344882742[10] = state[10];
   out_4570281413344882742[11] = state[11];
   out_4570281413344882742[12] = state[12];
   out_4570281413344882742[13] = state[13];
   out_4570281413344882742[14] = state[14];
   out_4570281413344882742[15] = state[15];
   out_4570281413344882742[16] = state[16];
   out_4570281413344882742[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3886745905040610692) {
   out_3886745905040610692[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3886745905040610692[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3886745905040610692[2] = 0;
   out_3886745905040610692[3] = 0;
   out_3886745905040610692[4] = 0;
   out_3886745905040610692[5] = 0;
   out_3886745905040610692[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3886745905040610692[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3886745905040610692[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3886745905040610692[9] = 0;
   out_3886745905040610692[10] = 0;
   out_3886745905040610692[11] = 0;
   out_3886745905040610692[12] = 0;
   out_3886745905040610692[13] = 0;
   out_3886745905040610692[14] = 0;
   out_3886745905040610692[15] = 0;
   out_3886745905040610692[16] = 0;
   out_3886745905040610692[17] = 0;
   out_3886745905040610692[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3886745905040610692[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3886745905040610692[20] = 0;
   out_3886745905040610692[21] = 0;
   out_3886745905040610692[22] = 0;
   out_3886745905040610692[23] = 0;
   out_3886745905040610692[24] = 0;
   out_3886745905040610692[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3886745905040610692[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3886745905040610692[27] = 0;
   out_3886745905040610692[28] = 0;
   out_3886745905040610692[29] = 0;
   out_3886745905040610692[30] = 0;
   out_3886745905040610692[31] = 0;
   out_3886745905040610692[32] = 0;
   out_3886745905040610692[33] = 0;
   out_3886745905040610692[34] = 0;
   out_3886745905040610692[35] = 0;
   out_3886745905040610692[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3886745905040610692[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3886745905040610692[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3886745905040610692[39] = 0;
   out_3886745905040610692[40] = 0;
   out_3886745905040610692[41] = 0;
   out_3886745905040610692[42] = 0;
   out_3886745905040610692[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3886745905040610692[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3886745905040610692[45] = 0;
   out_3886745905040610692[46] = 0;
   out_3886745905040610692[47] = 0;
   out_3886745905040610692[48] = 0;
   out_3886745905040610692[49] = 0;
   out_3886745905040610692[50] = 0;
   out_3886745905040610692[51] = 0;
   out_3886745905040610692[52] = 0;
   out_3886745905040610692[53] = 0;
   out_3886745905040610692[54] = 0;
   out_3886745905040610692[55] = 0;
   out_3886745905040610692[56] = 0;
   out_3886745905040610692[57] = 1;
   out_3886745905040610692[58] = 0;
   out_3886745905040610692[59] = 0;
   out_3886745905040610692[60] = 0;
   out_3886745905040610692[61] = 0;
   out_3886745905040610692[62] = 0;
   out_3886745905040610692[63] = 0;
   out_3886745905040610692[64] = 0;
   out_3886745905040610692[65] = 0;
   out_3886745905040610692[66] = dt;
   out_3886745905040610692[67] = 0;
   out_3886745905040610692[68] = 0;
   out_3886745905040610692[69] = 0;
   out_3886745905040610692[70] = 0;
   out_3886745905040610692[71] = 0;
   out_3886745905040610692[72] = 0;
   out_3886745905040610692[73] = 0;
   out_3886745905040610692[74] = 0;
   out_3886745905040610692[75] = 0;
   out_3886745905040610692[76] = 1;
   out_3886745905040610692[77] = 0;
   out_3886745905040610692[78] = 0;
   out_3886745905040610692[79] = 0;
   out_3886745905040610692[80] = 0;
   out_3886745905040610692[81] = 0;
   out_3886745905040610692[82] = 0;
   out_3886745905040610692[83] = 0;
   out_3886745905040610692[84] = 0;
   out_3886745905040610692[85] = dt;
   out_3886745905040610692[86] = 0;
   out_3886745905040610692[87] = 0;
   out_3886745905040610692[88] = 0;
   out_3886745905040610692[89] = 0;
   out_3886745905040610692[90] = 0;
   out_3886745905040610692[91] = 0;
   out_3886745905040610692[92] = 0;
   out_3886745905040610692[93] = 0;
   out_3886745905040610692[94] = 0;
   out_3886745905040610692[95] = 1;
   out_3886745905040610692[96] = 0;
   out_3886745905040610692[97] = 0;
   out_3886745905040610692[98] = 0;
   out_3886745905040610692[99] = 0;
   out_3886745905040610692[100] = 0;
   out_3886745905040610692[101] = 0;
   out_3886745905040610692[102] = 0;
   out_3886745905040610692[103] = 0;
   out_3886745905040610692[104] = dt;
   out_3886745905040610692[105] = 0;
   out_3886745905040610692[106] = 0;
   out_3886745905040610692[107] = 0;
   out_3886745905040610692[108] = 0;
   out_3886745905040610692[109] = 0;
   out_3886745905040610692[110] = 0;
   out_3886745905040610692[111] = 0;
   out_3886745905040610692[112] = 0;
   out_3886745905040610692[113] = 0;
   out_3886745905040610692[114] = 1;
   out_3886745905040610692[115] = 0;
   out_3886745905040610692[116] = 0;
   out_3886745905040610692[117] = 0;
   out_3886745905040610692[118] = 0;
   out_3886745905040610692[119] = 0;
   out_3886745905040610692[120] = 0;
   out_3886745905040610692[121] = 0;
   out_3886745905040610692[122] = 0;
   out_3886745905040610692[123] = 0;
   out_3886745905040610692[124] = 0;
   out_3886745905040610692[125] = 0;
   out_3886745905040610692[126] = 0;
   out_3886745905040610692[127] = 0;
   out_3886745905040610692[128] = 0;
   out_3886745905040610692[129] = 0;
   out_3886745905040610692[130] = 0;
   out_3886745905040610692[131] = 0;
   out_3886745905040610692[132] = 0;
   out_3886745905040610692[133] = 1;
   out_3886745905040610692[134] = 0;
   out_3886745905040610692[135] = 0;
   out_3886745905040610692[136] = 0;
   out_3886745905040610692[137] = 0;
   out_3886745905040610692[138] = 0;
   out_3886745905040610692[139] = 0;
   out_3886745905040610692[140] = 0;
   out_3886745905040610692[141] = 0;
   out_3886745905040610692[142] = 0;
   out_3886745905040610692[143] = 0;
   out_3886745905040610692[144] = 0;
   out_3886745905040610692[145] = 0;
   out_3886745905040610692[146] = 0;
   out_3886745905040610692[147] = 0;
   out_3886745905040610692[148] = 0;
   out_3886745905040610692[149] = 0;
   out_3886745905040610692[150] = 0;
   out_3886745905040610692[151] = 0;
   out_3886745905040610692[152] = 1;
   out_3886745905040610692[153] = 0;
   out_3886745905040610692[154] = 0;
   out_3886745905040610692[155] = 0;
   out_3886745905040610692[156] = 0;
   out_3886745905040610692[157] = 0;
   out_3886745905040610692[158] = 0;
   out_3886745905040610692[159] = 0;
   out_3886745905040610692[160] = 0;
   out_3886745905040610692[161] = 0;
   out_3886745905040610692[162] = 0;
   out_3886745905040610692[163] = 0;
   out_3886745905040610692[164] = 0;
   out_3886745905040610692[165] = 0;
   out_3886745905040610692[166] = 0;
   out_3886745905040610692[167] = 0;
   out_3886745905040610692[168] = 0;
   out_3886745905040610692[169] = 0;
   out_3886745905040610692[170] = 0;
   out_3886745905040610692[171] = 1;
   out_3886745905040610692[172] = 0;
   out_3886745905040610692[173] = 0;
   out_3886745905040610692[174] = 0;
   out_3886745905040610692[175] = 0;
   out_3886745905040610692[176] = 0;
   out_3886745905040610692[177] = 0;
   out_3886745905040610692[178] = 0;
   out_3886745905040610692[179] = 0;
   out_3886745905040610692[180] = 0;
   out_3886745905040610692[181] = 0;
   out_3886745905040610692[182] = 0;
   out_3886745905040610692[183] = 0;
   out_3886745905040610692[184] = 0;
   out_3886745905040610692[185] = 0;
   out_3886745905040610692[186] = 0;
   out_3886745905040610692[187] = 0;
   out_3886745905040610692[188] = 0;
   out_3886745905040610692[189] = 0;
   out_3886745905040610692[190] = 1;
   out_3886745905040610692[191] = 0;
   out_3886745905040610692[192] = 0;
   out_3886745905040610692[193] = 0;
   out_3886745905040610692[194] = 0;
   out_3886745905040610692[195] = 0;
   out_3886745905040610692[196] = 0;
   out_3886745905040610692[197] = 0;
   out_3886745905040610692[198] = 0;
   out_3886745905040610692[199] = 0;
   out_3886745905040610692[200] = 0;
   out_3886745905040610692[201] = 0;
   out_3886745905040610692[202] = 0;
   out_3886745905040610692[203] = 0;
   out_3886745905040610692[204] = 0;
   out_3886745905040610692[205] = 0;
   out_3886745905040610692[206] = 0;
   out_3886745905040610692[207] = 0;
   out_3886745905040610692[208] = 0;
   out_3886745905040610692[209] = 1;
   out_3886745905040610692[210] = 0;
   out_3886745905040610692[211] = 0;
   out_3886745905040610692[212] = 0;
   out_3886745905040610692[213] = 0;
   out_3886745905040610692[214] = 0;
   out_3886745905040610692[215] = 0;
   out_3886745905040610692[216] = 0;
   out_3886745905040610692[217] = 0;
   out_3886745905040610692[218] = 0;
   out_3886745905040610692[219] = 0;
   out_3886745905040610692[220] = 0;
   out_3886745905040610692[221] = 0;
   out_3886745905040610692[222] = 0;
   out_3886745905040610692[223] = 0;
   out_3886745905040610692[224] = 0;
   out_3886745905040610692[225] = 0;
   out_3886745905040610692[226] = 0;
   out_3886745905040610692[227] = 0;
   out_3886745905040610692[228] = 1;
   out_3886745905040610692[229] = 0;
   out_3886745905040610692[230] = 0;
   out_3886745905040610692[231] = 0;
   out_3886745905040610692[232] = 0;
   out_3886745905040610692[233] = 0;
   out_3886745905040610692[234] = 0;
   out_3886745905040610692[235] = 0;
   out_3886745905040610692[236] = 0;
   out_3886745905040610692[237] = 0;
   out_3886745905040610692[238] = 0;
   out_3886745905040610692[239] = 0;
   out_3886745905040610692[240] = 0;
   out_3886745905040610692[241] = 0;
   out_3886745905040610692[242] = 0;
   out_3886745905040610692[243] = 0;
   out_3886745905040610692[244] = 0;
   out_3886745905040610692[245] = 0;
   out_3886745905040610692[246] = 0;
   out_3886745905040610692[247] = 1;
   out_3886745905040610692[248] = 0;
   out_3886745905040610692[249] = 0;
   out_3886745905040610692[250] = 0;
   out_3886745905040610692[251] = 0;
   out_3886745905040610692[252] = 0;
   out_3886745905040610692[253] = 0;
   out_3886745905040610692[254] = 0;
   out_3886745905040610692[255] = 0;
   out_3886745905040610692[256] = 0;
   out_3886745905040610692[257] = 0;
   out_3886745905040610692[258] = 0;
   out_3886745905040610692[259] = 0;
   out_3886745905040610692[260] = 0;
   out_3886745905040610692[261] = 0;
   out_3886745905040610692[262] = 0;
   out_3886745905040610692[263] = 0;
   out_3886745905040610692[264] = 0;
   out_3886745905040610692[265] = 0;
   out_3886745905040610692[266] = 1;
   out_3886745905040610692[267] = 0;
   out_3886745905040610692[268] = 0;
   out_3886745905040610692[269] = 0;
   out_3886745905040610692[270] = 0;
   out_3886745905040610692[271] = 0;
   out_3886745905040610692[272] = 0;
   out_3886745905040610692[273] = 0;
   out_3886745905040610692[274] = 0;
   out_3886745905040610692[275] = 0;
   out_3886745905040610692[276] = 0;
   out_3886745905040610692[277] = 0;
   out_3886745905040610692[278] = 0;
   out_3886745905040610692[279] = 0;
   out_3886745905040610692[280] = 0;
   out_3886745905040610692[281] = 0;
   out_3886745905040610692[282] = 0;
   out_3886745905040610692[283] = 0;
   out_3886745905040610692[284] = 0;
   out_3886745905040610692[285] = 1;
   out_3886745905040610692[286] = 0;
   out_3886745905040610692[287] = 0;
   out_3886745905040610692[288] = 0;
   out_3886745905040610692[289] = 0;
   out_3886745905040610692[290] = 0;
   out_3886745905040610692[291] = 0;
   out_3886745905040610692[292] = 0;
   out_3886745905040610692[293] = 0;
   out_3886745905040610692[294] = 0;
   out_3886745905040610692[295] = 0;
   out_3886745905040610692[296] = 0;
   out_3886745905040610692[297] = 0;
   out_3886745905040610692[298] = 0;
   out_3886745905040610692[299] = 0;
   out_3886745905040610692[300] = 0;
   out_3886745905040610692[301] = 0;
   out_3886745905040610692[302] = 0;
   out_3886745905040610692[303] = 0;
   out_3886745905040610692[304] = 1;
   out_3886745905040610692[305] = 0;
   out_3886745905040610692[306] = 0;
   out_3886745905040610692[307] = 0;
   out_3886745905040610692[308] = 0;
   out_3886745905040610692[309] = 0;
   out_3886745905040610692[310] = 0;
   out_3886745905040610692[311] = 0;
   out_3886745905040610692[312] = 0;
   out_3886745905040610692[313] = 0;
   out_3886745905040610692[314] = 0;
   out_3886745905040610692[315] = 0;
   out_3886745905040610692[316] = 0;
   out_3886745905040610692[317] = 0;
   out_3886745905040610692[318] = 0;
   out_3886745905040610692[319] = 0;
   out_3886745905040610692[320] = 0;
   out_3886745905040610692[321] = 0;
   out_3886745905040610692[322] = 0;
   out_3886745905040610692[323] = 1;
}
void h_4(double *state, double *unused, double *out_1874588168802752989) {
   out_1874588168802752989[0] = state[6] + state[9];
   out_1874588168802752989[1] = state[7] + state[10];
   out_1874588168802752989[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6745741258383146320) {
   out_6745741258383146320[0] = 0;
   out_6745741258383146320[1] = 0;
   out_6745741258383146320[2] = 0;
   out_6745741258383146320[3] = 0;
   out_6745741258383146320[4] = 0;
   out_6745741258383146320[5] = 0;
   out_6745741258383146320[6] = 1;
   out_6745741258383146320[7] = 0;
   out_6745741258383146320[8] = 0;
   out_6745741258383146320[9] = 1;
   out_6745741258383146320[10] = 0;
   out_6745741258383146320[11] = 0;
   out_6745741258383146320[12] = 0;
   out_6745741258383146320[13] = 0;
   out_6745741258383146320[14] = 0;
   out_6745741258383146320[15] = 0;
   out_6745741258383146320[16] = 0;
   out_6745741258383146320[17] = 0;
   out_6745741258383146320[18] = 0;
   out_6745741258383146320[19] = 0;
   out_6745741258383146320[20] = 0;
   out_6745741258383146320[21] = 0;
   out_6745741258383146320[22] = 0;
   out_6745741258383146320[23] = 0;
   out_6745741258383146320[24] = 0;
   out_6745741258383146320[25] = 1;
   out_6745741258383146320[26] = 0;
   out_6745741258383146320[27] = 0;
   out_6745741258383146320[28] = 1;
   out_6745741258383146320[29] = 0;
   out_6745741258383146320[30] = 0;
   out_6745741258383146320[31] = 0;
   out_6745741258383146320[32] = 0;
   out_6745741258383146320[33] = 0;
   out_6745741258383146320[34] = 0;
   out_6745741258383146320[35] = 0;
   out_6745741258383146320[36] = 0;
   out_6745741258383146320[37] = 0;
   out_6745741258383146320[38] = 0;
   out_6745741258383146320[39] = 0;
   out_6745741258383146320[40] = 0;
   out_6745741258383146320[41] = 0;
   out_6745741258383146320[42] = 0;
   out_6745741258383146320[43] = 0;
   out_6745741258383146320[44] = 1;
   out_6745741258383146320[45] = 0;
   out_6745741258383146320[46] = 0;
   out_6745741258383146320[47] = 1;
   out_6745741258383146320[48] = 0;
   out_6745741258383146320[49] = 0;
   out_6745741258383146320[50] = 0;
   out_6745741258383146320[51] = 0;
   out_6745741258383146320[52] = 0;
   out_6745741258383146320[53] = 0;
}
void h_10(double *state, double *unused, double *out_904127136794521345) {
   out_904127136794521345[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_904127136794521345[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_904127136794521345[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_138933893569938853) {
   out_138933893569938853[0] = 0;
   out_138933893569938853[1] = 9.8100000000000005*cos(state[1]);
   out_138933893569938853[2] = 0;
   out_138933893569938853[3] = 0;
   out_138933893569938853[4] = -state[8];
   out_138933893569938853[5] = state[7];
   out_138933893569938853[6] = 0;
   out_138933893569938853[7] = state[5];
   out_138933893569938853[8] = -state[4];
   out_138933893569938853[9] = 0;
   out_138933893569938853[10] = 0;
   out_138933893569938853[11] = 0;
   out_138933893569938853[12] = 1;
   out_138933893569938853[13] = 0;
   out_138933893569938853[14] = 0;
   out_138933893569938853[15] = 1;
   out_138933893569938853[16] = 0;
   out_138933893569938853[17] = 0;
   out_138933893569938853[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_138933893569938853[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_138933893569938853[20] = 0;
   out_138933893569938853[21] = state[8];
   out_138933893569938853[22] = 0;
   out_138933893569938853[23] = -state[6];
   out_138933893569938853[24] = -state[5];
   out_138933893569938853[25] = 0;
   out_138933893569938853[26] = state[3];
   out_138933893569938853[27] = 0;
   out_138933893569938853[28] = 0;
   out_138933893569938853[29] = 0;
   out_138933893569938853[30] = 0;
   out_138933893569938853[31] = 1;
   out_138933893569938853[32] = 0;
   out_138933893569938853[33] = 0;
   out_138933893569938853[34] = 1;
   out_138933893569938853[35] = 0;
   out_138933893569938853[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_138933893569938853[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_138933893569938853[38] = 0;
   out_138933893569938853[39] = -state[7];
   out_138933893569938853[40] = state[6];
   out_138933893569938853[41] = 0;
   out_138933893569938853[42] = state[4];
   out_138933893569938853[43] = -state[3];
   out_138933893569938853[44] = 0;
   out_138933893569938853[45] = 0;
   out_138933893569938853[46] = 0;
   out_138933893569938853[47] = 0;
   out_138933893569938853[48] = 0;
   out_138933893569938853[49] = 0;
   out_138933893569938853[50] = 1;
   out_138933893569938853[51] = 0;
   out_138933893569938853[52] = 0;
   out_138933893569938853[53] = 1;
}
void h_13(double *state, double *unused, double *out_5867467314771514899) {
   out_5867467314771514899[0] = state[3];
   out_5867467314771514899[1] = state[4];
   out_5867467314771514899[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8488728989994072495) {
   out_8488728989994072495[0] = 0;
   out_8488728989994072495[1] = 0;
   out_8488728989994072495[2] = 0;
   out_8488728989994072495[3] = 1;
   out_8488728989994072495[4] = 0;
   out_8488728989994072495[5] = 0;
   out_8488728989994072495[6] = 0;
   out_8488728989994072495[7] = 0;
   out_8488728989994072495[8] = 0;
   out_8488728989994072495[9] = 0;
   out_8488728989994072495[10] = 0;
   out_8488728989994072495[11] = 0;
   out_8488728989994072495[12] = 0;
   out_8488728989994072495[13] = 0;
   out_8488728989994072495[14] = 0;
   out_8488728989994072495[15] = 0;
   out_8488728989994072495[16] = 0;
   out_8488728989994072495[17] = 0;
   out_8488728989994072495[18] = 0;
   out_8488728989994072495[19] = 0;
   out_8488728989994072495[20] = 0;
   out_8488728989994072495[21] = 0;
   out_8488728989994072495[22] = 1;
   out_8488728989994072495[23] = 0;
   out_8488728989994072495[24] = 0;
   out_8488728989994072495[25] = 0;
   out_8488728989994072495[26] = 0;
   out_8488728989994072495[27] = 0;
   out_8488728989994072495[28] = 0;
   out_8488728989994072495[29] = 0;
   out_8488728989994072495[30] = 0;
   out_8488728989994072495[31] = 0;
   out_8488728989994072495[32] = 0;
   out_8488728989994072495[33] = 0;
   out_8488728989994072495[34] = 0;
   out_8488728989994072495[35] = 0;
   out_8488728989994072495[36] = 0;
   out_8488728989994072495[37] = 0;
   out_8488728989994072495[38] = 0;
   out_8488728989994072495[39] = 0;
   out_8488728989994072495[40] = 0;
   out_8488728989994072495[41] = 1;
   out_8488728989994072495[42] = 0;
   out_8488728989994072495[43] = 0;
   out_8488728989994072495[44] = 0;
   out_8488728989994072495[45] = 0;
   out_8488728989994072495[46] = 0;
   out_8488728989994072495[47] = 0;
   out_8488728989994072495[48] = 0;
   out_8488728989994072495[49] = 0;
   out_8488728989994072495[50] = 0;
   out_8488728989994072495[51] = 0;
   out_8488728989994072495[52] = 0;
   out_8488728989994072495[53] = 0;
}
void h_14(double *state, double *unused, double *out_6345221351211143880) {
   out_6345221351211143880[0] = state[6];
   out_6345221351211143880[1] = state[7];
   out_6345221351211143880[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3662952826087774024) {
   out_3662952826087774024[0] = 0;
   out_3662952826087774024[1] = 0;
   out_3662952826087774024[2] = 0;
   out_3662952826087774024[3] = 0;
   out_3662952826087774024[4] = 0;
   out_3662952826087774024[5] = 0;
   out_3662952826087774024[6] = 1;
   out_3662952826087774024[7] = 0;
   out_3662952826087774024[8] = 0;
   out_3662952826087774024[9] = 0;
   out_3662952826087774024[10] = 0;
   out_3662952826087774024[11] = 0;
   out_3662952826087774024[12] = 0;
   out_3662952826087774024[13] = 0;
   out_3662952826087774024[14] = 0;
   out_3662952826087774024[15] = 0;
   out_3662952826087774024[16] = 0;
   out_3662952826087774024[17] = 0;
   out_3662952826087774024[18] = 0;
   out_3662952826087774024[19] = 0;
   out_3662952826087774024[20] = 0;
   out_3662952826087774024[21] = 0;
   out_3662952826087774024[22] = 0;
   out_3662952826087774024[23] = 0;
   out_3662952826087774024[24] = 0;
   out_3662952826087774024[25] = 1;
   out_3662952826087774024[26] = 0;
   out_3662952826087774024[27] = 0;
   out_3662952826087774024[28] = 0;
   out_3662952826087774024[29] = 0;
   out_3662952826087774024[30] = 0;
   out_3662952826087774024[31] = 0;
   out_3662952826087774024[32] = 0;
   out_3662952826087774024[33] = 0;
   out_3662952826087774024[34] = 0;
   out_3662952826087774024[35] = 0;
   out_3662952826087774024[36] = 0;
   out_3662952826087774024[37] = 0;
   out_3662952826087774024[38] = 0;
   out_3662952826087774024[39] = 0;
   out_3662952826087774024[40] = 0;
   out_3662952826087774024[41] = 0;
   out_3662952826087774024[42] = 0;
   out_3662952826087774024[43] = 0;
   out_3662952826087774024[44] = 1;
   out_3662952826087774024[45] = 0;
   out_3662952826087774024[46] = 0;
   out_3662952826087774024[47] = 0;
   out_3662952826087774024[48] = 0;
   out_3662952826087774024[49] = 0;
   out_3662952826087774024[50] = 0;
   out_3662952826087774024[51] = 0;
   out_3662952826087774024[52] = 0;
   out_3662952826087774024[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6408835186344628642) {
  err_fun(nom_x, delta_x, out_6408835186344628642);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4488020327469491521) {
  inv_err_fun(nom_x, true_x, out_4488020327469491521);
}
void pose_H_mod_fun(double *state, double *out_8565439984289443181) {
  H_mod_fun(state, out_8565439984289443181);
}
void pose_f_fun(double *state, double dt, double *out_4570281413344882742) {
  f_fun(state,  dt, out_4570281413344882742);
}
void pose_F_fun(double *state, double dt, double *out_3886745905040610692) {
  F_fun(state,  dt, out_3886745905040610692);
}
void pose_h_4(double *state, double *unused, double *out_1874588168802752989) {
  h_4(state, unused, out_1874588168802752989);
}
void pose_H_4(double *state, double *unused, double *out_6745741258383146320) {
  H_4(state, unused, out_6745741258383146320);
}
void pose_h_10(double *state, double *unused, double *out_904127136794521345) {
  h_10(state, unused, out_904127136794521345);
}
void pose_H_10(double *state, double *unused, double *out_138933893569938853) {
  H_10(state, unused, out_138933893569938853);
}
void pose_h_13(double *state, double *unused, double *out_5867467314771514899) {
  h_13(state, unused, out_5867467314771514899);
}
void pose_H_13(double *state, double *unused, double *out_8488728989994072495) {
  H_13(state, unused, out_8488728989994072495);
}
void pose_h_14(double *state, double *unused, double *out_6345221351211143880) {
  h_14(state, unused, out_6345221351211143880);
}
void pose_H_14(double *state, double *unused, double *out_3662952826087774024) {
  H_14(state, unused, out_3662952826087774024);
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
