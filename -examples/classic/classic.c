#include "classic.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

const unsigned zebu_lexer[57][123] = {
	[1][32] = 1,
	[1][65] = 21,
	[1][66] = 22,
	[1][67] = 23,
	[1][97] = 24,
	[1][98] = 25,
	[1][99] = 26,
	[1][103] = 1,
	[2][32] = 27,
	[2][63] = 28,
	[2][103] = 27,
	[2][104] = 9,
	[3][32] = 3,
	[3][58] = 30,
	[3][103] = 3,
	[4][32] = 4,
	[4][66] = 25,
	[4][97] = 31,
	[4][98] = 25,
	[4][99] = 26,
	[4][103] = 4,
	[5][32] = 5,
	[5][65] = 21,
	[5][66] = 22,
	[5][67] = 23,
	[5][103] = 5,
	[6][32] = 6,
	[6][97] = 31,
	[6][99] = 26,
	[6][103] = 6,
	[7][32] = 7,
	[7][97] = 31,
	[7][103] = 7,
	[8][32] = 5,
	[8][65] = 21,
	[8][66] = 22,
	[8][67] = 23,
	[8][103] = 5,
	[8][104] = 9,
	[9][104] = 9,
	[10][32] = 10,
	[10][46] = 32,
	[10][103] = 10,
	[10][119] = 33,
	[10][120] = 33,
	[10][121] = 33,
	[11][32] = 11,
	[11][46] = 32,
	[11][58] = 30,
	[11][103] = 11,
	[11][119] = 33,
	[11][120] = 34,
	[11][121] = 34,
	[11][122] = 35,
	[12][32] = 12,
	[12][58] = 30,
	[12][103] = 12,
	[12][120] = 35,
	[12][121] = 35,
	[12][122] = 35,
	[13][32] = 13,
	[13][99] = 26,
	[13][103] = 13,
	[14][32] = 14,
	[14][66] = 25,
	[14][98] = 25,
	[14][103] = 14,
	[15][32] = 15,
	[15][65] = 21,
	[15][103] = 15,
	[16][32] = 16,
	[16][66] = 22,
	[16][103] = 16,
	[17][32] = 17,
	[17][67] = 23,
	[17][103] = 17,
	[18][32] = 4,
	[18][66] = 25,
	[18][97] = 31,
	[18][98] = 25,
	[18][99] = 26,
	[18][103] = 4,
	[18][104] = 9,
	[19][32] = 19,
	[19][33] = 36,
	[19][46] = 32,
	[19][103] = 19,
	[19][119] = 33,
	[19][120] = 33,
	[19][121] = 33,
	[20][32] = 20,
	[20][33] = 36,
	[20][103] = 20,
	[24][97] = 37,
	[24][98] = 38,
	[27][32] = 27,
	[27][63] = 28,
	[27][103] = 27,
	[37][97] = 39,
	[37][98] = 40,
	[38][98] = 40,
	[38][99] = 41,
	[39][97] = 42,
	[39][98] = 43,
	[40][98] = 43,
	[40][99] = 44,
	[41][99] = 44,
	[42][97] = 45,
	[42][98] = 46,
	[43][98] = 46,
	[43][99] = 47,
	[44][99] = 47,
	[45][97] = 48,
	[45][98] = 49,
	[46][98] = 49,
	[46][99] = 50,
	[47][99] = 50,
	[48][97] = 51,
	[48][98] = 52,
	[49][98] = 52,
	[49][99] = 53,
	[50][99] = 53,
	[51][97] = 37,
	[51][98] = 54,
	[52][98] = 54,
	[52][99] = 55,
	[53][99] = 55,
	[54][98] = 40,
	[54][99] = 56,
	[55][99] = 56,
	[56][99] = 44,
};


