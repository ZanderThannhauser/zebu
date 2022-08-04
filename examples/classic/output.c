const unsigned zebu_shifts[93][40] = {
	[1][2] = 41,
	[1][3] = 39,
	[1][4] = 45,
	[1][5] = 14,
	[1][6] = 10,
	[1][7] = 17,
	[1][8] = 2,
	[1][9] = 18,
	[1][10] = 20,
	[1][11] = 22,
	[1][15] = 94,
	[1][22] = 62,
	[1][23] = 78,
	[1][24] = 80,
	[1][29] = 90,
	[1][30] = 82,
	[1][31] = 92,
	[2][12] = 4,
	[2][13] = 3,
	[4][12] = 5,
	[4][16] = 6,
	[4][18] = 9,
	[5][12] = 5,
	[5][16] = 6,
	[5][18] = 8,
	[6][17] = 7,
	[10][12] = 11,
	[11][19] = 12,
	[12][20] = 13,
	[14][12] = 15,
	[15][12] = 5,
	[15][16] = 6,
	[15][18] = 9,
	[15][19] = 12,
	[15][21] = 16,
	[16][17] = 7,
	[16][20] = 13,
	[17][12] = 4,
	[18][9] = 19,
	[18][10] = 20,
	[18][11] = 22,
	[18][23] = 34,
	[18][24] = 37,
	[20][9] = 18,
	[20][10] = 21,
	[20][11] = 22,
	[20][22] = 29,
	[20][24] = 32,
	[22][9] = 18,
	[22][10] = 20,
	[22][11] = 23,
	[22][22] = 24,
	[22][23] = 27,
	[24][11] = 25,
	[24][25] = 26,
	[27][11] = 25,
	[27][25] = 28,
	[29][10] = 30,
	[29][26] = 31,
	[32][10] = 30,
	[32][26] = 33,
	[34][9] = 35,
	[34][27] = 36,
	[37][9] = 35,
	[37][27] = 38,
	[39][2] = 41,
	[39][3] = 40,
	[39][4] = 45,
	[39][9] = 18,
	[39][10] = 21,
	[39][11] = 22,
	[39][22] = 29,
	[39][24] = 32,
	[39][30] = 52,
	[39][31] = 55,
	[41][2] = 42,
	[41][4] = 45,
	[41][28] = 43,
	[41][29] = 57,
	[41][31] = 60,
	[43][2] = 41,
	[43][4] = 45,
	[43][28] = 44,
	[43][30] = 52,
	[43][31] = 55,
	[45][2] = 41,
	[45][4] = 46,
	[45][28] = 43,
	[45][29] = 50,
	[45][30] = 47,
	[47][4] = 48,
	[47][32] = 49,
	[50][4] = 48,
	[50][32] = 51,
	[52][28] = 53,
	[52][33] = 54,
	[55][28] = 53,
	[55][33] = 56,
	[57][2] = 58,
	[57][34] = 59,
	[60][2] = 58,
	[60][34] = 61,
	[62][11] = 22,
	[62][24] = 64,
	[62][35] = 63,
	[64][9] = 18,
	[64][10] = 20,
	[64][11] = 22,
	[64][22] = 66,
	[64][23] = 68,
	[64][24] = 72,
	[64][36] = 65,
	[66][11] = 22,
	[66][24] = 64,
	[66][35] = 67,
	[68][9] = 18,
	[68][11] = 22,
	[68][22] = 70,
	[68][24] = 76,
	[68][37] = 69,
	[70][9] = 18,
	[70][10] = 20,
	[70][11] = 22,
	[70][22] = 66,
	[70][23] = 68,
	[70][24] = 72,
	[70][36] = 71,
	[72][9] = 18,
	[72][22] = 74,
	[72][38] = 73,
	[74][9] = 18,
	[74][10] = 20,
	[74][11] = 22,
	[74][22] = 66,
	[74][23] = 68,
	[74][24] = 72,
	[74][36] = 75,
	[76][9] = 18,
	[76][10] = 20,
	[76][11] = 22,
	[76][22] = 66,
	[76][23] = 68,
	[76][24] = 72,
	[76][36] = 77,
	[78][9] = 18,
	[78][11] = 22,
	[78][22] = 70,
	[78][24] = 76,
	[78][37] = 79,
	[80][9] = 18,
	[80][22] = 74,
	[80][38] = 81,
	[82][2] = 41,
	[82][4] = 45,
	[82][28] = 43,
	[82][29] = 86,
	[82][30] = 84,
	[82][31] = 88,
	[82][39] = 83,
	[84][2] = 41,
	[84][4] = 45,
	[84][28] = 43,
	[84][29] = 86,
	[84][30] = 84,
	[84][31] = 88,
	[84][39] = 85,
	[86][2] = 41,
	[86][4] = 45,
	[86][28] = 43,
	[86][29] = 86,
	[86][30] = 84,
	[86][31] = 88,
	[86][39] = 87,
	[88][2] = 41,
	[88][4] = 45,
	[88][28] = 43,
	[88][29] = 86,
	[88][30] = 84,
	[88][31] = 88,
	[88][39] = 89,
	[90][2] = 41,
	[90][4] = 45,
	[90][28] = 43,
	[90][29] = 86,
	[90][30] = 84,
	[90][31] = 88,
	[90][39] = 91,
	[92][2] = 41,
	[92][4] = 45,
	[92][28] = 43,
	[92][29] = 86,
	[92][30] = 84,
	[92][31] = 88,
	[92][39] = 93,
};
const unsigned zebu_reduces[95][29] = {
	[2][14] = 15,
	[3][14] = 15,
	[7][14] = 18,
	[8][14] = 18,
	[9][14] = 15,
	[13][14] = 15,
	[19][9] = 22,
	[19][10] = 22,
	[19][11] = 22,
	[19][14] = 22,
	[21][9] = 23,
	[21][11] = 23,
	[23][9] = 24,
	[23][10] = 24,
	[23][11] = 24,
	[23][14] = 24,
	[25][9] = 25,
	[25][10] = 25,
	[25][11] = 25,
	[25][14] = 25,
	[26][9] = 24,
	[26][10] = 24,
	[26][11] = 24,
	[26][14] = 24,
	[28][9] = 24,
	[28][10] = 24,
	[28][11] = 24,
	[28][14] = 24,
	[30][9] = 26,
	[30][11] = 26,
	[31][9] = 23,
	[31][11] = 23,
	[33][9] = 23,
	[33][11] = 23,
	[35][9] = 27,
	[35][10] = 27,
	[35][11] = 27,
	[35][14] = 27,
	[36][9] = 22,
	[36][10] = 22,
	[36][11] = 22,
	[36][14] = 22,
	[38][9] = 22,
	[38][10] = 22,
	[38][11] = 22,
	[38][14] = 22,
	[40][2] = 29,
	[40][4] = 29,
	[40][9] = 23,
	[40][11] = 23,
	[40][14] = 29,
	[40][28] = 29,
	[42][2] = 30,
	[42][4] = 30,
	[42][14] = 30,
	[42][28] = 30,
	[44][2] = 29,
	[44][4] = 29,
	[44][14] = 29,
	[44][28] = 29,
	[46][2] = 31,
	[46][4] = 31,
	[46][14] = 31,
	[46][28] = 31,
	[48][2] = 32,
	[48][4] = 32,
	[48][14] = 32,
	[48][28] = 32,
	[49][2] = 31,
	[49][4] = 31,
	[49][14] = 31,
	[49][28] = 31,
	[51][2] = 31,
	[51][4] = 31,
	[51][14] = 31,
	[51][28] = 31,
	[53][2] = 33,
	[53][4] = 33,
	[53][14] = 33,
	[53][28] = 33,
	[54][2] = 29,
	[54][4] = 29,
	[54][14] = 29,
	[54][28] = 29,
	[56][2] = 29,
	[56][4] = 29,
	[56][14] = 29,
	[56][28] = 29,
	[58][2] = 34,
	[58][4] = 34,
	[58][14] = 34,
	[58][28] = 34,
	[59][2] = 30,
	[59][4] = 30,
	[59][14] = 30,
	[59][28] = 30,
	[61][2] = 30,
	[61][4] = 30,
	[61][14] = 30,
	[61][28] = 30,
	[63][14] = 15,
	[64][14] = 35,
	[65][14] = 35,
	[67][14] = 36,
	[69][14] = 36,
	[70][14] = 37,
	[71][14] = 37,
	[73][14] = 36,
	[74][14] = 38,
	[75][14] = 38,
	[76][14] = 37,
	[77][14] = 37,
	[79][14] = 15,
	[81][14] = 15,
	[82][14] = 15,
	[83][14] = 15,
	[84][14] = 39,
	[85][14] = 39,
	[86][14] = 39,
	[87][14] = 39,
	[88][14] = 39,
	[89][14] = 39,
	[90][14] = 15,
	[91][14] = 15,
	[92][14] = 15,
	[93][14] = 15,
	[94][14] = 40,
};
const unsigned zebu_popcounts[95][29] = {
	[2][14] = 1,
	[3][14] = 2,
	[7][14] = 2,
	[8][14] = 2,
	[9][14] = 3,
	[13][14] = 4,
	[19][9] = 2,
	[19][10] = 2,
	[19][11] = 2,
	[19][14] = 2,
	[21][9] = 2,
	[21][11] = 2,
	[23][9] = 2,
	[23][10] = 2,
	[23][11] = 2,
	[23][14] = 2,
	[25][9] = 1,
	[25][10] = 1,
	[25][11] = 1,
	[25][14] = 1,
	[26][9] = 3,
	[26][10] = 3,
	[26][11] = 3,
	[26][14] = 3,
	[28][9] = 3,
	[28][10] = 3,
	[28][11] = 3,
	[28][14] = 3,
	[30][9] = 1,
	[30][11] = 1,
	[31][9] = 3,
	[31][11] = 3,
	[33][9] = 3,
	[33][11] = 3,
	[35][9] = 1,
	[35][10] = 1,
	[35][11] = 1,
	[35][14] = 1,
	[36][9] = 3,
	[36][10] = 3,
	[36][11] = 3,
	[36][14] = 3,
	[38][9] = 3,
	[38][10] = 3,
	[38][11] = 3,
	[38][14] = 3,
	[40][2] = 2,
	[40][4] = 2,
	[40][9] = 2,
	[40][11] = 2,
	[40][14] = 2,
	[40][28] = 2,
	[42][2] = 2,
	[42][4] = 2,
	[42][14] = 2,
	[42][28] = 2,
	[44][2] = 2,
	[44][4] = 2,
	[44][14] = 2,
	[44][28] = 2,
	[46][2] = 2,
	[46][4] = 2,
	[46][14] = 2,
	[46][28] = 2,
	[48][2] = 1,
	[48][4] = 1,
	[48][14] = 1,
	[48][28] = 1,
	[49][2] = 3,
	[49][4] = 3,
	[49][14] = 3,
	[49][28] = 3,
	[51][2] = 3,
	[51][4] = 3,
	[51][14] = 3,
	[51][28] = 3,
	[53][2] = 1,
	[53][4] = 1,
	[53][14] = 1,
	[53][28] = 1,
	[54][2] = 3,
	[54][4] = 3,
	[54][14] = 3,
	[54][28] = 3,
	[56][2] = 3,
	[56][4] = 3,
	[56][14] = 3,
	[56][28] = 3,
	[58][2] = 1,
	[58][4] = 1,
	[58][14] = 1,
	[58][28] = 1,
	[59][2] = 3,
	[59][4] = 3,
	[59][14] = 3,
	[59][28] = 3,
	[61][2] = 3,
	[61][4] = 3,
	[61][14] = 3,
	[61][28] = 3,
	[63][14] = 2,
	[64][14] = 1,
	[65][14] = 2,
	[67][14] = 2,
	[69][14] = 2,
	[70][14] = 1,
	[71][14] = 2,
	[73][14] = 2,
	[74][14] = 1,
	[75][14] = 2,
	[76][14] = 1,
	[77][14] = 2,
	[79][14] = 2,
	[81][14] = 2,
	[82][14] = 1,
	[83][14] = 2,
	[84][14] = 1,
	[85][14] = 2,
	[86][14] = 1,
	[87][14] = 2,
	[88][14] = 1,
	[89][14] = 2,
	[90][14] = 1,
	[91][14] = 2,
	[92][14] = 1,
	[93][14] = 2,
	[94][14] = 1,
};
const unsigned zebu_lexer[111][123] = {
	[1][32] = 1,
	[1][65] = 2,
	[1][66] = 3,
	[1][67] = 4,
	[1][97] = 5,
	[1][98] = 26,
	[1][99] = 27,
	[1][103] = 1,
	[5][97] = 6,
	[5][98] = 24,
	[6][97] = 7,
	[6][98] = 13,
	[7][97] = 8,
	[7][98] = 14,
	[8][97] = 9,
	[8][98] = 15,
	[9][97] = 10,
	[9][98] = 16,
	[10][97] = 11,
	[10][98] = 17,
	[11][97] = 6,
	[11][98] = 12,
	[12][98] = 13,
	[12][99] = 19,
	[13][98] = 14,
	[13][99] = 20,
	[14][98] = 15,
	[14][99] = 21,
	[15][98] = 16,
	[15][99] = 22,
	[16][98] = 17,
	[16][99] = 23,
	[17][98] = 12,
	[17][99] = 18,
	[18][99] = 19,
	[19][99] = 20,
	[20][99] = 21,
	[21][99] = 22,
	[22][99] = 23,
	[23][99] = 18,
	[24][98] = 13,
	[24][99] = 25,
	[25][99] = 20,
	[28][32] = 29,
	[28][58] = 30,
	[28][63] = 31,
	[28][103] = 29,
	[28][104] = 32,
	[29][32] = 29,
	[29][58] = 30,
	[29][63] = 31,
	[29][103] = 29,
	[32][104] = 32,
	[34][104] = 34,
	[36][32] = 36,
	[36][58] = 37,
	[36][103] = 36,
	[36][120] = 38,
	[36][121] = 38,
	[36][122] = 38,
	[39][32] = 39,
	[39][33] = 40,
	[39][103] = 39,
	[41][32] = 41,
	[41][58] = 42,
	[41][103] = 41,
	[43][32] = 44,
	[43][103] = 44,
	[43][119] = 44,
	[43][120] = 44,
	[43][121] = 44,
	[46][32] = 46,
	[46][46] = 47,
	[46][103] = 46,
	[48][32] = 49,
	[48][58] = 51,
	[48][103] = 49,
	[48][119] = 53,
	[48][120] = 54,
	[48][121] = 54,
	[48][122] = 52,
	[49][32] = 50,
	[49][58] = 51,
	[49][103] = 50,
	[49][120] = 52,
	[49][121] = 52,
	[49][122] = 52,
	[50][32] = 50,
	[50][58] = 51,
	[50][103] = 50,
	[50][120] = 52,
	[50][121] = 52,
	[50][122] = 52,
	[56][32] = 56,
	[56][33] = 57,
	[56][46] = 58,
	[56][103] = 56,
	[59][32] = 59,
	[59][66] = 60,
	[59][97] = 61,
	[59][98] = 60,
	[59][99] = 62,
	[59][103] = 59,
	[63][32] = 64,
	[63][66] = 65,
	[63][97] = 66,
	[63][98] = 65,
	[63][99] = 67,
	[63][103] = 64,
	[63][104] = 68,
	[64][32] = 64,
	[64][66] = 65,
	[64][97] = 66,
	[64][98] = 65,
	[64][99] = 67,
	[64][103] = 64,
	[68][104] = 68,
	[70][32] = 70,
	[70][97] = 71,
	[70][99] = 72,
	[70][103] = 70,
	[73][32] = 73,
	[73][99] = 74,
	[73][103] = 73,
	[75][32] = 75,
	[75][66] = 76,
	[75][98] = 76,
	[75][103] = 75,
	[77][32] = 77,
	[77][97] = 78,
	[77][103] = 77,
	[79][32] = 79,
	[79][65] = 80,
	[79][66] = 81,
	[79][67] = 82,
	[79][97] = 83,
	[79][98] = 84,
	[79][99] = 85,
	[79][103] = 79,
	[86][32] = 87,
	[86][65] = 88,
	[86][66] = 89,
	[86][67] = 90,
	[86][97] = 91,
	[86][99] = 92,
	[86][103] = 87,
	[86][104] = 93,
	[87][32] = 87,
	[87][65] = 88,
	[87][66] = 89,
	[87][67] = 90,
	[87][97] = 91,
	[87][99] = 92,
	[87][103] = 87,
	[93][104] = 93,
	[95][32] = 95,
	[95][65] = 96,
	[95][66] = 97,
	[95][67] = 98,
	[95][103] = 95,
	[99][32] = 100,
	[99][65] = 101,
	[99][66] = 102,
	[99][67] = 103,
	[99][103] = 100,
	[99][104] = 104,
	[100][32] = 100,
	[100][65] = 101,
	[100][66] = 102,
	[100][67] = 103,
	[100][103] = 100,
	[104][104] = 104,
	[106][32] = 106,
	[106][67] = 107,
	[106][103] = 106,
	[108][32] = 108,
	[108][66] = 109,
	[108][103] = 108,
	[110][32] = 110,
	[110][65] = 111,
	[110][103] = 110,
};
const unsigned zebu_starts[95] = {
	[1] = 1,
	[2] = 28,
	[3] = 34,
	[4] = 36,
	[5] = 36,
	[6] = 39,
	[7] = 34,
	[8] = 34,
	[9] = 34,
	[10] = 41,
	[11] = 43,
	[12] = 46,
	[13] = 34,
	[14] = 41,
	[15] = 48,
	[16] = 56,
	[17] = 41,
	[18] = 59,
	[19] = 63,
	[20] = 59,
	[21] = 70,
	[22] = 59,
	[23] = 63,
	[24] = 73,
	[25] = 63,
	[26] = 63,
	[27] = 73,
	[28] = 63,
	[29] = 75,
	[30] = 70,
	[31] = 70,
	[32] = 75,
	[33] = 70,
	[34] = 77,
	[35] = 63,
	[36] = 63,
	[37] = 77,
	[38] = 63,
	[39] = 79,
	[40] = 86,
	[41] = 95,
	[42] = 99,
	[43] = 95,
	[44] = 99,
	[45] = 95,
	[46] = 99,
	[47] = 106,
	[48] = 99,
	[49] = 99,
	[50] = 106,
	[51] = 99,
	[52] = 108,
	[53] = 99,
	[54] = 99,
	[55] = 108,
	[56] = 99,
	[57] = 110,
	[58] = 99,
	[59] = 99,
	[60] = 110,
	[61] = 99,
	[62] = 73,
	[63] = 34,
	[64] = 63,
	[65] = 34,
	[66] = 73,
	[67] = 34,
	[68] = 70,
	[69] = 34,
	[70] = 63,
	[71] = 34,
	[72] = 77,
	[73] = 34,
	[74] = 63,
	[75] = 34,
	[76] = 63,
	[77] = 34,
	[78] = 70,
	[79] = 34,
	[80] = 77,
	[81] = 34,
	[82] = 99,
	[83] = 34,
	[84] = 99,
	[85] = 34,
	[86] = 99,
	[87] = 34,
	[88] = 99,
	[89] = 34,
	[90] = 99,
	[91] = 34,
	[92] = 99,
	[93] = 34,
	[94] = 34,
};
const unsigned zebu_defaults[56] = {
	[43] = 45,
	[44] = 44,
	[45] = 44,
	[48] = 55,
	[49] = 53,
	[53] = 53,
	[54] = 53,
	[55] = 53,
};
const unsigned zebu_EOFs[105] = {
	[28] = 33,
	[32] = 33,
	[34] = 35,
	[63] = 69,
	[68] = 69,
	[86] = 94,
	[93] = 94,
	[99] = 105,
	[104] = 105,
};
const unsigned zebu_accepts[112] = {
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 9,
	[18] = 6,
	[19] = 7,
	[20] = 6,
	[22] = 5,
	[25] = 8,
	[26] = 10,
	[27] = 11,
	[30] = 12,
	[31] = 13,
	[33] = 14,
	[35] = 14,
	[37] = 12,
	[38] = 16,
	[40] = 17,
	[42] = 12,
	[43] = 19,
	[44] = 19,
	[47] = 20,
	[48] = 19,
	[49] = 19,
	[51] = 12,
	[52] = 16,
	[53] = 19,
	[54] = 21,
	[57] = 17,
	[58] = 20,
	[60] = 10,
	[61] = 9,
	[62] = 11,
	[65] = 10,
	[66] = 9,
	[67] = 11,
	[69] = 14,
	[71] = 9,
	[72] = 11,
	[74] = 11,
	[76] = 10,
	[78] = 9,
	[80] = 2,
	[81] = 3,
	[82] = 4,
	[83] = 9,
	[84] = 10,
	[85] = 11,
	[88] = 2,
	[89] = 28,
	[90] = 4,
	[91] = 9,
	[92] = 11,
	[94] = 14,
	[96] = 2,
	[97] = 28,
	[98] = 4,
	[101] = 2,
	[102] = 28,
	[103] = 4,
	[105] = 14,
	[107] = 4,
	[109] = 28,
	[111] = 2,
};
const unsigned start_grammar_id = 40;
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
struct zebu_state {
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};
static void push(struct zebu_state* this, unsigned ystate) {
	if (this->y.n + 1 >= this->y.cap) {
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
	}
	this->y.data[this->y.n++] = ystate;
}
static void append(struct zebu_state* this, const unsigned char* text, size_t length) {
	while (this->l.n + length >= this->l.cap) {
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	memcpy(this->l.data + this->l.n, text, length);
	this->l.n += length;
}
struct zebu_state* new_zebu_state() {
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}
void zebu_reset(struct zebu_state* this) {
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
}
#define N(array) (sizeof(array) / sizeof(*array))
static void process_token(struct zebu_state* this, unsigned t) {
	unsigned b, d, y = this->y.data[this->y.n - 1];
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t]))) {
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t])) {
			if (b == start_grammar_id) {
				this->y.n = 0;
				return;
			}
			this->y.n -= zebu_popcounts[y][t];
			y = this->y.data[this->y.n - 1];
			assert(y < N(zebu_shifts) && b < N(*zebu_shifts));
			d = zebu_shifts[y][b];
			push(this, d), y = d;
		} else {
			assert(!"TODO");
			exit(1);
		}
	}
	push(this, b), y = b;
}
void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length) {
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	i = this->l.n;
	append(this, text, length);
	for (n = this->l.n, f = 0; i < n;) {
		c = this->l.data[i];
		a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		if (a) {
			if (b)
				l = a, t = b, f = i++;
			else
				l = a, i++;
		} else if (b) {
			process_token(this, b);
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
		} else if (t) {
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		} else {
			assert(!"TODO");
		}
	}
	memcpy(this->l.data, this->l.data + f, this->l.n = n - f);
	this->t = t;
	this->lstate = l;
}
void zebu_parse_EOF(struct zebu_state* this) {
	unsigned i = this->l.n, n = i, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	while (1) {
		assert(i <= n + 1);
		if (i < n) {
			c = this->l.data[i];
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		} else {
			a = l < N(zebu_EOFs) ? zebu_EOFs[l] : 0;
		}
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		if (a) {
			if (b)
				l = a, t = b, f = i++;
			else
				l = a, i++;
		} else if (b) {
			process_token(this, b);
			if (!this->y.n) break;
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i + 1, t = 0;
			if (f >= n) break;
		} else if (t) {
			process_token(this, t);
			if (!this->y.n) break;
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
		} else {
			assert(!"TODO");
		}
	}
}
void free_zebu_state(struct zebu_state* this) {
	free(this->y.data);
	free(this->l.data);
	free(this);
}
