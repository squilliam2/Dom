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
void err_fun(double *nom_x, double *delta_x, double *out_3697966966174848325) {
   out_3697966966174848325[0] = delta_x[0] + nom_x[0];
   out_3697966966174848325[1] = delta_x[1] + nom_x[1];
   out_3697966966174848325[2] = delta_x[2] + nom_x[2];
   out_3697966966174848325[3] = delta_x[3] + nom_x[3];
   out_3697966966174848325[4] = delta_x[4] + nom_x[4];
   out_3697966966174848325[5] = delta_x[5] + nom_x[5];
   out_3697966966174848325[6] = delta_x[6] + nom_x[6];
   out_3697966966174848325[7] = delta_x[7] + nom_x[7];
   out_3697966966174848325[8] = delta_x[8] + nom_x[8];
   out_3697966966174848325[9] = delta_x[9] + nom_x[9];
   out_3697966966174848325[10] = delta_x[10] + nom_x[10];
   out_3697966966174848325[11] = delta_x[11] + nom_x[11];
   out_3697966966174848325[12] = delta_x[12] + nom_x[12];
   out_3697966966174848325[13] = delta_x[13] + nom_x[13];
   out_3697966966174848325[14] = delta_x[14] + nom_x[14];
   out_3697966966174848325[15] = delta_x[15] + nom_x[15];
   out_3697966966174848325[16] = delta_x[16] + nom_x[16];
   out_3697966966174848325[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6121892126530152725) {
   out_6121892126530152725[0] = -nom_x[0] + true_x[0];
   out_6121892126530152725[1] = -nom_x[1] + true_x[1];
   out_6121892126530152725[2] = -nom_x[2] + true_x[2];
   out_6121892126530152725[3] = -nom_x[3] + true_x[3];
   out_6121892126530152725[4] = -nom_x[4] + true_x[4];
   out_6121892126530152725[5] = -nom_x[5] + true_x[5];
   out_6121892126530152725[6] = -nom_x[6] + true_x[6];
   out_6121892126530152725[7] = -nom_x[7] + true_x[7];
   out_6121892126530152725[8] = -nom_x[8] + true_x[8];
   out_6121892126530152725[9] = -nom_x[9] + true_x[9];
   out_6121892126530152725[10] = -nom_x[10] + true_x[10];
   out_6121892126530152725[11] = -nom_x[11] + true_x[11];
   out_6121892126530152725[12] = -nom_x[12] + true_x[12];
   out_6121892126530152725[13] = -nom_x[13] + true_x[13];
   out_6121892126530152725[14] = -nom_x[14] + true_x[14];
   out_6121892126530152725[15] = -nom_x[15] + true_x[15];
   out_6121892126530152725[16] = -nom_x[16] + true_x[16];
   out_6121892126530152725[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1116503706765055069) {
   out_1116503706765055069[0] = 1.0;
   out_1116503706765055069[1] = 0.0;
   out_1116503706765055069[2] = 0.0;
   out_1116503706765055069[3] = 0.0;
   out_1116503706765055069[4] = 0.0;
   out_1116503706765055069[5] = 0.0;
   out_1116503706765055069[6] = 0.0;
   out_1116503706765055069[7] = 0.0;
   out_1116503706765055069[8] = 0.0;
   out_1116503706765055069[9] = 0.0;
   out_1116503706765055069[10] = 0.0;
   out_1116503706765055069[11] = 0.0;
   out_1116503706765055069[12] = 0.0;
   out_1116503706765055069[13] = 0.0;
   out_1116503706765055069[14] = 0.0;
   out_1116503706765055069[15] = 0.0;
   out_1116503706765055069[16] = 0.0;
   out_1116503706765055069[17] = 0.0;
   out_1116503706765055069[18] = 0.0;
   out_1116503706765055069[19] = 1.0;
   out_1116503706765055069[20] = 0.0;
   out_1116503706765055069[21] = 0.0;
   out_1116503706765055069[22] = 0.0;
   out_1116503706765055069[23] = 0.0;
   out_1116503706765055069[24] = 0.0;
   out_1116503706765055069[25] = 0.0;
   out_1116503706765055069[26] = 0.0;
   out_1116503706765055069[27] = 0.0;
   out_1116503706765055069[28] = 0.0;
   out_1116503706765055069[29] = 0.0;
   out_1116503706765055069[30] = 0.0;
   out_1116503706765055069[31] = 0.0;
   out_1116503706765055069[32] = 0.0;
   out_1116503706765055069[33] = 0.0;
   out_1116503706765055069[34] = 0.0;
   out_1116503706765055069[35] = 0.0;
   out_1116503706765055069[36] = 0.0;
   out_1116503706765055069[37] = 0.0;
   out_1116503706765055069[38] = 1.0;
   out_1116503706765055069[39] = 0.0;
   out_1116503706765055069[40] = 0.0;
   out_1116503706765055069[41] = 0.0;
   out_1116503706765055069[42] = 0.0;
   out_1116503706765055069[43] = 0.0;
   out_1116503706765055069[44] = 0.0;
   out_1116503706765055069[45] = 0.0;
   out_1116503706765055069[46] = 0.0;
   out_1116503706765055069[47] = 0.0;
   out_1116503706765055069[48] = 0.0;
   out_1116503706765055069[49] = 0.0;
   out_1116503706765055069[50] = 0.0;
   out_1116503706765055069[51] = 0.0;
   out_1116503706765055069[52] = 0.0;
   out_1116503706765055069[53] = 0.0;
   out_1116503706765055069[54] = 0.0;
   out_1116503706765055069[55] = 0.0;
   out_1116503706765055069[56] = 0.0;
   out_1116503706765055069[57] = 1.0;
   out_1116503706765055069[58] = 0.0;
   out_1116503706765055069[59] = 0.0;
   out_1116503706765055069[60] = 0.0;
   out_1116503706765055069[61] = 0.0;
   out_1116503706765055069[62] = 0.0;
   out_1116503706765055069[63] = 0.0;
   out_1116503706765055069[64] = 0.0;
   out_1116503706765055069[65] = 0.0;
   out_1116503706765055069[66] = 0.0;
   out_1116503706765055069[67] = 0.0;
   out_1116503706765055069[68] = 0.0;
   out_1116503706765055069[69] = 0.0;
   out_1116503706765055069[70] = 0.0;
   out_1116503706765055069[71] = 0.0;
   out_1116503706765055069[72] = 0.0;
   out_1116503706765055069[73] = 0.0;
   out_1116503706765055069[74] = 0.0;
   out_1116503706765055069[75] = 0.0;
   out_1116503706765055069[76] = 1.0;
   out_1116503706765055069[77] = 0.0;
   out_1116503706765055069[78] = 0.0;
   out_1116503706765055069[79] = 0.0;
   out_1116503706765055069[80] = 0.0;
   out_1116503706765055069[81] = 0.0;
   out_1116503706765055069[82] = 0.0;
   out_1116503706765055069[83] = 0.0;
   out_1116503706765055069[84] = 0.0;
   out_1116503706765055069[85] = 0.0;
   out_1116503706765055069[86] = 0.0;
   out_1116503706765055069[87] = 0.0;
   out_1116503706765055069[88] = 0.0;
   out_1116503706765055069[89] = 0.0;
   out_1116503706765055069[90] = 0.0;
   out_1116503706765055069[91] = 0.0;
   out_1116503706765055069[92] = 0.0;
   out_1116503706765055069[93] = 0.0;
   out_1116503706765055069[94] = 0.0;
   out_1116503706765055069[95] = 1.0;
   out_1116503706765055069[96] = 0.0;
   out_1116503706765055069[97] = 0.0;
   out_1116503706765055069[98] = 0.0;
   out_1116503706765055069[99] = 0.0;
   out_1116503706765055069[100] = 0.0;
   out_1116503706765055069[101] = 0.0;
   out_1116503706765055069[102] = 0.0;
   out_1116503706765055069[103] = 0.0;
   out_1116503706765055069[104] = 0.0;
   out_1116503706765055069[105] = 0.0;
   out_1116503706765055069[106] = 0.0;
   out_1116503706765055069[107] = 0.0;
   out_1116503706765055069[108] = 0.0;
   out_1116503706765055069[109] = 0.0;
   out_1116503706765055069[110] = 0.0;
   out_1116503706765055069[111] = 0.0;
   out_1116503706765055069[112] = 0.0;
   out_1116503706765055069[113] = 0.0;
   out_1116503706765055069[114] = 1.0;
   out_1116503706765055069[115] = 0.0;
   out_1116503706765055069[116] = 0.0;
   out_1116503706765055069[117] = 0.0;
   out_1116503706765055069[118] = 0.0;
   out_1116503706765055069[119] = 0.0;
   out_1116503706765055069[120] = 0.0;
   out_1116503706765055069[121] = 0.0;
   out_1116503706765055069[122] = 0.0;
   out_1116503706765055069[123] = 0.0;
   out_1116503706765055069[124] = 0.0;
   out_1116503706765055069[125] = 0.0;
   out_1116503706765055069[126] = 0.0;
   out_1116503706765055069[127] = 0.0;
   out_1116503706765055069[128] = 0.0;
   out_1116503706765055069[129] = 0.0;
   out_1116503706765055069[130] = 0.0;
   out_1116503706765055069[131] = 0.0;
   out_1116503706765055069[132] = 0.0;
   out_1116503706765055069[133] = 1.0;
   out_1116503706765055069[134] = 0.0;
   out_1116503706765055069[135] = 0.0;
   out_1116503706765055069[136] = 0.0;
   out_1116503706765055069[137] = 0.0;
   out_1116503706765055069[138] = 0.0;
   out_1116503706765055069[139] = 0.0;
   out_1116503706765055069[140] = 0.0;
   out_1116503706765055069[141] = 0.0;
   out_1116503706765055069[142] = 0.0;
   out_1116503706765055069[143] = 0.0;
   out_1116503706765055069[144] = 0.0;
   out_1116503706765055069[145] = 0.0;
   out_1116503706765055069[146] = 0.0;
   out_1116503706765055069[147] = 0.0;
   out_1116503706765055069[148] = 0.0;
   out_1116503706765055069[149] = 0.0;
   out_1116503706765055069[150] = 0.0;
   out_1116503706765055069[151] = 0.0;
   out_1116503706765055069[152] = 1.0;
   out_1116503706765055069[153] = 0.0;
   out_1116503706765055069[154] = 0.0;
   out_1116503706765055069[155] = 0.0;
   out_1116503706765055069[156] = 0.0;
   out_1116503706765055069[157] = 0.0;
   out_1116503706765055069[158] = 0.0;
   out_1116503706765055069[159] = 0.0;
   out_1116503706765055069[160] = 0.0;
   out_1116503706765055069[161] = 0.0;
   out_1116503706765055069[162] = 0.0;
   out_1116503706765055069[163] = 0.0;
   out_1116503706765055069[164] = 0.0;
   out_1116503706765055069[165] = 0.0;
   out_1116503706765055069[166] = 0.0;
   out_1116503706765055069[167] = 0.0;
   out_1116503706765055069[168] = 0.0;
   out_1116503706765055069[169] = 0.0;
   out_1116503706765055069[170] = 0.0;
   out_1116503706765055069[171] = 1.0;
   out_1116503706765055069[172] = 0.0;
   out_1116503706765055069[173] = 0.0;
   out_1116503706765055069[174] = 0.0;
   out_1116503706765055069[175] = 0.0;
   out_1116503706765055069[176] = 0.0;
   out_1116503706765055069[177] = 0.0;
   out_1116503706765055069[178] = 0.0;
   out_1116503706765055069[179] = 0.0;
   out_1116503706765055069[180] = 0.0;
   out_1116503706765055069[181] = 0.0;
   out_1116503706765055069[182] = 0.0;
   out_1116503706765055069[183] = 0.0;
   out_1116503706765055069[184] = 0.0;
   out_1116503706765055069[185] = 0.0;
   out_1116503706765055069[186] = 0.0;
   out_1116503706765055069[187] = 0.0;
   out_1116503706765055069[188] = 0.0;
   out_1116503706765055069[189] = 0.0;
   out_1116503706765055069[190] = 1.0;
   out_1116503706765055069[191] = 0.0;
   out_1116503706765055069[192] = 0.0;
   out_1116503706765055069[193] = 0.0;
   out_1116503706765055069[194] = 0.0;
   out_1116503706765055069[195] = 0.0;
   out_1116503706765055069[196] = 0.0;
   out_1116503706765055069[197] = 0.0;
   out_1116503706765055069[198] = 0.0;
   out_1116503706765055069[199] = 0.0;
   out_1116503706765055069[200] = 0.0;
   out_1116503706765055069[201] = 0.0;
   out_1116503706765055069[202] = 0.0;
   out_1116503706765055069[203] = 0.0;
   out_1116503706765055069[204] = 0.0;
   out_1116503706765055069[205] = 0.0;
   out_1116503706765055069[206] = 0.0;
   out_1116503706765055069[207] = 0.0;
   out_1116503706765055069[208] = 0.0;
   out_1116503706765055069[209] = 1.0;
   out_1116503706765055069[210] = 0.0;
   out_1116503706765055069[211] = 0.0;
   out_1116503706765055069[212] = 0.0;
   out_1116503706765055069[213] = 0.0;
   out_1116503706765055069[214] = 0.0;
   out_1116503706765055069[215] = 0.0;
   out_1116503706765055069[216] = 0.0;
   out_1116503706765055069[217] = 0.0;
   out_1116503706765055069[218] = 0.0;
   out_1116503706765055069[219] = 0.0;
   out_1116503706765055069[220] = 0.0;
   out_1116503706765055069[221] = 0.0;
   out_1116503706765055069[222] = 0.0;
   out_1116503706765055069[223] = 0.0;
   out_1116503706765055069[224] = 0.0;
   out_1116503706765055069[225] = 0.0;
   out_1116503706765055069[226] = 0.0;
   out_1116503706765055069[227] = 0.0;
   out_1116503706765055069[228] = 1.0;
   out_1116503706765055069[229] = 0.0;
   out_1116503706765055069[230] = 0.0;
   out_1116503706765055069[231] = 0.0;
   out_1116503706765055069[232] = 0.0;
   out_1116503706765055069[233] = 0.0;
   out_1116503706765055069[234] = 0.0;
   out_1116503706765055069[235] = 0.0;
   out_1116503706765055069[236] = 0.0;
   out_1116503706765055069[237] = 0.0;
   out_1116503706765055069[238] = 0.0;
   out_1116503706765055069[239] = 0.0;
   out_1116503706765055069[240] = 0.0;
   out_1116503706765055069[241] = 0.0;
   out_1116503706765055069[242] = 0.0;
   out_1116503706765055069[243] = 0.0;
   out_1116503706765055069[244] = 0.0;
   out_1116503706765055069[245] = 0.0;
   out_1116503706765055069[246] = 0.0;
   out_1116503706765055069[247] = 1.0;
   out_1116503706765055069[248] = 0.0;
   out_1116503706765055069[249] = 0.0;
   out_1116503706765055069[250] = 0.0;
   out_1116503706765055069[251] = 0.0;
   out_1116503706765055069[252] = 0.0;
   out_1116503706765055069[253] = 0.0;
   out_1116503706765055069[254] = 0.0;
   out_1116503706765055069[255] = 0.0;
   out_1116503706765055069[256] = 0.0;
   out_1116503706765055069[257] = 0.0;
   out_1116503706765055069[258] = 0.0;
   out_1116503706765055069[259] = 0.0;
   out_1116503706765055069[260] = 0.0;
   out_1116503706765055069[261] = 0.0;
   out_1116503706765055069[262] = 0.0;
   out_1116503706765055069[263] = 0.0;
   out_1116503706765055069[264] = 0.0;
   out_1116503706765055069[265] = 0.0;
   out_1116503706765055069[266] = 1.0;
   out_1116503706765055069[267] = 0.0;
   out_1116503706765055069[268] = 0.0;
   out_1116503706765055069[269] = 0.0;
   out_1116503706765055069[270] = 0.0;
   out_1116503706765055069[271] = 0.0;
   out_1116503706765055069[272] = 0.0;
   out_1116503706765055069[273] = 0.0;
   out_1116503706765055069[274] = 0.0;
   out_1116503706765055069[275] = 0.0;
   out_1116503706765055069[276] = 0.0;
   out_1116503706765055069[277] = 0.0;
   out_1116503706765055069[278] = 0.0;
   out_1116503706765055069[279] = 0.0;
   out_1116503706765055069[280] = 0.0;
   out_1116503706765055069[281] = 0.0;
   out_1116503706765055069[282] = 0.0;
   out_1116503706765055069[283] = 0.0;
   out_1116503706765055069[284] = 0.0;
   out_1116503706765055069[285] = 1.0;
   out_1116503706765055069[286] = 0.0;
   out_1116503706765055069[287] = 0.0;
   out_1116503706765055069[288] = 0.0;
   out_1116503706765055069[289] = 0.0;
   out_1116503706765055069[290] = 0.0;
   out_1116503706765055069[291] = 0.0;
   out_1116503706765055069[292] = 0.0;
   out_1116503706765055069[293] = 0.0;
   out_1116503706765055069[294] = 0.0;
   out_1116503706765055069[295] = 0.0;
   out_1116503706765055069[296] = 0.0;
   out_1116503706765055069[297] = 0.0;
   out_1116503706765055069[298] = 0.0;
   out_1116503706765055069[299] = 0.0;
   out_1116503706765055069[300] = 0.0;
   out_1116503706765055069[301] = 0.0;
   out_1116503706765055069[302] = 0.0;
   out_1116503706765055069[303] = 0.0;
   out_1116503706765055069[304] = 1.0;
   out_1116503706765055069[305] = 0.0;
   out_1116503706765055069[306] = 0.0;
   out_1116503706765055069[307] = 0.0;
   out_1116503706765055069[308] = 0.0;
   out_1116503706765055069[309] = 0.0;
   out_1116503706765055069[310] = 0.0;
   out_1116503706765055069[311] = 0.0;
   out_1116503706765055069[312] = 0.0;
   out_1116503706765055069[313] = 0.0;
   out_1116503706765055069[314] = 0.0;
   out_1116503706765055069[315] = 0.0;
   out_1116503706765055069[316] = 0.0;
   out_1116503706765055069[317] = 0.0;
   out_1116503706765055069[318] = 0.0;
   out_1116503706765055069[319] = 0.0;
   out_1116503706765055069[320] = 0.0;
   out_1116503706765055069[321] = 0.0;
   out_1116503706765055069[322] = 0.0;
   out_1116503706765055069[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2317659772838150308) {
   out_2317659772838150308[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2317659772838150308[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2317659772838150308[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2317659772838150308[3] = dt*state[12] + state[3];
   out_2317659772838150308[4] = dt*state[13] + state[4];
   out_2317659772838150308[5] = dt*state[14] + state[5];
   out_2317659772838150308[6] = state[6];
   out_2317659772838150308[7] = state[7];
   out_2317659772838150308[8] = state[8];
   out_2317659772838150308[9] = state[9];
   out_2317659772838150308[10] = state[10];
   out_2317659772838150308[11] = state[11];
   out_2317659772838150308[12] = state[12];
   out_2317659772838150308[13] = state[13];
   out_2317659772838150308[14] = state[14];
   out_2317659772838150308[15] = state[15];
   out_2317659772838150308[16] = state[16];
   out_2317659772838150308[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6164130103148092652) {
   out_6164130103148092652[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6164130103148092652[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6164130103148092652[2] = 0;
   out_6164130103148092652[3] = 0;
   out_6164130103148092652[4] = 0;
   out_6164130103148092652[5] = 0;
   out_6164130103148092652[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6164130103148092652[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6164130103148092652[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6164130103148092652[9] = 0;
   out_6164130103148092652[10] = 0;
   out_6164130103148092652[11] = 0;
   out_6164130103148092652[12] = 0;
   out_6164130103148092652[13] = 0;
   out_6164130103148092652[14] = 0;
   out_6164130103148092652[15] = 0;
   out_6164130103148092652[16] = 0;
   out_6164130103148092652[17] = 0;
   out_6164130103148092652[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6164130103148092652[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6164130103148092652[20] = 0;
   out_6164130103148092652[21] = 0;
   out_6164130103148092652[22] = 0;
   out_6164130103148092652[23] = 0;
   out_6164130103148092652[24] = 0;
   out_6164130103148092652[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6164130103148092652[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6164130103148092652[27] = 0;
   out_6164130103148092652[28] = 0;
   out_6164130103148092652[29] = 0;
   out_6164130103148092652[30] = 0;
   out_6164130103148092652[31] = 0;
   out_6164130103148092652[32] = 0;
   out_6164130103148092652[33] = 0;
   out_6164130103148092652[34] = 0;
   out_6164130103148092652[35] = 0;
   out_6164130103148092652[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6164130103148092652[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6164130103148092652[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6164130103148092652[39] = 0;
   out_6164130103148092652[40] = 0;
   out_6164130103148092652[41] = 0;
   out_6164130103148092652[42] = 0;
   out_6164130103148092652[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6164130103148092652[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6164130103148092652[45] = 0;
   out_6164130103148092652[46] = 0;
   out_6164130103148092652[47] = 0;
   out_6164130103148092652[48] = 0;
   out_6164130103148092652[49] = 0;
   out_6164130103148092652[50] = 0;
   out_6164130103148092652[51] = 0;
   out_6164130103148092652[52] = 0;
   out_6164130103148092652[53] = 0;
   out_6164130103148092652[54] = 0;
   out_6164130103148092652[55] = 0;
   out_6164130103148092652[56] = 0;
   out_6164130103148092652[57] = 1;
   out_6164130103148092652[58] = 0;
   out_6164130103148092652[59] = 0;
   out_6164130103148092652[60] = 0;
   out_6164130103148092652[61] = 0;
   out_6164130103148092652[62] = 0;
   out_6164130103148092652[63] = 0;
   out_6164130103148092652[64] = 0;
   out_6164130103148092652[65] = 0;
   out_6164130103148092652[66] = dt;
   out_6164130103148092652[67] = 0;
   out_6164130103148092652[68] = 0;
   out_6164130103148092652[69] = 0;
   out_6164130103148092652[70] = 0;
   out_6164130103148092652[71] = 0;
   out_6164130103148092652[72] = 0;
   out_6164130103148092652[73] = 0;
   out_6164130103148092652[74] = 0;
   out_6164130103148092652[75] = 0;
   out_6164130103148092652[76] = 1;
   out_6164130103148092652[77] = 0;
   out_6164130103148092652[78] = 0;
   out_6164130103148092652[79] = 0;
   out_6164130103148092652[80] = 0;
   out_6164130103148092652[81] = 0;
   out_6164130103148092652[82] = 0;
   out_6164130103148092652[83] = 0;
   out_6164130103148092652[84] = 0;
   out_6164130103148092652[85] = dt;
   out_6164130103148092652[86] = 0;
   out_6164130103148092652[87] = 0;
   out_6164130103148092652[88] = 0;
   out_6164130103148092652[89] = 0;
   out_6164130103148092652[90] = 0;
   out_6164130103148092652[91] = 0;
   out_6164130103148092652[92] = 0;
   out_6164130103148092652[93] = 0;
   out_6164130103148092652[94] = 0;
   out_6164130103148092652[95] = 1;
   out_6164130103148092652[96] = 0;
   out_6164130103148092652[97] = 0;
   out_6164130103148092652[98] = 0;
   out_6164130103148092652[99] = 0;
   out_6164130103148092652[100] = 0;
   out_6164130103148092652[101] = 0;
   out_6164130103148092652[102] = 0;
   out_6164130103148092652[103] = 0;
   out_6164130103148092652[104] = dt;
   out_6164130103148092652[105] = 0;
   out_6164130103148092652[106] = 0;
   out_6164130103148092652[107] = 0;
   out_6164130103148092652[108] = 0;
   out_6164130103148092652[109] = 0;
   out_6164130103148092652[110] = 0;
   out_6164130103148092652[111] = 0;
   out_6164130103148092652[112] = 0;
   out_6164130103148092652[113] = 0;
   out_6164130103148092652[114] = 1;
   out_6164130103148092652[115] = 0;
   out_6164130103148092652[116] = 0;
   out_6164130103148092652[117] = 0;
   out_6164130103148092652[118] = 0;
   out_6164130103148092652[119] = 0;
   out_6164130103148092652[120] = 0;
   out_6164130103148092652[121] = 0;
   out_6164130103148092652[122] = 0;
   out_6164130103148092652[123] = 0;
   out_6164130103148092652[124] = 0;
   out_6164130103148092652[125] = 0;
   out_6164130103148092652[126] = 0;
   out_6164130103148092652[127] = 0;
   out_6164130103148092652[128] = 0;
   out_6164130103148092652[129] = 0;
   out_6164130103148092652[130] = 0;
   out_6164130103148092652[131] = 0;
   out_6164130103148092652[132] = 0;
   out_6164130103148092652[133] = 1;
   out_6164130103148092652[134] = 0;
   out_6164130103148092652[135] = 0;
   out_6164130103148092652[136] = 0;
   out_6164130103148092652[137] = 0;
   out_6164130103148092652[138] = 0;
   out_6164130103148092652[139] = 0;
   out_6164130103148092652[140] = 0;
   out_6164130103148092652[141] = 0;
   out_6164130103148092652[142] = 0;
   out_6164130103148092652[143] = 0;
   out_6164130103148092652[144] = 0;
   out_6164130103148092652[145] = 0;
   out_6164130103148092652[146] = 0;
   out_6164130103148092652[147] = 0;
   out_6164130103148092652[148] = 0;
   out_6164130103148092652[149] = 0;
   out_6164130103148092652[150] = 0;
   out_6164130103148092652[151] = 0;
   out_6164130103148092652[152] = 1;
   out_6164130103148092652[153] = 0;
   out_6164130103148092652[154] = 0;
   out_6164130103148092652[155] = 0;
   out_6164130103148092652[156] = 0;
   out_6164130103148092652[157] = 0;
   out_6164130103148092652[158] = 0;
   out_6164130103148092652[159] = 0;
   out_6164130103148092652[160] = 0;
   out_6164130103148092652[161] = 0;
   out_6164130103148092652[162] = 0;
   out_6164130103148092652[163] = 0;
   out_6164130103148092652[164] = 0;
   out_6164130103148092652[165] = 0;
   out_6164130103148092652[166] = 0;
   out_6164130103148092652[167] = 0;
   out_6164130103148092652[168] = 0;
   out_6164130103148092652[169] = 0;
   out_6164130103148092652[170] = 0;
   out_6164130103148092652[171] = 1;
   out_6164130103148092652[172] = 0;
   out_6164130103148092652[173] = 0;
   out_6164130103148092652[174] = 0;
   out_6164130103148092652[175] = 0;
   out_6164130103148092652[176] = 0;
   out_6164130103148092652[177] = 0;
   out_6164130103148092652[178] = 0;
   out_6164130103148092652[179] = 0;
   out_6164130103148092652[180] = 0;
   out_6164130103148092652[181] = 0;
   out_6164130103148092652[182] = 0;
   out_6164130103148092652[183] = 0;
   out_6164130103148092652[184] = 0;
   out_6164130103148092652[185] = 0;
   out_6164130103148092652[186] = 0;
   out_6164130103148092652[187] = 0;
   out_6164130103148092652[188] = 0;
   out_6164130103148092652[189] = 0;
   out_6164130103148092652[190] = 1;
   out_6164130103148092652[191] = 0;
   out_6164130103148092652[192] = 0;
   out_6164130103148092652[193] = 0;
   out_6164130103148092652[194] = 0;
   out_6164130103148092652[195] = 0;
   out_6164130103148092652[196] = 0;
   out_6164130103148092652[197] = 0;
   out_6164130103148092652[198] = 0;
   out_6164130103148092652[199] = 0;
   out_6164130103148092652[200] = 0;
   out_6164130103148092652[201] = 0;
   out_6164130103148092652[202] = 0;
   out_6164130103148092652[203] = 0;
   out_6164130103148092652[204] = 0;
   out_6164130103148092652[205] = 0;
   out_6164130103148092652[206] = 0;
   out_6164130103148092652[207] = 0;
   out_6164130103148092652[208] = 0;
   out_6164130103148092652[209] = 1;
   out_6164130103148092652[210] = 0;
   out_6164130103148092652[211] = 0;
   out_6164130103148092652[212] = 0;
   out_6164130103148092652[213] = 0;
   out_6164130103148092652[214] = 0;
   out_6164130103148092652[215] = 0;
   out_6164130103148092652[216] = 0;
   out_6164130103148092652[217] = 0;
   out_6164130103148092652[218] = 0;
   out_6164130103148092652[219] = 0;
   out_6164130103148092652[220] = 0;
   out_6164130103148092652[221] = 0;
   out_6164130103148092652[222] = 0;
   out_6164130103148092652[223] = 0;
   out_6164130103148092652[224] = 0;
   out_6164130103148092652[225] = 0;
   out_6164130103148092652[226] = 0;
   out_6164130103148092652[227] = 0;
   out_6164130103148092652[228] = 1;
   out_6164130103148092652[229] = 0;
   out_6164130103148092652[230] = 0;
   out_6164130103148092652[231] = 0;
   out_6164130103148092652[232] = 0;
   out_6164130103148092652[233] = 0;
   out_6164130103148092652[234] = 0;
   out_6164130103148092652[235] = 0;
   out_6164130103148092652[236] = 0;
   out_6164130103148092652[237] = 0;
   out_6164130103148092652[238] = 0;
   out_6164130103148092652[239] = 0;
   out_6164130103148092652[240] = 0;
   out_6164130103148092652[241] = 0;
   out_6164130103148092652[242] = 0;
   out_6164130103148092652[243] = 0;
   out_6164130103148092652[244] = 0;
   out_6164130103148092652[245] = 0;
   out_6164130103148092652[246] = 0;
   out_6164130103148092652[247] = 1;
   out_6164130103148092652[248] = 0;
   out_6164130103148092652[249] = 0;
   out_6164130103148092652[250] = 0;
   out_6164130103148092652[251] = 0;
   out_6164130103148092652[252] = 0;
   out_6164130103148092652[253] = 0;
   out_6164130103148092652[254] = 0;
   out_6164130103148092652[255] = 0;
   out_6164130103148092652[256] = 0;
   out_6164130103148092652[257] = 0;
   out_6164130103148092652[258] = 0;
   out_6164130103148092652[259] = 0;
   out_6164130103148092652[260] = 0;
   out_6164130103148092652[261] = 0;
   out_6164130103148092652[262] = 0;
   out_6164130103148092652[263] = 0;
   out_6164130103148092652[264] = 0;
   out_6164130103148092652[265] = 0;
   out_6164130103148092652[266] = 1;
   out_6164130103148092652[267] = 0;
   out_6164130103148092652[268] = 0;
   out_6164130103148092652[269] = 0;
   out_6164130103148092652[270] = 0;
   out_6164130103148092652[271] = 0;
   out_6164130103148092652[272] = 0;
   out_6164130103148092652[273] = 0;
   out_6164130103148092652[274] = 0;
   out_6164130103148092652[275] = 0;
   out_6164130103148092652[276] = 0;
   out_6164130103148092652[277] = 0;
   out_6164130103148092652[278] = 0;
   out_6164130103148092652[279] = 0;
   out_6164130103148092652[280] = 0;
   out_6164130103148092652[281] = 0;
   out_6164130103148092652[282] = 0;
   out_6164130103148092652[283] = 0;
   out_6164130103148092652[284] = 0;
   out_6164130103148092652[285] = 1;
   out_6164130103148092652[286] = 0;
   out_6164130103148092652[287] = 0;
   out_6164130103148092652[288] = 0;
   out_6164130103148092652[289] = 0;
   out_6164130103148092652[290] = 0;
   out_6164130103148092652[291] = 0;
   out_6164130103148092652[292] = 0;
   out_6164130103148092652[293] = 0;
   out_6164130103148092652[294] = 0;
   out_6164130103148092652[295] = 0;
   out_6164130103148092652[296] = 0;
   out_6164130103148092652[297] = 0;
   out_6164130103148092652[298] = 0;
   out_6164130103148092652[299] = 0;
   out_6164130103148092652[300] = 0;
   out_6164130103148092652[301] = 0;
   out_6164130103148092652[302] = 0;
   out_6164130103148092652[303] = 0;
   out_6164130103148092652[304] = 1;
   out_6164130103148092652[305] = 0;
   out_6164130103148092652[306] = 0;
   out_6164130103148092652[307] = 0;
   out_6164130103148092652[308] = 0;
   out_6164130103148092652[309] = 0;
   out_6164130103148092652[310] = 0;
   out_6164130103148092652[311] = 0;
   out_6164130103148092652[312] = 0;
   out_6164130103148092652[313] = 0;
   out_6164130103148092652[314] = 0;
   out_6164130103148092652[315] = 0;
   out_6164130103148092652[316] = 0;
   out_6164130103148092652[317] = 0;
   out_6164130103148092652[318] = 0;
   out_6164130103148092652[319] = 0;
   out_6164130103148092652[320] = 0;
   out_6164130103148092652[321] = 0;
   out_6164130103148092652[322] = 0;
   out_6164130103148092652[323] = 1;
}
void h_4(double *state, double *unused, double *out_2811574505702470007) {
   out_2811574505702470007[0] = state[6] + state[9];
   out_2811574505702470007[1] = state[7] + state[10];
   out_2811574505702470007[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8385878700886675205) {
   out_8385878700886675205[0] = 0;
   out_8385878700886675205[1] = 0;
   out_8385878700886675205[2] = 0;
   out_8385878700886675205[3] = 0;
   out_8385878700886675205[4] = 0;
   out_8385878700886675205[5] = 0;
   out_8385878700886675205[6] = 1;
   out_8385878700886675205[7] = 0;
   out_8385878700886675205[8] = 0;
   out_8385878700886675205[9] = 1;
   out_8385878700886675205[10] = 0;
   out_8385878700886675205[11] = 0;
   out_8385878700886675205[12] = 0;
   out_8385878700886675205[13] = 0;
   out_8385878700886675205[14] = 0;
   out_8385878700886675205[15] = 0;
   out_8385878700886675205[16] = 0;
   out_8385878700886675205[17] = 0;
   out_8385878700886675205[18] = 0;
   out_8385878700886675205[19] = 0;
   out_8385878700886675205[20] = 0;
   out_8385878700886675205[21] = 0;
   out_8385878700886675205[22] = 0;
   out_8385878700886675205[23] = 0;
   out_8385878700886675205[24] = 0;
   out_8385878700886675205[25] = 1;
   out_8385878700886675205[26] = 0;
   out_8385878700886675205[27] = 0;
   out_8385878700886675205[28] = 1;
   out_8385878700886675205[29] = 0;
   out_8385878700886675205[30] = 0;
   out_8385878700886675205[31] = 0;
   out_8385878700886675205[32] = 0;
   out_8385878700886675205[33] = 0;
   out_8385878700886675205[34] = 0;
   out_8385878700886675205[35] = 0;
   out_8385878700886675205[36] = 0;
   out_8385878700886675205[37] = 0;
   out_8385878700886675205[38] = 0;
   out_8385878700886675205[39] = 0;
   out_8385878700886675205[40] = 0;
   out_8385878700886675205[41] = 0;
   out_8385878700886675205[42] = 0;
   out_8385878700886675205[43] = 0;
   out_8385878700886675205[44] = 1;
   out_8385878700886675205[45] = 0;
   out_8385878700886675205[46] = 0;
   out_8385878700886675205[47] = 1;
   out_8385878700886675205[48] = 0;
   out_8385878700886675205[49] = 0;
   out_8385878700886675205[50] = 0;
   out_8385878700886675205[51] = 0;
   out_8385878700886675205[52] = 0;
   out_8385878700886675205[53] = 0;
}
void h_10(double *state, double *unused, double *out_5534858922172779190) {
   out_5534858922172779190[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5534858922172779190[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5534858922172779190[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3607384786905077425) {
   out_3607384786905077425[0] = 0;
   out_3607384786905077425[1] = 9.8100000000000005*cos(state[1]);
   out_3607384786905077425[2] = 0;
   out_3607384786905077425[3] = 0;
   out_3607384786905077425[4] = -state[8];
   out_3607384786905077425[5] = state[7];
   out_3607384786905077425[6] = 0;
   out_3607384786905077425[7] = state[5];
   out_3607384786905077425[8] = -state[4];
   out_3607384786905077425[9] = 0;
   out_3607384786905077425[10] = 0;
   out_3607384786905077425[11] = 0;
   out_3607384786905077425[12] = 1;
   out_3607384786905077425[13] = 0;
   out_3607384786905077425[14] = 0;
   out_3607384786905077425[15] = 1;
   out_3607384786905077425[16] = 0;
   out_3607384786905077425[17] = 0;
   out_3607384786905077425[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3607384786905077425[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3607384786905077425[20] = 0;
   out_3607384786905077425[21] = state[8];
   out_3607384786905077425[22] = 0;
   out_3607384786905077425[23] = -state[6];
   out_3607384786905077425[24] = -state[5];
   out_3607384786905077425[25] = 0;
   out_3607384786905077425[26] = state[3];
   out_3607384786905077425[27] = 0;
   out_3607384786905077425[28] = 0;
   out_3607384786905077425[29] = 0;
   out_3607384786905077425[30] = 0;
   out_3607384786905077425[31] = 1;
   out_3607384786905077425[32] = 0;
   out_3607384786905077425[33] = 0;
   out_3607384786905077425[34] = 1;
   out_3607384786905077425[35] = 0;
   out_3607384786905077425[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3607384786905077425[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3607384786905077425[38] = 0;
   out_3607384786905077425[39] = -state[7];
   out_3607384786905077425[40] = state[6];
   out_3607384786905077425[41] = 0;
   out_3607384786905077425[42] = state[4];
   out_3607384786905077425[43] = -state[3];
   out_3607384786905077425[44] = 0;
   out_3607384786905077425[45] = 0;
   out_3607384786905077425[46] = 0;
   out_3607384786905077425[47] = 0;
   out_3607384786905077425[48] = 0;
   out_3607384786905077425[49] = 0;
   out_3607384786905077425[50] = 1;
   out_3607384786905077425[51] = 0;
   out_3607384786905077425[52] = 0;
   out_3607384786905077425[53] = 1;
}
void h_13(double *state, double *unused, double *out_7690213453916874753) {
   out_7690213453916874753[0] = state[3];
   out_7690213453916874753[1] = state[4];
   out_7690213453916874753[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6848591547490543610) {
   out_6848591547490543610[0] = 0;
   out_6848591547490543610[1] = 0;
   out_6848591547490543610[2] = 0;
   out_6848591547490543610[3] = 1;
   out_6848591547490543610[4] = 0;
   out_6848591547490543610[5] = 0;
   out_6848591547490543610[6] = 0;
   out_6848591547490543610[7] = 0;
   out_6848591547490543610[8] = 0;
   out_6848591547490543610[9] = 0;
   out_6848591547490543610[10] = 0;
   out_6848591547490543610[11] = 0;
   out_6848591547490543610[12] = 0;
   out_6848591547490543610[13] = 0;
   out_6848591547490543610[14] = 0;
   out_6848591547490543610[15] = 0;
   out_6848591547490543610[16] = 0;
   out_6848591547490543610[17] = 0;
   out_6848591547490543610[18] = 0;
   out_6848591547490543610[19] = 0;
   out_6848591547490543610[20] = 0;
   out_6848591547490543610[21] = 0;
   out_6848591547490543610[22] = 1;
   out_6848591547490543610[23] = 0;
   out_6848591547490543610[24] = 0;
   out_6848591547490543610[25] = 0;
   out_6848591547490543610[26] = 0;
   out_6848591547490543610[27] = 0;
   out_6848591547490543610[28] = 0;
   out_6848591547490543610[29] = 0;
   out_6848591547490543610[30] = 0;
   out_6848591547490543610[31] = 0;
   out_6848591547490543610[32] = 0;
   out_6848591547490543610[33] = 0;
   out_6848591547490543610[34] = 0;
   out_6848591547490543610[35] = 0;
   out_6848591547490543610[36] = 0;
   out_6848591547490543610[37] = 0;
   out_6848591547490543610[38] = 0;
   out_6848591547490543610[39] = 0;
   out_6848591547490543610[40] = 0;
   out_6848591547490543610[41] = 1;
   out_6848591547490543610[42] = 0;
   out_6848591547490543610[43] = 0;
   out_6848591547490543610[44] = 0;
   out_6848591547490543610[45] = 0;
   out_6848591547490543610[46] = 0;
   out_6848591547490543610[47] = 0;
   out_6848591547490543610[48] = 0;
   out_6848591547490543610[49] = 0;
   out_6848591547490543610[50] = 0;
   out_6848591547490543610[51] = 0;
   out_6848591547490543610[52] = 0;
   out_6848591547490543610[53] = 0;
}
void h_14(double *state, double *unused, double *out_1351222622664013473) {
   out_1351222622664013473[0] = state[6];
   out_1351222622664013473[1] = state[7];
   out_1351222622664013473[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5303090268591302909) {
   out_5303090268591302909[0] = 0;
   out_5303090268591302909[1] = 0;
   out_5303090268591302909[2] = 0;
   out_5303090268591302909[3] = 0;
   out_5303090268591302909[4] = 0;
   out_5303090268591302909[5] = 0;
   out_5303090268591302909[6] = 1;
   out_5303090268591302909[7] = 0;
   out_5303090268591302909[8] = 0;
   out_5303090268591302909[9] = 0;
   out_5303090268591302909[10] = 0;
   out_5303090268591302909[11] = 0;
   out_5303090268591302909[12] = 0;
   out_5303090268591302909[13] = 0;
   out_5303090268591302909[14] = 0;
   out_5303090268591302909[15] = 0;
   out_5303090268591302909[16] = 0;
   out_5303090268591302909[17] = 0;
   out_5303090268591302909[18] = 0;
   out_5303090268591302909[19] = 0;
   out_5303090268591302909[20] = 0;
   out_5303090268591302909[21] = 0;
   out_5303090268591302909[22] = 0;
   out_5303090268591302909[23] = 0;
   out_5303090268591302909[24] = 0;
   out_5303090268591302909[25] = 1;
   out_5303090268591302909[26] = 0;
   out_5303090268591302909[27] = 0;
   out_5303090268591302909[28] = 0;
   out_5303090268591302909[29] = 0;
   out_5303090268591302909[30] = 0;
   out_5303090268591302909[31] = 0;
   out_5303090268591302909[32] = 0;
   out_5303090268591302909[33] = 0;
   out_5303090268591302909[34] = 0;
   out_5303090268591302909[35] = 0;
   out_5303090268591302909[36] = 0;
   out_5303090268591302909[37] = 0;
   out_5303090268591302909[38] = 0;
   out_5303090268591302909[39] = 0;
   out_5303090268591302909[40] = 0;
   out_5303090268591302909[41] = 0;
   out_5303090268591302909[42] = 0;
   out_5303090268591302909[43] = 0;
   out_5303090268591302909[44] = 1;
   out_5303090268591302909[45] = 0;
   out_5303090268591302909[46] = 0;
   out_5303090268591302909[47] = 0;
   out_5303090268591302909[48] = 0;
   out_5303090268591302909[49] = 0;
   out_5303090268591302909[50] = 0;
   out_5303090268591302909[51] = 0;
   out_5303090268591302909[52] = 0;
   out_5303090268591302909[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3697966966174848325) {
  err_fun(nom_x, delta_x, out_3697966966174848325);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6121892126530152725) {
  inv_err_fun(nom_x, true_x, out_6121892126530152725);
}
void pose_H_mod_fun(double *state, double *out_1116503706765055069) {
  H_mod_fun(state, out_1116503706765055069);
}
void pose_f_fun(double *state, double dt, double *out_2317659772838150308) {
  f_fun(state,  dt, out_2317659772838150308);
}
void pose_F_fun(double *state, double dt, double *out_6164130103148092652) {
  F_fun(state,  dt, out_6164130103148092652);
}
void pose_h_4(double *state, double *unused, double *out_2811574505702470007) {
  h_4(state, unused, out_2811574505702470007);
}
void pose_H_4(double *state, double *unused, double *out_8385878700886675205) {
  H_4(state, unused, out_8385878700886675205);
}
void pose_h_10(double *state, double *unused, double *out_5534858922172779190) {
  h_10(state, unused, out_5534858922172779190);
}
void pose_H_10(double *state, double *unused, double *out_3607384786905077425) {
  H_10(state, unused, out_3607384786905077425);
}
void pose_h_13(double *state, double *unused, double *out_7690213453916874753) {
  h_13(state, unused, out_7690213453916874753);
}
void pose_H_13(double *state, double *unused, double *out_6848591547490543610) {
  H_13(state, unused, out_6848591547490543610);
}
void pose_h_14(double *state, double *unused, double *out_1351222622664013473) {
  h_14(state, unused, out_1351222622664013473);
}
void pose_H_14(double *state, double *unused, double *out_5303090268591302909) {
  H_14(state, unused, out_5303090268591302909);
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