const unsigned zebu_lexer_starts[215] = {
	[1] = 1,
	[2] = 2,
	[3] = 3,
	[4] = 3,
	[5] = 3,
	[6] = 4,
	[7] = 4,
	[8] = 4,
	[9] = 5,
	[10] = 5,
	[11] = 5,
	[12] = 6,
	[13] = 7,
	[14] = 8,
	[15] = 8,
	[16] = 8,
	[17] = 9,
	[18] = 10,
	[19] = 11,
	[20] = 12,
	[21] = 13,
	[22] = 4,
	[23] = 9,
	[24] = 7,
	[25] = 7,
	[26] = 4,
	[27] = 6,
	[28] = 4,
	[29] = 14,
	[30] = 4,
	[31] = 4,
	[32] = 7,
	[33] = 13,
	[34] = 8,
	[35] = 5,
	[36] = 5,
	[37] = 15,
	[38] = 15,
	[39] = 5,
	[40] = 8,
	[41] = 5,
	[42] = 16,
	[43] = 16,
	[44] = 5,
	[45] = 5,
	[46] = 8,
	[47] = 17,
	[48] = 17,
	[49] = 4,
	[50] = 4,
	[51] = 9,
	[52] = 18,
	[53] = 4,
	[54] = 9,
	[55] = 9,
	[56] = 8,
	[57] = 8,
	[58] = 8,
	[59] = 9,
	[60] = 9,
	[61] = 10,
	[62] = 9,
	[63] = 9,
	[64] = 12,
	[65] = 19,
	[66] = 20,
	[67] = 9,
	[68] = 9,
	[69] = 18,
	[70] = 4,
	[71] = 7,
	[72] = 14,
	[73] = 13,
	[74] = 9,
	[75] = 9,
	[76] = 14,
	[77] = 7,
	[78] = 7,
	[79] = 4,
	[80] = 14,
	[81] = 13,
	[82] = 6,
	[83] = 6,
	[84] = 13,
	[85] = 7,
	[86] = 7,
	[87] = 4,
	[88] = 13,
	[89] = 14,
	[90] = 7,
	[91] = 7,
	[92] = 15,
	[93] = 16,
	[94] = 16,
	[95] = 15,
	[96] = 17,
	[97] = 17,
	[98] = 8,
	[99] = 8,
	[100] = 8,
	[101] = 16,
	[102] = 15,
	[103] = 15,
	[104] = 16,
	[105] = 17,
	[106] = 17,
	[107] = 8,
	[108] = 8,
	[109] = 8,
	[110] = 17,
	[111] = 15,
	[112] = 15,
	[113] = 17,
	[114] = 16,
	[115] = 16,
	[116] = 8,
	[117] = 8,
	[118] = 8,
	[119] = 18,
	[120] = 9,
	[121] = 7,
	[122] = 7,
	[123] = 4,
	[124] = 18,
	[125] = 13,
	[126] = 4,
	[127] = 9,
	[128] = 6,
	[129] = 7,
	[130] = 9,
	[131] = 9,
	[132] = 9,
	[133] = 9,
	[134] = 9,
	[135] = 9,
	[136] = 9,
	[137] = 9,
	[138] = 14,
	[139] = 7,
	[140] = 7,
	[141] = 7,
	[142] = 7,
	[143] = 9,
	[144] = 6,
	[145] = 14,
	[146] = 6,
	[147] = 6,
	[148] = 13,
	[149] = 7,
	[150] = 7,
	[151] = 14,
	[152] = 14,
	[153] = 7,
	[154] = 13,
	[155] = 7,
	[156] = 7,
	[157] = 14,
	[158] = 7,
	[159] = 7,
	[160] = 13,
	[161] = 13,
	[162] = 15,
	[163] = 15,
	[164] = 15,
	[165] = 15,
	[166] = 15,
	[167] = 15,
	[168] = 16,
	[169] = 16,
	[170] = 16,
	[171] = 16,
	[172] = 16,
	[173] = 16,
	[174] = 17,
	[175] = 17,
	[176] = 17,
	[177] = 17,
	[178] = 17,
	[179] = 17,
	[180] = 9,
	[181] = 18,
	[182] = 9,
	[183] = 9,
	[184] = 13,
	[185] = 7,
	[186] = 7,
	[187] = 18,
	[188] = 18,
	[189] = 9,
	[190] = 9,
	[191] = 9,
	[192] = 7,
	[193] = 14,
	[194] = 7,
	[195] = 7,
	[196] = 6,
	[197] = 14,
	[198] = 13,
	[199] = 14,
	[200] = 14,
	[201] = 7,
	[202] = 13,
	[203] = 14,
	[204] = 13,
	[205] = 13,
	[206] = 9,
	[207] = 18,
	[208] = 13,
	[209] = 18,
	[210] = 18,
	[211] = 7,
	[212] = 14,
	[213] = 13,
	[214] = 18,
};


const unsigned zebu_lexer_accepts[57] = {
	[21] = 9,
	[22] = 10,
	[23] = 11,
	[24] = 6,
	[25] = 7,
	[26] = 8,
	[28] = 12,
	[29] = 13,
	[30] = 14,
	[31] = 6,
	[32] = 16,
	[33] = 15,
	[34] = 17,
	[35] = 18,
	[36] = 19,
	[41] = 2,
	[44] = 3,
	[50] = 4,
	[55] = 3,
	[56] = 5,
};


