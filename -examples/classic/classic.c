const unsigned zebu_shifts[212][43] = {
	[1][2] = 134,
	[1][3] = 183,
	[1][4] = 190,
	[1][5] = 8,
	[1][6] = 4,
	[1][7] = 16,
	[1][8] = 2,
	[1][9] = 18,
	[1][10] = 100,
	[1][11] = 30,
	[1][23] = 199,
	[1][25] = 197,
	[1][36] = 201,
	[1][37] = 209,
	[1][39] = 211,
	[2][12] = 3,
	[4][15] = 5,
	[5][16] = 6,
	[6][17] = 7,
	[8][15] = 9,
	[9][15] = 10,
	[9][16] = 6,
	[9][18] = 11,
	[9][19] = 14,
	[9][21] = 15,
	[10][15] = 10,
	[10][18] = 11,
	[10][21] = 13,
	[11][20] = 12,
	[14][17] = 7,
	[14][20] = 12,
	[16][15] = 17,
	[17][15] = 10,
	[17][18] = 11,
	[17][21] = 15,
	[18][9] = 19,
	[18][10] = 25,
	[18][11] = 30,
	[18][23] = 98,
	[18][25] = 94,
	[18][29] = 133,
	[19][11] = 20,
	[19][23] = 91,
	[19][28] = 90,
	[20][9] = 21,
	[20][10] = 41,
	[20][11] = 87,
	[20][25] = 88,
	[21][9] = 22,
	[21][10] = 25,
	[21][11] = 30,
	[21][23] = 85,
	[21][25] = 81,
	[22][11] = 23,
	[22][22] = 24,
	[25][9] = 26,
	[25][10] = 78,
	[25][11] = 53,
	[25][23] = 79,
	[26][9] = 27,
	[26][10] = 25,
	[26][11] = 30,
	[26][23] = 76,
	[26][25] = 72,
	[27][10] = 28,
	[27][24] = 29,
	[30][9] = 31,
	[30][10] = 41,
	[30][11] = 69,
	[30][25] = 70,
	[31][9] = 32,
	[31][10] = 25,
	[31][11] = 30,
	[31][23] = 39,
	[31][25] = 35,
	[32][11] = 33,
	[32][22] = 34,
	[35][9] = 36,
	[35][26] = 38,
	[36][11] = 33,
	[36][22] = 37,
	[39][9] = 36,
	[39][26] = 40,
	[41][9] = 42,
	[41][10] = 52,
	[41][11] = 53,
	[41][23] = 67,
	[42][9] = 43,
	[42][10] = 25,
	[42][11] = 30,
	[42][23] = 50,
	[42][25] = 46,
	[43][10] = 44,
	[43][24] = 45,
	[46][9] = 47,
	[46][27] = 49,
	[47][10] = 44,
	[47][24] = 48,
	[50][9] = 47,
	[50][27] = 51,
	[53][9] = 54,
	[53][10] = 41,
	[53][11] = 64,
	[53][25] = 65,
	[54][9] = 55,
	[54][10] = 25,
	[54][11] = 30,
	[54][23] = 62,
	[54][25] = 58,
	[55][11] = 56,
	[55][22] = 57,
	[58][9] = 59,
	[58][26] = 61,
	[59][11] = 56,
	[59][22] = 60,
	[62][9] = 59,
	[62][26] = 63,
	[65][11] = 56,
	[65][22] = 66,
	[67][10] = 44,
	[67][24] = 68,
	[70][11] = 33,
	[70][22] = 71,
	[72][9] = 73,
	[72][27] = 75,
	[73][10] = 28,
	[73][24] = 74,
	[76][9] = 73,
	[76][27] = 77,
	[79][10] = 28,
	[79][24] = 80,
	[81][9] = 82,
	[81][26] = 84,
	[82][11] = 23,
	[82][22] = 83,
	[85][9] = 82,
	[85][26] = 86,
	[88][11] = 23,
	[88][22] = 89,
	[91][9] = 92,
	[91][10] = 100,
	[91][11] = 30,
	[91][23] = 119,
	[91][25] = 115,
	[91][30] = 114,
	[92][9] = 19,
	[92][10] = 25,
	[92][11] = 30,
	[92][23] = 98,
	[92][25] = 94,
	[92][29] = 93,
	[94][9] = 95,
	[94][31] = 97,
	[95][11] = 20,
	[95][23] = 91,
	[95][28] = 96,
	[98][9] = 95,
	[98][31] = 99,
	[100][9] = 101,
	[100][10] = 111,
	[100][11] = 53,
	[100][23] = 112,
	[101][9] = 102,
	[101][10] = 25,
	[101][11] = 30,
	[101][23] = 109,
	[101][25] = 105,
	[102][10] = 103,
	[102][24] = 104,
	[105][9] = 106,
	[105][27] = 108,
	[106][10] = 103,
	[106][24] = 107,
	[109][9] = 106,
	[109][27] = 110,
	[112][10] = 103,
	[112][24] = 113,
	[115][9] = 116,
	[115][11] = 20,
	[115][23] = 131,
	[115][35] = 130,
	[116][9] = 117,
	[116][10] = 25,
	[116][11] = 30,
	[116][23] = 126,
	[116][25] = 122,
	[116][32] = 129,
	[117][9] = 92,
	[117][10] = 100,
	[117][11] = 30,
	[117][23] = 119,
	[117][25] = 115,
	[117][30] = 118,
	[119][9] = 120,
	[119][33] = 128,
	[120][9] = 117,
	[120][10] = 25,
	[120][11] = 30,
	[120][23] = 126,
	[120][25] = 122,
	[120][32] = 121,
	[122][9] = 123,
	[122][34] = 125,
	[123][9] = 92,
	[123][10] = 100,
	[123][11] = 30,
	[123][23] = 119,
	[123][25] = 115,
	[123][30] = 124,
	[126][9] = 123,
	[126][34] = 127,
	[131][9] = 92,
	[131][10] = 100,
	[131][11] = 30,
	[131][23] = 119,
	[131][25] = 115,
	[131][30] = 132,
	[134][2] = 135,
	[134][3] = 136,
	[134][4] = 139,
	[134][37] = 178,
	[134][39] = 181,
	[136][2] = 137,
	[136][3] = 172,
	[136][4] = 149,
	[136][36] = 173,
	[136][39] = 176,
	[137][2] = 138,
	[137][3] = 136,
	[137][4] = 139,
	[137][37] = 167,
	[137][39] = 170,
	[139][2] = 140,
	[139][3] = 147,
	[139][4] = 161,
	[139][36] = 162,
	[139][37] = 165,
	[140][2] = 141,
	[140][3] = 136,
	[140][4] = 139,
	[140][37] = 142,
	[140][39] = 145,
	[142][2] = 143,
	[142][38] = 144,
	[145][2] = 143,
	[145][38] = 146,
	[147][2] = 137,
	[147][3] = 148,
	[147][4] = 149,
	[147][36] = 156,
	[147][39] = 159,
	[149][2] = 140,
	[149][3] = 147,
	[149][4] = 150,
	[149][36] = 151,
	[149][37] = 154,
	[151][4] = 152,
	[151][40] = 153,
	[154][4] = 152,
	[154][40] = 155,
	[156][3] = 157,
	[156][41] = 158,
	[159][3] = 157,
	[159][41] = 160,
	[162][4] = 163,
	[162][40] = 164,
	[165][4] = 163,
	[165][40] = 166,
	[167][2] = 168,
	[167][38] = 169,
	[170][2] = 168,
	[170][38] = 171,
	[173][3] = 174,
	[173][41] = 175,
	[176][3] = 174,
	[176][41] = 177,
	[178][2] = 179,
	[178][38] = 180,
	[181][2] = 179,
	[181][38] = 182,
	[183][2] = 137,
	[183][3] = 184,
	[183][4] = 149,
	[183][36] = 185,
	[183][39] = 188,
	[185][3] = 186,
	[185][41] = 187,
	[188][3] = 186,
	[188][41] = 189,
	[190][2] = 140,
	[190][3] = 147,
	[190][4] = 191,
	[190][36] = 192,
	[190][37] = 195,
	[192][4] = 193,
	[192][40] = 194,
	[195][4] = 193,
	[195][40] = 196,
	[197][9] = 116,
	[197][11] = 20,
	[197][23] = 131,
	[197][35] = 198,
	[199][9] = 120,
	[199][33] = 200,
	[201][2] = 134,
	[201][3] = 183,
	[201][4] = 190,
	[201][36] = 203,
	[201][37] = 205,
	[201][39] = 207,
	[201][42] = 202,
	[203][2] = 134,
	[203][3] = 183,
	[203][4] = 190,
	[203][36] = 203,
	[203][37] = 205,
	[203][39] = 207,
	[203][42] = 204,
	[205][2] = 134,
	[205][3] = 183,
	[205][4] = 190,
	[205][36] = 203,
	[205][37] = 205,
	[205][39] = 207,
	[205][42] = 206,
	[207][2] = 134,
	[207][3] = 183,
	[207][4] = 190,
	[207][36] = 203,
	[207][37] = 205,
	[207][39] = 207,
	[207][42] = 208,
	[209][2] = 134,
	[209][3] = 183,
	[209][4] = 190,
	[209][36] = 203,
	[209][37] = 205,
	[209][39] = 207,
	[209][42] = 210,
	[211][2] = 134,
	[211][3] = 183,
	[211][4] = 190,
	[211][36] = 203,
	[211][37] = 205,
	[211][39] = 207,
	[211][42] = 212,
};
const unsigned zebu_reduces[213][14] = {
	[2][13] = 14,
	[3][13] = 14,
	[7][13] = 14,
	[12][13] = 21,
	[13][13] = 21,
	[15][13] = 14,
	[23][9] = 22,
	[23][10] = 22,
	[23][11] = 22,
	[23][13] = 22,
	[24][9] = 23,
	[24][10] = 23,
	[24][11] = 23,
	[24][13] = 23,
	[28][9] = 24,
	[29][9] = 25,
	[33][9] = 22,
	[34][9] = 23,
	[37][9] = 26,
	[38][9] = 23,
	[40][9] = 23,
	[44][11] = 24,
	[45][11] = 25,
	[48][11] = 27,
	[49][11] = 25,
	[51][11] = 25,
	[52][11] = 25,
	[56][10] = 22,
	[57][10] = 23,
	[60][10] = 26,
	[61][10] = 23,
	[63][10] = 23,
	[64][10] = 23,
	[66][10] = 23,
	[68][11] = 25,
	[69][9] = 23,
	[71][9] = 23,
	[74][9] = 27,
	[75][9] = 25,
	[77][9] = 25,
	[78][9] = 25,
	[80][9] = 25,
	[83][9] = 26,
	[83][10] = 26,
	[83][11] = 26,
	[83][13] = 26,
	[84][9] = 23,
	[84][10] = 23,
	[84][11] = 23,
	[84][13] = 23,
	[86][9] = 23,
	[86][10] = 23,
	[86][11] = 23,
	[86][13] = 23,
	[87][9] = 23,
	[87][10] = 23,
	[87][11] = 23,
	[87][13] = 23,
	[89][9] = 23,
	[89][10] = 23,
	[89][11] = 23,
	[89][13] = 23,
	[90][13] = 29,
	[91][13] = 28,
	[93][13] = 30,
	[96][13] = 31,
	[97][13] = 29,
	[99][13] = 29,
	[103][9] = 24,
	[103][11] = 24,
	[104][9] = 25,
	[104][11] = 25,
	[107][9] = 27,
	[107][11] = 27,
	[108][9] = 25,
	[108][11] = 25,
	[110][9] = 25,
	[110][11] = 25,
	[111][9] = 25,
	[111][11] = 25,
	[113][9] = 25,
	[113][11] = 25,
	[114][13] = 28,
	[117][13] = 32,
	[118][13] = 32,
	[121][13] = 33,
	[123][13] = 34,
	[124][13] = 34,
	[125][13] = 32,
	[127][13] = 32,
	[128][13] = 30,
	[129][13] = 35,
	[130][13] = 30,
	[131][13] = 35,
	[132][13] = 35,
	[133][13] = 14,
	[135][2] = 36,
	[135][3] = 36,
	[135][4] = 36,
	[135][13] = 36,
	[138][3] = 36,
	[141][4] = 36,
	[143][4] = 38,
	[144][4] = 36,
	[146][4] = 36,
	[148][4] = 37,
	[150][3] = 39,
	[152][3] = 40,
	[153][3] = 39,
	[155][3] = 39,
	[157][4] = 41,
	[158][4] = 37,
	[160][4] = 37,
	[161][2] = 39,
	[163][2] = 40,
	[164][2] = 39,
	[166][2] = 39,
	[168][3] = 38,
	[169][3] = 36,
	[171][3] = 36,
	[172][2] = 37,
	[174][2] = 41,
	[175][2] = 37,
	[177][2] = 37,
	[179][2] = 38,
	[179][3] = 38,
	[179][4] = 38,
	[179][13] = 38,
	[180][2] = 36,
	[180][3] = 36,
	[180][4] = 36,
	[180][13] = 36,
	[182][2] = 36,
	[182][3] = 36,
	[182][4] = 36,
	[182][13] = 36,
	[184][2] = 37,
	[184][3] = 37,
	[184][4] = 37,
	[184][13] = 37,
	[186][2] = 41,
	[186][3] = 41,
	[186][4] = 41,
	[186][13] = 41,
	[187][2] = 37,
	[187][3] = 37,
	[187][4] = 37,
	[187][13] = 37,
	[189][2] = 37,
	[189][3] = 37,
	[189][4] = 37,
	[189][13] = 37,
	[191][2] = 39,
	[191][3] = 39,
	[191][4] = 39,
	[191][13] = 39,
	[193][2] = 40,
	[193][3] = 40,
	[193][4] = 40,
	[193][13] = 40,
	[194][2] = 39,
	[194][3] = 39,
	[194][4] = 39,
	[194][13] = 39,
	[196][2] = 39,
	[196][3] = 39,
	[196][4] = 39,
	[196][13] = 39,
	[198][13] = 14,
	[200][13] = 14,
	[201][13] = 14,
	[202][13] = 14,
	[203][13] = 42,
	[204][13] = 42,
	[205][13] = 42,
	[206][13] = 42,
	[207][13] = 42,
	[208][13] = 42,
	[209][13] = 14,
	[210][13] = 14,
	[211][13] = 14,
	[212][13] = 14,
};
const unsigned zebu_popcounts[213][14] = {
	[2][13] = 1,
	[3][13] = 2,
	[7][13] = 4,
	[12][13] = 2,
	[13][13] = 2,
	[15][13] = 3,
	[23][9] = 1,
	[23][10] = 1,
	[23][11] = 1,
	[23][13] = 1,
	[24][9] = 4,
	[24][10] = 4,
	[24][11] = 4,
	[24][13] = 4,
	[28][9] = 1,
	[29][9] = 4,
	[33][9] = 1,
	[34][9] = 4,
	[37][9] = 2,
	[38][9] = 4,
	[40][9] = 4,
	[44][11] = 1,
	[45][11] = 4,
	[48][11] = 2,
	[49][11] = 4,
	[51][11] = 4,
	[52][11] = 2,
	[56][10] = 1,
	[57][10] = 4,
	[60][10] = 2,
	[61][10] = 4,
	[63][10] = 4,
	[64][10] = 2,
	[66][10] = 3,
	[68][11] = 3,
	[69][9] = 2,
	[71][9] = 3,
	[74][9] = 2,
	[75][9] = 4,
	[77][9] = 4,
	[78][9] = 2,
	[80][9] = 3,
	[83][9] = 2,
	[83][10] = 2,
	[83][11] = 2,
	[83][13] = 2,
	[84][9] = 4,
	[84][10] = 4,
	[84][11] = 4,
	[84][13] = 4,
	[86][9] = 4,
	[86][10] = 4,
	[86][11] = 4,
	[86][13] = 4,
	[87][9] = 2,
	[87][10] = 2,
	[87][11] = 2,
	[87][13] = 2,
	[89][9] = 3,
	[89][10] = 3,
	[89][11] = 3,
	[89][13] = 3,
	[90][13] = 2,
	[91][13] = 1,
	[93][13] = 2,
	[96][13] = 2,
	[97][13] = 2,
	[99][13] = 2,
	[103][9] = 1,
	[103][11] = 1,
	[104][9] = 4,
	[104][11] = 4,
	[107][9] = 2,
	[107][11] = 2,
	[108][9] = 4,
	[108][11] = 4,
	[110][9] = 4,
	[110][11] = 4,
	[111][9] = 2,
	[111][11] = 2,
	[113][9] = 3,
	[113][11] = 3,
	[114][13] = 2,
	[117][13] = 1,
	[118][13] = 2,
	[121][13] = 2,
	[123][13] = 1,
	[124][13] = 2,
	[125][13] = 2,
	[127][13] = 2,
	[128][13] = 2,
	[129][13] = 2,
	[130][13] = 2,
	[131][13] = 1,
	[132][13] = 2,
	[133][13] = 2,
	[135][2] = 2,
	[135][3] = 2,
	[135][4] = 2,
	[135][13] = 2,
	[138][3] = 2,
	[141][4] = 2,
	[143][4] = 1,
	[144][4] = 3,
	[146][4] = 3,
	[148][4] = 2,
	[150][3] = 2,
	[152][3] = 1,
	[153][3] = 3,
	[155][3] = 3,
	[157][4] = 1,
	[158][4] = 3,
	[160][4] = 3,
	[161][2] = 2,
	[163][2] = 1,
	[164][2] = 3,
	[166][2] = 3,
	[168][3] = 1,
	[169][3] = 3,
	[171][3] = 3,
	[172][2] = 2,
	[174][2] = 1,
	[175][2] = 3,
	[177][2] = 3,
	[179][2] = 1,
	[179][3] = 1,
	[179][4] = 1,
	[179][13] = 1,
	[180][2] = 3,
	[180][3] = 3,
	[180][4] = 3,
	[180][13] = 3,
	[182][2] = 3,
	[182][3] = 3,
	[182][4] = 3,
	[182][13] = 3,
	[184][2] = 2,
	[184][3] = 2,
	[184][4] = 2,
	[184][13] = 2,
	[186][2] = 1,
	[186][3] = 1,
	[186][4] = 1,
	[186][13] = 1,
	[187][2] = 3,
	[187][3] = 3,
	[187][4] = 3,
	[187][13] = 3,
	[189][2] = 3,
	[189][3] = 3,
	[189][4] = 3,
	[189][13] = 3,
	[191][2] = 2,
	[191][3] = 2,
	[191][4] = 2,
	[191][13] = 2,
	[193][2] = 1,
	[193][3] = 1,
	[193][4] = 1,
	[193][13] = 1,
	[194][2] = 3,
	[194][3] = 3,
	[194][4] = 3,
	[194][13] = 3,
	[196][2] = 3,
	[196][3] = 3,
	[196][4] = 3,
	[196][13] = 3,
	[198][13] = 2,
	[200][13] = 2,
	[201][13] = 1,
	[202][13] = 2,
	[203][13] = 1,
	[204][13] = 2,
	[205][13] = 1,
	[206][13] = 2,
	[207][13] = 1,
	[208][13] = 2,
	[209][13] = 1,
	[210][13] = 2,
	[211][13] = 1,
	[212][13] = 2,
};
const unsigned zebu_lexer[95][123] = {
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
	[28][63] = 30,
	[28][103] = 29,
	[28][104] = 31,
	[29][32] = 29,
	[29][63] = 30,
	[29][103] = 29,
	[31][45] = 31,
	[31][104] = 31,
	[33][104] = 34,
	[34][45] = 34,
	[34][104] = 34,
	[36][32] = 36,
	[36][58] = 37,
	[36][103] = 36,
	[38][32] = 39,
	[38][45] = 39,
	[38][103] = 39,
	[38][119] = 39,
	[38][120] = 39,
	[38][121] = 39,
	[41][32] = 41,
	[41][46] = 42,
	[41][103] = 41,
	[43][32] = 44,
	[43][45] = 48,
	[43][58] = 46,
	[43][103] = 44,
	[43][119] = 48,
	[43][120] = 49,
	[43][121] = 49,
	[43][122] = 47,
	[44][32] = 45,
	[44][58] = 46,
	[44][103] = 45,
	[44][120] = 47,
	[44][121] = 47,
	[44][122] = 47,
	[45][32] = 45,
	[45][58] = 46,
	[45][103] = 45,
	[45][120] = 47,
	[45][121] = 47,
	[45][122] = 47,
	[51][32] = 51,
	[51][58] = 52,
	[51][103] = 51,
	[51][120] = 53,
	[51][121] = 53,
	[51][122] = 53,
	[54][32] = 54,
	[54][33] = 55,
	[54][103] = 54,
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
	[63][32] = 63,
	[63][99] = 64,
	[63][103] = 63,
	[65][32] = 66,
	[65][66] = 67,
	[65][97] = 68,
	[65][98] = 67,
	[65][99] = 69,
	[65][103] = 66,
	[65][104] = 70,
	[66][32] = 66,
	[66][66] = 67,
	[66][97] = 68,
	[66][98] = 67,
	[66][99] = 69,
	[66][103] = 66,
	[70][45] = 70,
	[70][104] = 70,
	[72][32] = 72,
	[72][66] = 73,
	[72][98] = 73,
	[72][103] = 72,
	[74][32] = 74,
	[74][97] = 75,
	[74][103] = 74,
	[76][32] = 76,
	[76][97] = 77,
	[76][99] = 78,
	[76][103] = 76,
	[79][32] = 79,
	[79][65] = 80,
	[79][66] = 81,
	[79][67] = 82,
	[79][103] = 79,
	[83][32] = 84,
	[83][65] = 85,
	[83][66] = 86,
	[83][67] = 87,
	[83][103] = 84,
	[83][104] = 88,
	[84][32] = 84,
	[84][65] = 85,
	[84][66] = 86,
	[84][67] = 87,
	[84][103] = 84,
	[88][45] = 88,
	[88][104] = 88,
	[90][32] = 90,
	[90][66] = 91,
	[90][103] = 90,
	[92][32] = 92,
	[92][67] = 93,
	[92][103] = 92,
	[94][32] = 94,
	[94][65] = 95,
	[94][103] = 94,
};
const unsigned zebu_starts[213] = {
	[1] = 1,
	[2] = 28,
	[3] = 33,
	[4] = 36,
	[5] = 38,
	[6] = 41,
	[7] = 33,
	[8] = 36,
	[9] = 43,
	[10] = 51,
	[11] = 54,
	[12] = 33,
	[13] = 33,
	[14] = 56,
	[15] = 33,
	[16] = 36,
	[17] = 51,
	[18] = 59,
	[19] = 63,
	[20] = 59,
	[21] = 59,
	[22] = 63,
	[23] = 65,
	[24] = 65,
	[25] = 59,
	[26] = 59,
	[27] = 72,
	[28] = 74,
	[29] = 74,
	[30] = 59,
	[31] = 59,
	[32] = 63,
	[33] = 74,
	[34] = 74,
	[35] = 74,
	[36] = 63,
	[37] = 74,
	[38] = 74,
	[39] = 74,
	[40] = 74,
	[41] = 59,
	[42] = 59,
	[43] = 72,
	[44] = 63,
	[45] = 63,
	[46] = 74,
	[47] = 72,
	[48] = 63,
	[49] = 63,
	[50] = 74,
	[51] = 63,
	[52] = 63,
	[53] = 59,
	[54] = 59,
	[55] = 63,
	[56] = 72,
	[57] = 72,
	[58] = 74,
	[59] = 63,
	[60] = 72,
	[61] = 72,
	[62] = 74,
	[63] = 72,
	[64] = 72,
	[65] = 63,
	[66] = 72,
	[67] = 72,
	[68] = 63,
	[69] = 74,
	[70] = 63,
	[71] = 74,
	[72] = 74,
	[73] = 72,
	[74] = 74,
	[75] = 74,
	[76] = 74,
	[77] = 74,
	[78] = 74,
	[79] = 72,
	[80] = 74,
	[81] = 74,
	[82] = 63,
	[83] = 65,
	[84] = 65,
	[85] = 74,
	[86] = 65,
	[87] = 65,
	[88] = 63,
	[89] = 65,
	[90] = 33,
	[91] = 65,
	[92] = 59,
	[93] = 33,
	[94] = 74,
	[95] = 63,
	[96] = 33,
	[97] = 33,
	[98] = 74,
	[99] = 33,
	[100] = 59,
	[101] = 59,
	[102] = 72,
	[103] = 76,
	[104] = 76,
	[105] = 74,
	[106] = 72,
	[107] = 76,
	[108] = 76,
	[109] = 74,
	[110] = 76,
	[111] = 76,
	[112] = 72,
	[113] = 76,
	[114] = 33,
	[115] = 76,
	[116] = 59,
	[117] = 65,
	[118] = 33,
	[119] = 74,
	[120] = 59,
	[121] = 33,
	[122] = 74,
	[123] = 65,
	[124] = 33,
	[125] = 33,
	[126] = 74,
	[127] = 33,
	[128] = 33,
	[129] = 33,
	[130] = 33,
	[131] = 65,
	[132] = 33,
	[133] = 33,
	[134] = 79,
	[135] = 83,
	[136] = 79,
	[137] = 79,
	[138] = 90,
	[139] = 79,
	[140] = 79,
	[141] = 92,
	[142] = 94,
	[143] = 92,
	[144] = 92,
	[145] = 94,
	[146] = 92,
	[147] = 79,
	[148] = 92,
	[149] = 79,
	[150] = 90,
	[151] = 92,
	[152] = 90,
	[153] = 90,
	[154] = 92,
	[155] = 90,
	[156] = 90,
	[157] = 92,
	[158] = 92,
	[159] = 90,
	[160] = 92,
	[161] = 94,
	[162] = 92,
	[163] = 94,
	[164] = 94,
	[165] = 92,
	[166] = 94,
	[167] = 94,
	[168] = 90,
	[169] = 90,
	[170] = 94,
	[171] = 90,
	[172] = 94,
	[173] = 90,
	[174] = 94,
	[175] = 94,
	[176] = 90,
	[177] = 94,
	[178] = 94,
	[179] = 83,
	[180] = 83,
	[181] = 94,
	[182] = 83,
	[183] = 79,
	[184] = 83,
	[185] = 90,
	[186] = 83,
	[187] = 83,
	[188] = 90,
	[189] = 83,
	[190] = 79,
	[191] = 83,
	[192] = 92,
	[193] = 83,
	[194] = 83,
	[195] = 92,
	[196] = 83,
	[197] = 76,
	[198] = 33,
	[199] = 74,
	[200] = 33,
	[201] = 83,
	[202] = 33,
	[203] = 83,
	[204] = 33,
	[205] = 83,
	[206] = 33,
	[207] = 83,
	[208] = 33,
	[209] = 83,
	[210] = 33,
	[211] = 83,
	[212] = 33,
};
const unsigned zebu_defaults[51] = {
	[38] = 40,
	[39] = 39,
	[40] = 39,
	[43] = 50,
	[44] = 48,
	[48] = 48,
	[49] = 48,
	[50] = 48,
};
const unsigned zebu_EOFs[89] = {
	[28] = 32,
	[31] = 32,
	[33] = 35,
	[34] = 35,
	[65] = 71,
	[70] = 71,
	[83] = 89,
	[88] = 89,
};
const unsigned zebu_accepts[96] = {
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
	[32] = 13,
	[35] = 13,
	[37] = 15,
	[38] = 16,
	[39] = 16,
	[42] = 17,
	[43] = 16,
	[44] = 16,
	[46] = 15,
	[47] = 18,
	[48] = 16,
	[49] = 19,
	[52] = 15,
	[53] = 18,
	[55] = 20,
	[57] = 20,
	[58] = 17,
	[60] = 10,
	[61] = 9,
	[62] = 11,
	[64] = 11,
	[67] = 10,
	[68] = 9,
	[69] = 11,
	[71] = 13,
	[73] = 10,
	[75] = 9,
	[77] = 9,
	[78] = 11,
	[80] = 2,
	[81] = 3,
	[82] = 4,
	[85] = 2,
	[86] = 3,
	[87] = 4,
	[89] = 13,
	[91] = 3,
	[93] = 4,
	[95] = 2,
};
const unsigned start_grammar_id = 14;
const char* zebu_grammar_names[44] = {
	[14] = "(start)",
	[22] = "(trie #0)",
	[40] = "(trie #11)",
	[21] = "(trie #13)",
	[29] = "(trie #14)",
	[28] = "(trie #15)",
	[30] = "(trie #16)",
	[35] = "(trie #17)",
	[32] = "(trie #18)",
	[34] = "(trie #19)",
	[26] = "(trie #2)",
	[33] = "(trie #20)",
	[31] = "(trie #21)",
	[42] = "(trie #22)",
	[24] = "(trie #3)",
	[27] = "(trie #5)",
	[38] = "(trie #7)",
	[41] = "(trie #9)",
	[25] = "0.b",
	[23] = "0.c",
	[36] = "1.a",
	[37] = "1.b",
	[39] = "1.c",
};
const char* zebu_token_names[44] = {
	[1] = "0",
	[8] = "1",
	[12] = "2",
	[6] = "3",
	[5] = "3, 7",
	[15] = "4",
	[16] = "5",
	[19] = "5, 8",
	[17] = "6",
	[7] = "7",
	[18] = "8",
	[20] = "9",
	[9] = "10",
	[10] = "11",
	[11] = "12",
	[2] = "13",
	[3] = "14",
	[4] = "15",
	[13] = "16",
};

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct zebu_state
{
	struct { unsigned* data, n, cap; } y;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t;
};

static void ddprintf(struct zebu_state* this, const char* fmt, ...)
{
	for (unsigned i = 0, n = this->y.n; i < n; i++)
		printf("%u ", this->y.data[i]);
	
	printf("| ");
	
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}

static void push(struct zebu_state* this, unsigned ystate)
{
	if (this->y.n + 1 >= this->y.cap)
	{
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
	}
	
	this->y.data[this->y.n++] = ystate;
}

static void append(struct zebu_state* this, const unsigned char* text, size_t length)
{
	while (this->l.n + length >= this->l.cap)
	{
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	memcpy(this->l.data + this->l.n, text, length);
	this->l.n += length;
}

static struct zebu_state* new_zebu_state()
{
	struct zebu_state* this = malloc(sizeof(*this));
	assert(this);
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	this->lstate = 1, this->t = 0;
	push(this, 1);
	return this;
}

static void zebu_reset(struct zebu_state* this)
{
	this->y.n = 0;
	this->l.n = 0;
	this->lstate = 1;
	push(this, 1);
	ddprintf(this, "y = %u, l == %u\n", 1, 1);
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct zebu_state* this, unsigned t)
{
	unsigned b, d, p, y = this->y.data[this->y.n - 1];
	
	while (!(y < N(zebu_shifts) && t < N(*zebu_shifts) && (b = zebu_shifts[y][t])))
	{
		if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (b = zebu_reduces[y][t]))
		{
			ddprintf(this, "b == %u\n", b);
			ddprintf(this, "g == \"%s\"\n", zebu_grammar_names[b]);
			
			if (b == start_grammar_id)
			{
				this->y.n = 0;
				return;
			}
			
			ddprintf(this, "p == %u\n", p = zebu_popcounts[y][t]);
			
			this->y.n -= p;
			
			y = this->y.data[this->y.n - 1];
			ddprintf(this, "y = %u\n", y);
			
			assert(y < N(zebu_shifts) && b < N(*zebu_shifts));
			
			d = zebu_shifts[y][b];
			ddprintf(this, "d = %u\n", d);
			
			push(this, d), y = d;
		}
		else
		{
			assert(!"TODO");
			exit(1);
		}
	}
	
	push(this, b), y = b;
}