const unsigned zebu_lexer_EOFs[19] = {
	[2] = 29,
	[8] = 29,
	[9] = 29,
	[18] = 29,
};


const unsigned zebu_shifts[209][20] = {
	[1][2] = 2,
	[1][3] = 3,
	[1][4] = 4,
	[1][5] = 5,
	[1][6] = 6,
	[1][7] = 7,
	[1][8] = 8,
	[1][9] = 9,
	[1][10] = 10,
	[1][11] = 11,
	[2][12] = 17,
	[3][14] = 18,
	[4][14] = 19,
	[5][14] = 20,
	[6][6] = 21,
	[6][7] = 22,
	[6][8] = 8,
	[7][6] = 26,
	[7][7] = 27,
	[7][8] = 28,
	[8][6] = 30,
	[8][7] = 31,
	[8][8] = 32,
	[9][9] = 34,
	[9][10] = 35,
	[9][11] = 36,
	[10][9] = 39,
	[10][10] = 40,
	[10][11] = 41,
	[11][9] = 44,
	[11][10] = 45,
	[11][11] = 46,
	[12][6] = 49,
	[12][8] = 50,
	[13][6] = 53,
	[14][9] = 9,
	[14][10] = 10,
	[14][11] = 11,
	[15][9] = 9,
	[15][10] = 10,
	[15][11] = 11,
	[16][9] = 9,
	[16][10] = 10,
	[16][11] = 11,
	[18][15] = 61,
	[18][16] = 62,
	[19][14] = 64,
	[19][15] = 61,
	[19][16] = 62,
	[19][17] = 65,
	[19][18] = 66,
	[20][14] = 64,
	[20][18] = 66,
	[21][8] = 50,
	[22][6] = 70,
	[22][7] = 71,
	[22][8] = 28,
	[24][6] = 73,
	[25][6] = 73,
	[26][6] = 76,
	[26][7] = 22,
	[26][8] = 8,
	[28][6] = 79,
	[28][7] = 31,
	[28][8] = 80,
	[29][7] = 82,
	[30][6] = 84,
	[30][7] = 22,
	[30][8] = 8,
	[31][6] = 87,
	[31][7] = 88,
	[31][8] = 28,
	[33][8] = 90,
	[35][9] = 39,
	[35][10] = 92,
	[35][11] = 41,
	[36][9] = 44,
	[36][10] = 45,
	[36][11] = 95,
	[37][9] = 98,
	[38][9] = 98,
	[39][9] = 101,
	[39][10] = 35,
	[39][11] = 36,
	[41][9] = 44,
	[41][10] = 45,
	[41][11] = 104,
	[42][10] = 107,
	[43][10] = 107,
	[44][9] = 110,
	[44][10] = 35,
	[44][11] = 36,
	[45][9] = 39,
	[45][10] = 113,
	[45][11] = 41,
	[47][11] = 116,
	[48][11] = 116,
	[49][6] = 119,
	[49][7] = 22,
	[49][8] = 8,
	[50][6] = 123,
	[50][7] = 31,
	[50][8] = 124,
	[52][6] = 126,
	[52][7] = 7,
	[52][8] = 8,
	[53][6] = 119,
	[53][7] = 22,
	[53][8] = 8,
	[56][9] = 9,
	[56][10] = 10,
	[56][11] = 11,
	[57][9] = 9,
	[57][10] = 10,
	[57][11] = 11,
	[58][9] = 9,
	[58][10] = 10,
	[58][11] = 11,
	[61][15] = 61,
	[61][16] = 62,
	[64][14] = 64,
	[64][18] = 66,
	[65][15] = 61,
	[65][16] = 62,
	[65][19] = 136,
	[66][19] = 136,
	[69][6] = 126,
	[69][7] = 7,
	[69][8] = 8,
	[70][6] = 138,
	[70][7] = 22,
	[70][8] = 8,
	[72][7] = 141,
	[73][8] = 50,
	[76][7] = 82,
	[77][6] = 145,
	[78][6] = 145,
	[79][6] = 148,
	[79][7] = 22,
	[79][8] = 8,
	[81][8] = 151,
	[84][8] = 90,
	[85][6] = 154,
	[86][6] = 154,
	[87][6] = 157,
	[87][7] = 22,
	[87][8] = 8,
	[89][7] = 160,
	[93][10] = 162,
	[94][10] = 162,
	[96][11] = 165,
	[97][11] = 165,
	[102][9] = 168,
	[103][9] = 168,
	[105][11] = 171,
	[106][11] = 171,
	[111][9] = 174,
	[112][9] = 174,
	[114][10] = 177,
	[115][10] = 177,
	[119][6] = 126,
	[119][7] = 7,
	[119][8] = 8,
	[121][6] = 181,
	[122][6] = 181,
	[123][6] = 184,
	[123][7] = 22,
	[123][8] = 8,
	[125][8] = 187,
	[126][6] = 21,
	[126][7] = 22,
	[126][8] = 8,
	[128][6] = 49,
	[128][8] = 50,
	[129][6] = 53,
	[138][7] = 141,
	[139][6] = 193,
	[140][6] = 193,
	[145][7] = 82,
	[148][8] = 151,
	[149][6] = 198,
	[150][6] = 198,
	[154][8] = 90,
	[157][7] = 160,
	[158][6] = 203,
	[159][6] = 203,
	[181][6] = 126,
	[181][7] = 7,
	[181][8] = 8,
	[184][8] = 187,
	[185][6] = 208,
	[186][6] = 208,
	[193][7] = 141,
	[198][8] = 151,
	[203][7] = 160,
	[208][8] = 187,
};