static void escape(char *out, unsigned char in)
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

static void zebu_parse(struct zebu_state* this, const unsigned char* text, size_t length)
{
	unsigned c, l = this->lstate;
	unsigned a, b, i, n, f, t = this->t;
	
	char escaped[10];
	
	i = this->l.n;
	
	append(this, text, length);
	
	for (n = this->l.n, f = 0; i < n;)
	{
		c = this->l.data[i];
		
		escape(escaped, c);
		
		ddprintf(this, "c = %s (0x%X)\n", escaped, c);
		
		a = (l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
				ddprintf(this, "l = %u, t == %u, f = %u (saved)\n", l, t, f);
			}
			else
			{
				l = a, i++;
				ddprintf(this, "l == %u\n", l);
			}
		}
		else if (b)
		{
			process_token(this, b);
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
		}
		else if (t)
		{
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
		}
		else
		{
			assert(!"TODO");
		}
	}
	
	memcpy(this->l.data, this->l.data + f, this->l.n = n - f);
	
	this->t = t;
	
	this->lstate = l;
}

static void zebu_parse_EOF(struct zebu_state* this)
{
	unsigned i = this->l.n, n = i, l = this->lstate;
	unsigned a, b, c, f = 0, t = this->t;
	
	char escaped[10];
	
	while (1)
	{
		assert(i <= n + 1);
		
		if (i < n)
		{
			c = this->l.data[i];
			
			escape(escaped, c);
			
			ddprintf(this, "c = %s (0x%X)\n", escaped, c);
		
			a = (c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0) ?: (l < N( zebu_defaults) ? zebu_defaults[l] : 0);
		}
		else
		{
			ddprintf(this, "c == <EOF>\n");
			a = l < N(zebu_EOFs) ? zebu_EOFs[l] : 0;
		}
		
		b = (l < N(zebu_accepts) ? zebu_accepts[l] : 0);
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
				ddprintf(this, "l = %u, t == %u, f = %u (saved)\n", l, t, f);
			}
			else
			{
				l = a, i++;
				ddprintf(this, "l == %u\n", l);
			}
		}
		else if (b)
		{
			process_token(this, b);
			
			if (!this->y.n) break;
			
			l = zebu_starts[this->y.data[this->y.n - 1]], f = i, t = 0;
			ddprintf(this, "l == %u, f = %u, t = %u\n", l, f, t);
		}
		else if (t)
		{
			process_token(this, t);
			l = zebu_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			ddprintf(this, "l == %u, i = %u, t = %u\n", l, i, t);
		}
		else
		{
			assert(!"TODO");
		}
	}
}

static void free_zebu_state(struct zebu_state* this)
{
	free(this->y.data);
	free(this->l.data);
	free(this);
}

int main()
{
	struct zebu_state* new = new_zebu_state();
	
	for (char* line; (line = readline(">>> "));)
	{
		zebu_reset(new);
		
		zebu_parse(new, (unsigned char*) line, strlen(line));
		
		zebu_parse_EOF(new);
		
		puts("accepted!");
		
		add_history(line);
		
		free(line);
	}
	
	free_zebu_state(new);
	
	return 0;
}