const unsigned zebu_reduces[215][14] = {
	[2][13] = 1,
	[14][13] = 2,
	[15][13] = 3,
	[16][13] = 4,
	[17][13] = 5,
	[23][13] = 6,
	[27][6] = 7,
	[27][8] = 7,
	[32][6] = 8,
	[34][9] = 9,
	[34][10] = 9,
	[34][11] = 9,
	[34][13] = 9,
	[40][9] = 10,
	[40][10] = 10,
	[40][11] = 10,
	[40][13] = 10,
	[46][9] = 11,
	[46][10] = 11,
	[46][11] = 11,
	[46][13] = 11,
	[51][13] = 12,
	[52][13] = 13,
	[54][13] = 14,
	[55][13] = 15,
	[56][13] = 16,
	[57][13] = 17,
	[58][13] = 18,
	[59][13] = 19,
	[60][13] = 20,
	[62][13] = 21,
	[63][13] = 22,
	[67][13] = 23,
	[68][13] = 24,
	[69][13] = 25,
	[71][6] = 7,
	[74][13] = 26,
	[75][13] = 27,
	[80][7] = 8,
	[82][6] = 28,
	[82][8] = 28,
	[83][6] = 29,
	[83][8] = 29,
	[88][8] = 7,
	[90][6] = 30,
	[91][6] = 31,
	[92][9] = 10,
	[95][9] = 11,
	[98][9] = 32,
	[98][10] = 32,
	[98][11] = 32,
	[98][13] = 32,
	[99][9] = 33,
	[99][10] = 33,
	[99][11] = 33,
	[99][13] = 33,
	[100][9] = 34,
	[100][10] = 34,
	[100][11] = 34,
	[100][13] = 34,
	[101][10] = 9,
	[104][10] = 11,
	[107][9] = 35,
	[107][10] = 35,
	[107][11] = 35,
	[107][13] = 35,
	[108][9] = 36,
	[108][10] = 36,
	[108][11] = 36,
	[108][13] = 36,
	[109][9] = 37,
	[109][10] = 37,
	[109][11] = 37,
	[109][13] = 37,
	[110][11] = 9,
	[113][11] = 10,
	[116][9] = 38,
	[116][10] = 38,
	[116][11] = 38,
	[116][13] = 38,
	[117][9] = 39,
	[117][10] = 39,
	[117][11] = 39,
	[117][13] = 39,
	[118][9] = 40,
	[118][10] = 40,
	[118][11] = 40,
	[118][13] = 40,
	[119][13] = 41,
	[120][13] = 42,
	[124][6] = 8,
	[124][7] = 8,
	[124][8] = 8,
	[124][13] = 8,
	[127][13] = 43,
	[130][13] = 44,
	[131][13] = 45,
	[132][13] = 46,
	[133][13] = 47,
	[134][13] = 48,
	[135][13] = 49,
	[136][13] = 50,
	[137][13] = 51,
	[141][6] = 28,
	[142][6] = 29,
	[143][13] = 52,
	[144][6] = 53,
	[144][8] = 53,
	[146][6] = 54,
	[146][8] = 54,
	[147][6] = 55,
	[147][8] = 55,
	[151][7] = 30,
	[152][7] = 31,
	[153][6] = 56,
	[155][6] = 57,
	[156][6] = 58,
	[160][8] = 28,
	[161][8] = 29,
	[162][9] = 35,
	[163][9] = 36,
	[164][9] = 37,
	[165][9] = 38,
	[166][9] = 39,
	[167][9] = 40,
	[168][10] = 32,
	[169][10] = 33,
	[170][10] = 34,
	[171][10] = 38,
	[172][10] = 39,
	[173][10] = 40,
	[174][11] = 32,
	[175][11] = 33,
	[176][11] = 34,
	[177][11] = 35,
	[178][11] = 36,
	[179][11] = 37,
	[180][13] = 59,
	[181][13] = 60,
	[182][13] = 61,
	[183][13] = 62,
	[187][6] = 30,
	[187][7] = 30,
	[187][8] = 30,
	[187][13] = 30,
	[188][6] = 31,
	[188][7] = 31,
	[188][8] = 31,
	[188][13] = 31,
	[189][13] = 63,
	[190][13] = 64,
	[191][13] = 65,
	[192][6] = 53,
	[194][6] = 54,
	[195][6] = 55,
	[196][6] = 66,
	[196][8] = 66,
	[197][7] = 56,
	[199][7] = 57,
	[200][7] = 58,
	[201][6] = 67,
	[202][8] = 53,
	[204][8] = 54,
	[205][8] = 55,
	[206][13] = 68,
	[207][6] = 56,
	[207][7] = 56,
	[207][8] = 56,
	[207][13] = 56,
	[209][6] = 57,
	[209][7] = 57,
	[209][8] = 57,
	[209][13] = 57,
	[210][6] = 58,
	[210][7] = 58,
	[210][8] = 58,
	[210][13] = 58,
	[211][6] = 66,
	[212][7] = 67,
	[213][8] = 66,
	[214][6] = 67,
	[214][7] = 67,
	[214][8] = 67,
	[214][13] = 67,
};


const unsigned zebu_gotos[209][24] = {
	[1][1] = 12,
	[1][2] = 13,
	[1][3] = 14,
	[1][4] = 15,
	[1][5] = 16,
	[6][1] = 24,
	[6][2] = 25,
	[6][6] = 23,
	[7][2] = 29,
	[8][1] = 33,
	[9][4] = 37,
	[9][5] = 38,
	[10][3] = 42,
	[10][5] = 43,
	[11][3] = 47,
	[11][4] = 48,
	[12][2] = 52,
	[12][7] = 51,
	[13][8] = 54,
	[14][3] = 56,
	[14][4] = 57,
	[14][5] = 58,
	[14][9] = 55,
	[15][3] = 56,
	[15][4] = 57,
	[15][5] = 58,
	[15][9] = 59,
	[16][3] = 56,
	[16][4] = 57,
	[16][5] = 58,
	[16][9] = 60,
	[18][10] = 63,
	[19][10] = 63,
	[19][11] = 67,
	[20][11] = 67,
	[21][2] = 69,
	[21][12] = 68,
	[22][2] = 72,
	[24][13] = 74,
	[25][13] = 75,
	[26][1] = 77,
	[26][2] = 78,
	[28][1] = 81,
	[29][14] = 83,
	[30][1] = 85,
	[30][2] = 86,
	[31][2] = 89,
	[33][15] = 91,
	[35][3] = 93,
	[35][5] = 94,
	[36][3] = 96,
	[36][4] = 97,
	[37][16] = 99,
	[38][16] = 100,
	[39][4] = 102,
	[39][5] = 103,
	[41][3] = 105,
	[41][4] = 106,
	[42][17] = 108,
	[43][17] = 109,
	[44][4] = 111,
	[44][5] = 112,
	[45][3] = 114,
	[45][5] = 115,
	[47][18] = 117,
	[48][18] = 118,
	[49][1] = 121,
	[49][2] = 122,
	[49][19] = 120,
	[50][1] = 125,
	[52][1] = 128,
	[52][2] = 129,
	[52][20] = 127,
	[53][1] = 121,
	[53][2] = 122,
	[53][19] = 130,
	[56][3] = 56,
	[56][4] = 57,
	[56][5] = 58,
	[56][9] = 131,
	[57][3] = 56,
	[57][4] = 57,
	[57][5] = 58,
	[57][9] = 132,
	[58][3] = 56,
	[58][4] = 57,
	[58][5] = 58,
	[58][9] = 133,
	[61][10] = 134,
	[64][11] = 135,
	[65][10] = 134,
	[69][1] = 128,
	[69][2] = 129,
	[69][20] = 137,
	[70][1] = 139,
	[70][2] = 140,
	[72][14] = 142,
	[73][2] = 69,
	[73][12] = 143,
	[76][14] = 144,
	[77][21] = 146,
	[78][21] = 147,
	[79][1] = 149,
	[79][2] = 150,
	[81][15] = 152,
	[84][15] = 153,
	[85][22] = 155,
	[86][22] = 156,
	[87][1] = 158,
	[87][2] = 159,
	[89][14] = 161,
	[93][17] = 163,
	[94][17] = 164,
	[96][18] = 166,
	[97][18] = 167,
	[102][16] = 169,
	[103][16] = 170,
	[105][18] = 172,
	[106][18] = 173,
	[111][16] = 175,
	[112][16] = 176,
	[114][17] = 178,
	[115][17] = 179,
	[119][1] = 128,
	[119][2] = 129,
	[119][20] = 180,
	[121][23] = 182,
	[122][23] = 183,
	[123][1] = 185,
	[123][2] = 186,
	[125][15] = 188,
	[126][1] = 24,
	[126][2] = 25,
	[126][6] = 189,
	[128][2] = 52,
	[128][7] = 190,
	[129][8] = 191,
	[138][14] = 192,
	[139][21] = 194,
	[140][21] = 195,
	[145][14] = 196,
	[148][15] = 197,
	[149][22] = 199,
	[150][22] = 200,
	[154][15] = 201,
	[157][14] = 202,
	[158][21] = 204,
	[159][21] = 205,
	[181][1] = 128,
	[181][2] = 129,
	[181][20] = 206,
	[184][15] = 207,
	[185][22] = 209,
	[186][22] = 210,
	[193][14] = 211,
	[198][15] = 212,
	[203][14] = 213,
	[208][15] = 214,
};


struct token
{
unsigned char* data;
unsigned len, refcount;
};
struct __0_b
{
	unsigned refcount;
};

struct __0_c
{
	unsigned refcount;
};

struct __1_a
{
	unsigned refcount;
};

struct __1_b
{
	unsigned refcount;
};

struct __1_c
{
	unsigned refcount;
};

struct __start__
{
	struct token* abc1;
	struct token* abc2;
	struct token* abc3;
	unsigned refcount;
};



#include <stdbool.h>

struct link
{
	bool is_last;
	struct link* prev;
};

void print_links(struct link* link)
{
	if (!link) return;
	
	print_links(link->prev);
	
	if (link->is_last)
		fputs("    ", stdout);
	else
		fputs("│   ", stdout);
}

enum prefix
{
	p_root,
	p_not_last_child,
	p_last_child,
};

void print_token_leaf(struct link* links, enum prefix p, const char* name, struct token* token)
{
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[32m%s\e[0m (\e[35m\"%s\"\e[0m)\n", name, token->data);
}

void print_empty_leaf(struct link* links, enum prefix p, const char* type, const char* name)
{
	print_links(links);
	switch (p)
	{
		case p_root: break;
		case p_not_last_child: fputs("├── ", stdout); break;
		case p_last_child: fputs("└── ", stdout); break;
	}
	printf("\e[31m%s\e[0m (\e[36m%s\e[0m)\n", name, type);
}
void print___0_b_tree(struct link* links, enum prefix p, const char* name, struct __0_b* ptree);

void print___0_c_tree(struct link* links, enum prefix p, const char* name, struct __0_c* ptree);

void print___1_a_tree(struct link* links, enum prefix p, const char* name, struct __1_a* ptree);

void print___1_b_tree(struct link* links, enum prefix p, const char* name, struct __1_b* ptree);

void print___1_c_tree(struct link* links, enum prefix p, const char* name, struct __1_c* ptree);

void print___start___tree(struct link* links, enum prefix p, const char* name, struct __start__* ptree);

void print___0_b_tree(struct link* links, enum prefix p, const char* name, struct __0_b* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__0_b\e[m)\n", name);
	free(new);
}
void print___0_c_tree(struct link* links, enum prefix p, const char* name, struct __0_c* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__0_c\e[m)\n", name);
	free(new);
}
void print___1_a_tree(struct link* links, enum prefix p, const char* name, struct __1_a* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__1_a\e[m)\n", name);
	free(new);
}
void print___1_b_tree(struct link* links, enum prefix p, const char* name, struct __1_b* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__1_b\e[m)\n", name);
	free(new);
}
void print___1_c_tree(struct link* links, enum prefix p, const char* name, struct __1_c* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__1_c\e[m)\n", name);
	free(new);
}
void print___start___tree(struct link* links, enum prefix p, const char* name, struct __start__* ptree)
{
	print_links(links);
	
	struct link* new = NULL;
	
	switch (p)
	{
		case p_root:
			break;
		
		case p_not_last_child:
			fputs("├── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = false;
			new->prev = links;
			break;
		
		case p_last_child:
			fputs("└── ", stdout);
			new = malloc(sizeof(*new));
			new->is_last = true;
			new->prev = links;
		break;
	}
	printf("\e[34m%s\e[m (\e[36m__start__\e[m)\n", name);
	if (ptree->abc1)
		print_token_leaf(new ?: links, p_not_last_child, "abc1", ptree->abc1);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "abc1");
	if (ptree->abc2)
		print_token_leaf(new ?: links, p_not_last_child, "abc2", ptree->abc2);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "abc2");
	if (ptree->abc3)
		print_token_leaf(new ?: links, p_last_child, "abc3", ptree->abc3);
	else
		print_empty_leaf(new ?: links, p_last_child, "token", "abc3");
	free(new);
}


struct token* inc_token(struct token* this)
{
	if (this) this->refcount++;
	return this;
}
struct __0_b* inc___0_b_tree(struct __0_b* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct __0_c* inc___0_c_tree(struct __0_c* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct __1_a* inc___1_a_tree(struct __1_a* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct __1_b* inc___1_b_tree(struct __1_b* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct __1_c* inc___1_c_tree(struct __1_c* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct __start__* inc___start___tree(struct __start__* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}



void free_token(struct token* this)
{
	if (this && !--this->refcount)
	{
		free(this->data);
		free(this);
	}
}
void free___0_b_tree(struct __0_b* ptree);

void free___0_c_tree(struct __0_c* ptree);

void free___1_a_tree(struct __1_a* ptree);

void free___1_b_tree(struct __1_b* ptree);

void free___1_c_tree(struct __1_c* ptree);

void free___start___tree(struct __start__* ptree);

void free___0_b_tree(struct __0_b* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free(ptree);
	}
}

void free___0_c_tree(struct __0_c* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free(ptree);
	}
}

void free___1_a_tree(struct __1_a* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free(ptree);
	}
}

void free___1_b_tree(struct __1_b* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free(ptree);
	}
}

void free___1_c_tree(struct __1_c* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free(ptree);
	}
}

void free___start___tree(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_token(ptree->abc1);
		free_token(ptree->abc2);
		free_token(ptree->abc3);
		free(ptree);
	}
}



#define N(array) (sizeof(array) / sizeof(*array))

static void escape(char *out, char in)
{
	switch (in)
	{
		case ' ':
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '=':
		case '|':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}

int main()
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	void ddprintf(const char* fmt, ...)
	{
		for (unsigned i = 0, n = yacc.n; i < n; i++)
			printf("%u ", yacc.data[i]);
		
		printf("| ");
		
		va_list va;
		va_start(va, fmt);
		vprintf(fmt, va);
		va_end(va);
	}

	void push_state(unsigned state)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		
		yacc.data[yacc.n++] = state;
	}
	
	void push_data(void* element)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		
		data.data[data.n++] = element;
	}
	
	for (char* line; (line = readline(">>> "));)
	{
		char* lexer = (void*) line;
		
		unsigned y, s, r, t;
		
		void* td;
		
		void read_token(unsigned l)
		{
			char escaped[10];
			
			char* begin = lexer, *f = NULL;
			
			unsigned a, b, c;
			
			while (1)
			{
				if ((c = *lexer))
				{
					escape(escaped, c);
					
					ddprintf("c = '%s' (0x%X)\n", escaped, c);
					
					a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
				}
				else
				{
					ddprintf("c == <EOF>\n");
					a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
				}
				
				b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
				
				ddprintf("lexer: %u: a = %u, b = %u\n", l, a, b);
				
				if (a)
				{
					if (b)
					{
						l = a, t = b, f = lexer++;
						ddprintf("l = %u, t == %u, f = %p (saved)\n", l, t, f);
					}
					else
					{
						l = a;
						if (c) lexer++;
						ddprintf("lexer: l == %u\n", l);
					}
				}
				else if (b)
				{
					ddprintf("lexer: \"%.*s\"\n", lexer - begin, begin);
					
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = (void*) strndup(begin, lexer - begin);
					t = b, td = token;
					break;
				}
				else if (t)
				{
					assert(!"172");
					#if 0
					process_token(t);
					l = zebu_starts[yacc.data[yacc.n - 1]], i = f, t = 0;
					ddprintf("l == %u, i = %u, t = %u\n", l, i, t);
					#endif
				}
				else
				{
					assert(!"TODO");
				}
			}
		}
		
		yacc.n = 0, data.n = 0, y = 1, push_state(y);
		
		read_token(zebu_lexer_starts[y]);
		
		ddprintf("y = %u, t == %u\n", y, t);
		
		void* root;
		
		while (yacc.n)
		{
			if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
			{
				y = s, push_state(y), push_data(td);
				read_token(zebu_lexer_starts[y]);
			}
			else if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
			{
				unsigned g;
				
				void* d;
				
				ddprintf("r = %u\n", r);
				
				switch (r)
{
	case 28:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 14;
		break;
	}
	case 66:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 21;
		break;
	}
	case 48:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 10;
		break;
	}
	case 21:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 10;
		break;
	}
	case 49:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 11;
		break;
	}
	case 50:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 11;
		break;
	}
	case 63:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 20;
		break;
	}
	case 64:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 20;
		break;
	}
	case 65:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 20;
		break;
	}
	case 25:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 12;
		break;
	}
	case 51:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 12;
		break;
	}
	case 60:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 23;
		break;
	}
	case 68:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 23;
		break;
	}
	case 27:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 24:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 26:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 6;
		break;
	}
	case 42:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 7;
		break;
	}
	case 13:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 7;
		break;
	}
	case 43:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 7;
		break;
	}
	case 44:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 8;
		break;
	}
	case 30:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 15;
		break;
	}
	case 67:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 22;
		break;
	}
	case 32:
	{
		struct __1_a* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 16;
		break;
	}
	case 35:
	{
		struct __1_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 17;
		break;
	}
	case 38:
	{
		struct __1_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 18;
		break;
	}
	case 16:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 47:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 45:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 17:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 46:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 18:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 9;
		break;
	}
	case 52:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 13;
		break;
	}
	case 41:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 19;
		break;
	}
	case 59:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 19;
		break;
	}
	case 61:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 19;
		break;
	}
	case 62:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 19;
		break;
	}
	case 53:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 55:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 54:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 7:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 29:
	{
		struct __0_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 56:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 31:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 8:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 58:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 57:
	{
		struct __0_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __0_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 9:
	{
		struct __1_a* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 34:
	{
		struct __1_a* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_a* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 33:
	{
		struct __1_a* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_a* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 37:
	{
		struct __1_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 4;
		break;
	}
	case 36:
	{
		struct __1_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_b* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 4;
		break;
	}
	case 10:
	{
		struct __1_b* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 4;
		break;
	}
	case 40:
	{
		struct __1_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 11:
	{
		struct __1_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 39:
	{
		struct __1_c* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __1_c* trie = data.data[--yacc.n, --data.n];
			free(trie);
		};
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 5;
		break;
	}
	case 3:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 19:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 4:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 1:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->abc1), value->abc1 = data.data[--yacc.n, --data.n];
		d = value, g = 24;
		break;
	}
	case 14:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 2:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 15:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_a_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 6:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 12:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___0_b_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 20:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free___1_c_tree(data.data[--yacc.n, --data.n]);
		d = value, g = 24;
		break;
	}
	case 5:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->abc1), value->abc1 = data.data[--yacc.n, --data.n];
		d = value, g = 24;
		break;
	}
	case 22:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->abc2), value->abc2 = data.data[--yacc.n, --data.n];
		d = value, g = 24;
		break;
	}
	case 23:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->abc1) { free_token(value->abc1); value->abc1 = trie->abc1; }
			if (trie->abc2) { free_token(value->abc2); value->abc2 = trie->abc2; }
			if (trie->abc3) { free_token(value->abc3); value->abc3 = trie->abc3; }
			free(trie);
		};
		free_token(data.data[--yacc.n, --data.n]);
		free_token(value->abc3), value->abc3 = data.data[--yacc.n, --data.n];
		d = value, g = 24;
		break;
	}
}
				
				if (g == 24)
				{
					free_token(td);
					yacc.n = 0, root = d;
				}
				else
				{
					y = yacc.data[yacc.n - 1];
					
					ddprintf("y = %u\n", y);
					
					assert(y < N(zebu_gotos) && g < N(*zebu_gotos));
					
					s = zebu_gotos[y][g];
					
					ddprintf("s = %u\n", s);
					
					y = s, push_state(y), push_data(d);
				}
			}
			else
			{
				assert(!"190");
			}
		}
		
		assert(!data.n);
		
		puts("accepted!");
		
		print___start___tree(NULL, p_root, "start", root);
		
		free___start___tree(root);
		
		add_history(line);
		
		free(line);
	}
	
	rl_clear_history();
	
	free(yacc.data);
	
	free(data.data);
	
	return 0;
}










