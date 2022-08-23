const unsigned zebu_shifts[244][65] = {
	[1][2] = 240,
	[1][3] = 241,
	[1][4] = 2,
	[2][5] = 3,
	[3][6] = 4,
	[4][7] = 5,
	[5][6] = 6,
	[6][2] = 26,
	[6][3] = 27,
	[6][4] = 7,
	[6][24] = 239,
	[7][9] = 112,
	[7][10] = 88,
	[7][11] = 8,
	[7][36] = 238,
	[8][7] = 9,
	[9][12] = 10,
	[10][13] = 11,
	[11][14] = 12,
	[12][10] = 13,
	[13][2] = 79,
	[13][3] = 80,
	[13][4] = 14,
	[13][34] = 87,
	[14][15] = 15,
	[15][2] = 71,
	[15][3] = 73,
	[15][15] = 70,
	[15][16] = 75,
	[15][17] = 16,
	[15][33] = 78,
	[16][2] = 18,
	[16][3] = 64,
	[16][16] = 66,
	[16][17] = 17,
	[16][32] = 69,
	[17][2] = 18,
	[17][3] = 64,
	[17][16] = 66,
	[17][17] = 17,
	[17][32] = 68,
	[18][2] = 19,
	[18][3] = 20,
	[18][16] = 23,
	[18][30] = 63,
	[19][2] = 19,
	[19][3] = 20,
	[19][16] = 23,
	[19][30] = 62,
	[20][18] = 22,
	[20][19] = 21,
	[20][31] = 61,
	[21][18] = 22,
	[21][19] = 21,
	[21][31] = 60,
	[22][2] = 19,
	[22][3] = 20,
	[22][16] = 23,
	[22][30] = 59,
	[23][2] = 50,
	[23][3] = 51,
	[23][20] = 24,
	[23][28] = 58,
	[24][20] = 25,
	[24][21] = 36,
	[24][22] = 35,
	[24][25] = 49,
	[25][2] = 26,
	[25][3] = 27,
	[25][4] = 7,
	[25][24] = 34,
	[26][2] = 26,
	[26][3] = 27,
	[26][4] = 7,
	[26][24] = 33,
	[27][18] = 29,
	[27][19] = 28,
	[27][23] = 32,
	[28][18] = 29,
	[28][19] = 28,
	[28][23] = 31,
	[29][2] = 26,
	[29][3] = 27,
	[29][4] = 7,
	[29][24] = 30,
	[35][20] = 25,
	[35][21] = 36,
	[35][22] = 35,
	[35][25] = 48,
	[36][17] = 37,
	[36][27] = 47,
	[37][17] = 38,
	[37][20] = 39,
	[37][21] = 43,
	[37][22] = 41,
	[37][26] = 46,
	[38][17] = 38,
	[38][20] = 39,
	[38][21] = 43,
	[38][22] = 41,
	[38][26] = 45,
	[39][2] = 26,
	[39][3] = 27,
	[39][4] = 7,
	[39][24] = 40,
	[41][20] = 25,
	[41][21] = 36,
	[41][22] = 35,
	[41][25] = 42,
	[43][17] = 37,
	[43][27] = 44,
	[50][2] = 50,
	[50][3] = 51,
	[50][20] = 24,
	[50][28] = 57,
	[51][18] = 53,
	[51][19] = 52,
	[51][29] = 56,
	[52][18] = 53,
	[52][19] = 52,
	[52][29] = 55,
	[53][2] = 50,
	[53][3] = 51,
	[53][20] = 24,
	[53][28] = 54,
	[64][18] = 22,
	[64][19] = 21,
	[64][31] = 65,
	[66][2] = 50,
	[66][3] = 51,
	[66][20] = 24,
	[66][28] = 67,
	[70][2] = 71,
	[70][3] = 73,
	[70][15] = 70,
	[70][16] = 75,
	[70][17] = 16,
	[70][33] = 77,
	[71][2] = 19,
	[71][3] = 20,
	[71][16] = 23,
	[71][30] = 72,
	[73][18] = 22,
	[73][19] = 21,
	[73][31] = 74,
	[75][2] = 50,
	[75][3] = 51,
	[75][20] = 24,
	[75][28] = 76,
	[79][2] = 79,
	[79][3] = 80,
	[79][4] = 14,
	[79][34] = 86,
	[80][18] = 82,
	[80][19] = 81,
	[80][35] = 85,
	[81][18] = 82,
	[81][19] = 81,
	[81][35] = 84,
	[82][2] = 79,
	[82][3] = 80,
	[82][4] = 14,
	[82][34] = 83,
	[88][37] = 89,
	[89][38] = 90,
	[90][39] = 91,
	[91][6] = 92,
	[92][37] = 93,
	[93][2] = 229,
	[93][3] = 230,
	[93][4] = 94,
	[93][61] = 237,
	[94][15] = 95,
	[95][2] = 221,
	[95][3] = 223,
	[95][15] = 220,
	[95][16] = 225,
	[95][17] = 96,
	[95][60] = 228,
	[96][2] = 98,
	[96][3] = 214,
	[96][16] = 216,
	[96][17] = 97,
	[96][59] = 219,
	[97][2] = 98,
	[97][3] = 214,
	[97][16] = 216,
	[97][17] = 97,
	[97][59] = 218,
	[98][2] = 99,
	[98][3] = 100,
	[98][16] = 189,
	[98][55] = 213,
	[99][2] = 99,
	[99][3] = 100,
	[99][16] = 189,
	[99][55] = 212,
	[100][18] = 103,
	[100][19] = 101,
	[100][40] = 188,
	[101][18] = 22,
	[101][19] = 21,
	[101][31] = 102,
	[103][2] = 104,
	[103][3] = 105,
	[103][16] = 107,
	[103][41] = 187,
	[104][2] = 104,
	[104][3] = 105,
	[104][16] = 107,
	[104][41] = 186,
	[105][18] = 103,
	[105][19] = 101,
	[105][40] = 106,
	[107][2] = 177,
	[107][3] = 178,
	[107][17] = 175,
	[107][42] = 108,
	[107][53] = 185,
	[108][17] = 109,
	[108][44] = 174,
	[109][2] = 168,
	[109][3] = 170,
	[109][4] = 111,
	[109][17] = 110,
	[109][52] = 173,
	[110][2] = 168,
	[110][3] = 170,
	[110][4] = 111,
	[110][17] = 110,
	[110][52] = 172,
	[111][9] = 112,
	[111][10] = 88,
	[111][11] = 8,
	[111][36] = 167,
	[112][37] = 113,
	[113][38] = 114,
	[114][6] = 115,
	[115][7] = 116,
	[116][2] = 158,
	[116][3] = 159,
	[116][4] = 117,
	[116][50] = 166,
	[117][15] = 118,
	[118][2] = 150,
	[118][3] = 152,
	[118][15] = 149,
	[118][16] = 154,
	[118][17] = 119,
	[118][49] = 157,
	[119][2] = 121,
	[119][3] = 143,
	[119][16] = 145,
	[119][17] = 120,
	[119][48] = 148,
	[120][2] = 121,
	[120][3] = 143,
	[120][16] = 145,
	[120][17] = 120,
	[120][48] = 147,
	[121][2] = 122,
	[121][3] = 123,
	[121][16] = 125,
	[121][43] = 142,
	[122][2] = 122,
	[122][3] = 123,
	[122][16] = 125,
	[122][43] = 141,
	[123][18] = 103,
	[123][19] = 101,
	[123][40] = 124,
	[125][2] = 132,
	[125][3] = 133,
	[125][17] = 126,
	[125][46] = 140,
	[126][4] = 128,
	[126][17] = 127,
	[126][45] = 131,
	[127][4] = 128,
	[127][17] = 127,
	[127][45] = 130,
	[128][17] = 109,
	[128][44] = 129,
	[132][2] = 132,
	[132][3] = 133,
	[132][17] = 126,
	[132][46] = 139,
	[133][18] = 135,
	[133][19] = 134,
	[133][47] = 138,
	[134][18] = 135,
	[134][19] = 134,
	[134][47] = 137,
	[135][2] = 132,
	[135][3] = 133,
	[135][17] = 126,
	[135][46] = 136,
	[143][18] = 103,
	[143][19] = 101,
	[143][40] = 144,
	[145][2] = 132,
	[145][3] = 133,
	[145][17] = 126,
	[145][46] = 146,
	[149][2] = 150,
	[149][3] = 152,
	[149][15] = 149,
	[149][16] = 154,
	[149][17] = 119,
	[149][49] = 156,
	[150][2] = 122,
	[150][3] = 123,
	[150][16] = 125,
	[150][43] = 151,
	[152][18] = 103,
	[152][19] = 101,
	[152][40] = 153,
	[154][2] = 132,
	[154][3] = 133,
	[154][17] = 126,
	[154][46] = 155,
	[158][2] = 158,
	[158][3] = 159,
	[158][4] = 117,
	[158][50] = 165,
	[159][18] = 161,
	[159][19] = 160,
	[159][51] = 164,
	[160][18] = 161,
	[160][19] = 160,
	[160][51] = 163,
	[161][2] = 158,
	[161][3] = 159,
	[161][4] = 117,
	[161][50] = 162,
	[168][2] = 26,
	[168][3] = 27,
	[168][4] = 7,
	[168][24] = 169,
	[170][18] = 29,
	[170][19] = 28,
	[170][23] = 171,
	[175][2] = 168,
	[175][3] = 170,
	[175][4] = 111,
	[175][17] = 110,
	[175][52] = 176,
	[177][2] = 177,
	[177][3] = 178,
	[177][17] = 175,
	[177][42] = 108,
	[177][53] = 184,
	[178][18] = 180,
	[178][19] = 179,
	[178][54] = 183,
	[179][18] = 180,
	[179][19] = 179,
	[179][54] = 182,
	[180][2] = 177,
	[180][3] = 178,
	[180][17] = 175,
	[180][42] = 108,
	[180][53] = 181,
	[189][2] = 203,
	[189][3] = 204,
	[189][17] = 201,
	[189][42] = 190,
	[189][57] = 211,
	[190][17] = 191,
	[191][2] = 193,
	[191][3] = 195,
	[191][16] = 197,
	[191][17] = 192,
	[191][56] = 200,
	[192][2] = 193,
	[192][3] = 195,
	[192][16] = 197,
	[192][17] = 192,
	[192][56] = 199,
	[193][2] = 104,
	[193][3] = 105,
	[193][16] = 107,
	[193][41] = 194,
	[195][18] = 103,
	[195][19] = 101,
	[195][40] = 196,
	[197][2] = 177,
	[197][3] = 178,
	[197][17] = 175,
	[197][42] = 108,
	[197][53] = 198,
	[201][2] = 193,
	[201][3] = 195,
	[201][16] = 197,
	[201][17] = 192,
	[201][56] = 202,
	[203][2] = 203,
	[203][3] = 204,
	[203][17] = 201,
	[203][42] = 190,
	[203][57] = 210,
	[204][18] = 206,
	[204][19] = 205,
	[204][58] = 209,
	[205][18] = 206,
	[205][19] = 205,
	[205][58] = 208,
	[206][2] = 203,
	[206][3] = 204,
	[206][17] = 201,
	[206][42] = 190,
	[206][57] = 207,
	[214][18] = 103,
	[214][19] = 101,
	[214][40] = 215,
	[216][2] = 203,
	[216][3] = 204,
	[216][17] = 201,
	[216][42] = 190,
	[216][57] = 217,
	[220][2] = 221,
	[220][3] = 223,
	[220][15] = 220,
	[220][16] = 225,
	[220][17] = 96,
	[220][60] = 227,
	[221][2] = 99,
	[221][3] = 100,
	[221][16] = 189,
	[221][55] = 222,
	[223][18] = 103,
	[223][19] = 101,
	[223][40] = 224,
	[225][2] = 203,
	[225][3] = 204,
	[225][17] = 201,
	[225][42] = 190,
	[225][57] = 226,
	[229][2] = 229,
	[229][3] = 230,
	[229][4] = 94,
	[229][61] = 236,
	[230][18] = 232,
	[230][19] = 231,
	[230][62] = 235,
	[231][18] = 232,
	[231][19] = 231,
	[231][62] = 234,
	[232][2] = 229,
	[232][3] = 230,
	[232][4] = 94,
	[232][61] = 233,
	[240][2] = 240,
	[240][3] = 241,
	[240][4] = 2,
	[240][63] = 247,
	[241][18] = 243,
	[241][19] = 242,
	[241][64] = 246,
	[242][18] = 243,
	[242][19] = 242,
	[242][64] = 245,
	[243][2] = 240,
	[243][3] = 241,
	[243][4] = 2,
	[243][63] = 244,
};
const unsigned zebu_reduces[248][9] = {
	[6][8] = 63,
	[25][8] = 25,
	[26][8] = 24,
	[29][8] = 23,
	[30][8] = 23,
	[31][8] = 23,
	[32][8] = 24,
	[33][8] = 24,
	[34][8] = 25,
	[39][8] = 26,
	[40][8] = 26,
	[42][8] = 26,
	[44][8] = 26,
	[45][8] = 26,
	[46][8] = 27,
	[47][8] = 25,
	[48][8] = 25,
	[49][8] = 28,
	[54][8] = 29,
	[55][8] = 29,
	[56][8] = 28,
	[57][8] = 28,
	[58][8] = 30,
	[59][8] = 31,
	[60][8] = 31,
	[61][8] = 30,
	[62][8] = 30,
	[63][8] = 32,
	[65][8] = 32,
	[67][8] = 32,
	[68][8] = 32,
	[69][8] = 33,
	[72][8] = 33,
	[74][8] = 33,
	[76][8] = 33,
	[77][8] = 33,
	[78][8] = 34,
	[83][8] = 35,
	[84][8] = 35,
	[85][8] = 34,
	[86][8] = 34,
	[87][8] = 36,
	[102][8] = 40,
	[106][8] = 41,
	[109][8] = 44,
	[110][8] = 52,
	[124][8] = 43,
	[129][8] = 45,
	[130][8] = 45,
	[131][8] = 46,
	[136][8] = 47,
	[137][8] = 47,
	[138][8] = 46,
	[139][8] = 46,
	[140][8] = 43,
	[141][8] = 43,
	[142][8] = 48,
	[144][8] = 48,
	[146][8] = 48,
	[147][8] = 48,
	[148][8] = 49,
	[151][8] = 49,
	[153][8] = 49,
	[155][8] = 49,
	[156][8] = 49,
	[157][8] = 50,
	[162][8] = 51,
	[163][8] = 51,
	[164][8] = 50,
	[165][8] = 50,
	[166][8] = 36,
	[167][8] = 52,
	[168][8] = 52,
	[169][8] = 52,
	[171][8] = 52,
	[172][8] = 52,
	[173][8] = 44,
	[174][8] = 53,
	[175][8] = 53,
	[176][8] = 53,
	[181][8] = 54,
	[182][8] = 54,
	[183][8] = 53,
	[184][8] = 53,
	[185][8] = 41,
	[186][8] = 41,
	[187][8] = 40,
	[188][8] = 55,
	[194][8] = 56,
	[196][8] = 56,
	[198][8] = 56,
	[199][8] = 56,
	[200][8] = 57,
	[202][8] = 57,
	[207][8] = 58,
	[208][8] = 58,
	[209][8] = 57,
	[210][8] = 57,
	[211][8] = 55,
	[212][8] = 55,
	[213][8] = 59,
	[215][8] = 59,
	[217][8] = 59,
	[218][8] = 59,
	[219][8] = 60,
	[222][8] = 60,
	[224][8] = 60,
	[226][8] = 60,
	[227][8] = 60,
	[228][8] = 61,
	[233][8] = 62,
	[234][8] = 62,
	[235][8] = 61,
	[236][8] = 61,
	[237][8] = 36,
	[238][8] = 24,
	[239][8] = 63,
	[244][8] = 64,
	[245][8] = 64,
	[246][8] = 63,
	[247][8] = 63,
};
const unsigned zebu_popcounts[248][9] = {
	[6][8] = 5,
	[25][8] = 1,
	[26][8] = 1,
	[29][8] = 1,
	[30][8] = 2,
	[31][8] = 2,
	[32][8] = 2,
	[33][8] = 2,
	[34][8] = 2,
	[39][8] = 1,
	[40][8] = 2,
	[42][8] = 2,
	[44][8] = 2,
	[45][8] = 2,
	[46][8] = 2,
	[47][8] = 2,
	[48][8] = 2,
	[49][8] = 2,
	[54][8] = 2,
	[55][8] = 2,
	[56][8] = 2,
	[57][8] = 2,
	[58][8] = 2,
	[59][8] = 2,
	[60][8] = 2,
	[61][8] = 2,
	[62][8] = 2,
	[63][8] = 2,
	[65][8] = 2,
	[67][8] = 2,
	[68][8] = 2,
	[69][8] = 2,
	[72][8] = 2,
	[74][8] = 2,
	[76][8] = 2,
	[77][8] = 2,
	[78][8] = 3,
	[83][8] = 2,
	[84][8] = 2,
	[85][8] = 2,
	[86][8] = 2,
	[87][8] = 7,
	[102][8] = 2,
	[106][8] = 2,
	[109][8] = 1,
	[110][8] = 1,
	[124][8] = 2,
	[129][8] = 2,
	[130][8] = 2,
	[131][8] = 2,
	[136][8] = 2,
	[137][8] = 2,
	[138][8] = 2,
	[139][8] = 2,
	[140][8] = 2,
	[141][8] = 2,
	[142][8] = 2,
	[144][8] = 2,
	[146][8] = 2,
	[147][8] = 2,
	[148][8] = 2,
	[151][8] = 2,
	[153][8] = 2,
	[155][8] = 2,
	[156][8] = 2,
	[157][8] = 3,
	[162][8] = 2,
	[163][8] = 2,
	[164][8] = 2,
	[165][8] = 2,
	[166][8] = 6,
	[167][8] = 2,
	[168][8] = 1,
	[169][8] = 2,
	[171][8] = 2,
	[172][8] = 2,
	[173][8] = 2,
	[174][8] = 2,
	[175][8] = 1,
	[176][8] = 2,
	[181][8] = 2,
	[182][8] = 2,
	[183][8] = 2,
	[184][8] = 2,
	[185][8] = 2,
	[186][8] = 2,
	[187][8] = 2,
	[188][8] = 2,
	[194][8] = 2,
	[196][8] = 2,
	[198][8] = 2,
	[199][8] = 2,
	[200][8] = 3,
	[202][8] = 2,
	[207][8] = 2,
	[208][8] = 2,
	[209][8] = 2,
	[210][8] = 2,
	[211][8] = 2,
	[212][8] = 2,
	[213][8] = 2,
	[215][8] = 2,
	[217][8] = 2,
	[218][8] = 2,
	[219][8] = 2,
	[222][8] = 2,
	[224][8] = 2,
	[226][8] = 2,
	[227][8] = 2,
	[228][8] = 3,
	[233][8] = 2,
	[234][8] = 2,
	[235][8] = 2,
	[236][8] = 2,
	[237][8] = 7,
	[238][8] = 2,
	[239][8] = 6,
	[244][8] = 2,
	[245][8] = 2,
	[246][8] = 2,
	[247][8] = 2,
};
const unsigned zebu_lexer[87][123] = {
	[1][9] = 2,
	[1][10] = 2,
	[1][32] = 2,
	[1][35] = 3,
	[1][46] = 4,
	[5][100] = 6,
	[7][97] = 8,
	[9][116] = 10,
	[11][9] = 12,
	[11][10] = 12,
	[11][32] = 12,
	[11][35] = 13,
	[11][46] = 14,
	[16][102] = 17,
	[16][103] = 18,
	[16][115] = 19,
	[20][114] = 21,
	[22][105] = 23,
	[24][110] = 25,
	[26][103] = 27,
	[28][65] = 29,
	[28][66] = 29,
	[28][67] = 29,
	[28][68] = 29,
	[28][69] = 29,
	[28][70] = 29,
	[28][71] = 29,
	[28][72] = 29,
	[28][73] = 29,
	[28][74] = 29,
	[28][75] = 29,
	[28][76] = 29,
	[28][77] = 29,
	[28][78] = 29,
	[28][79] = 29,
	[28][80] = 29,
	[28][81] = 29,
	[28][82] = 29,
	[28][83] = 29,
	[28][84] = 29,
	[28][85] = 29,
	[28][86] = 29,
	[28][87] = 29,
	[28][88] = 29,
	[28][89] = 29,
	[28][90] = 29,
	[28][95] = 29,
	[28][97] = 29,
	[28][98] = 29,
	[28][99] = 29,
	[28][100] = 29,
	[28][101] = 29,
	[28][102] = 29,
	[28][103] = 29,
	[28][104] = 29,
	[28][105] = 29,
	[28][106] = 29,
	[28][107] = 29,
	[28][108] = 29,
	[28][109] = 29,
	[28][110] = 29,
	[28][111] = 29,
	[28][112] = 29,
	[28][113] = 29,
	[28][114] = 29,
	[28][115] = 29,
	[28][116] = 29,
	[28][117] = 29,
	[28][118] = 29,
	[28][119] = 29,
	[28][120] = 29,
	[28][121] = 29,
	[28][122] = 29,
	[30][9] = 31,
	[30][10] = 31,
	[30][32] = 31,
	[30][35] = 32,
	[30][44] = 33,
	[30][48] = 34,
	[30][49] = 34,
	[30][50] = 34,
	[30][51] = 34,
	[30][52] = 34,
	[30][53] = 34,
	[30][54] = 34,
	[30][55] = 34,
	[30][56] = 34,
	[30][57] = 34,
	[30][65] = 35,
	[30][66] = 35,
	[30][67] = 35,
	[30][68] = 35,
	[30][69] = 35,
	[30][70] = 35,
	[30][71] = 35,
	[30][72] = 35,
	[30][73] = 35,
	[30][74] = 35,
	[30][75] = 35,
	[30][76] = 35,
	[30][77] = 35,
	[30][78] = 35,
	[30][79] = 35,
	[30][80] = 35,
	[30][81] = 35,
	[30][82] = 35,
	[30][83] = 35,
	[30][84] = 35,
	[30][85] = 35,
	[30][86] = 35,
	[30][87] = 35,
	[30][88] = 35,
	[30][89] = 35,
	[30][90] = 35,
	[30][95] = 35,
	[30][97] = 35,
	[30][98] = 35,
	[30][99] = 35,
	[30][100] = 35,
	[30][101] = 35,
	[30][102] = 35,
	[30][103] = 35,
	[30][104] = 35,
	[30][105] = 35,
	[30][106] = 35,
	[30][107] = 35,
	[30][108] = 35,
	[30][109] = 35,
	[30][110] = 35,
	[30][111] = 35,
	[30][112] = 35,
	[30][113] = 35,
	[30][114] = 35,
	[30][115] = 35,
	[30][116] = 35,
	[30][117] = 35,
	[30][118] = 35,
	[30][119] = 35,
	[30][120] = 35,
	[30][121] = 35,
	[30][122] = 35,
	[36][9] = 37,
	[36][10] = 37,
	[36][32] = 37,
	[36][35] = 38,
	[36][44] = 39,
	[36][48] = 40,
	[36][49] = 40,
	[36][50] = 40,
	[36][51] = 40,
	[36][52] = 40,
	[36][53] = 40,
	[36][54] = 40,
	[36][55] = 40,
	[36][56] = 40,
	[36][57] = 40,
	[41][9] = 42,
	[41][10] = 42,
	[41][32] = 42,
	[41][35] = 43,
	[41][44] = 44,
	[45][10] = 46,
	[48][9] = 49,
	[48][10] = 49,
	[48][32] = 49,
	[48][34] = 50,
	[48][35] = 51,
	[52][34] = 53,
	[52][92] = 54,
	[58][48] = 59,
	[58][49] = 59,
	[58][50] = 59,
	[58][51] = 59,
	[58][52] = 59,
	[58][53] = 59,
	[58][54] = 59,
	[58][55] = 59,
	[58][56] = 59,
	[58][57] = 59,
	[60][34] = 61,
	[60][48] = 62,
	[60][49] = 62,
	[60][50] = 62,
	[60][51] = 62,
	[60][52] = 62,
	[60][53] = 62,
	[60][54] = 62,
	[60][55] = 62,
	[60][56] = 62,
	[60][57] = 62,
	[60][92] = 63,
	[65][108] = 66,
	[67][111] = 68,
	[69][98] = 70,
	[71][9] = 72,
	[71][10] = 72,
	[71][32] = 72,
	[71][35] = 73,
	[71][43] = 74,
	[71][45] = 74,
	[71][48] = 75,
	[71][49] = 75,
	[71][50] = 75,
	[71][51] = 75,
	[71][52] = 75,
	[71][53] = 75,
	[71][54] = 75,
	[71][55] = 75,
	[71][56] = 75,
	[71][57] = 75,
	[76][9] = 77,
	[76][10] = 77,
	[76][32] = 77,
	[76][35] = 78,
	[76][46] = 79,
	[76][48] = 80,
	[76][49] = 80,
	[76][50] = 80,
	[76][51] = 80,
	[76][52] = 80,
	[76][53] = 80,
	[76][54] = 80,
	[76][55] = 80,
	[76][56] = 80,
	[76][57] = 80,
	[82][9] = 83,
	[82][10] = 83,
	[82][32] = 83,
	[82][35] = 84,
	[82][48] = 85,
	[82][49] = 85,
	[82][50] = 85,
	[82][51] = 85,
	[82][52] = 85,
	[82][53] = 85,
	[82][54] = 85,
	[82][55] = 85,
	[82][56] = 85,
	[82][57] = 85,
	[86][46] = 87,
	[86][48] = 88,
	[86][49] = 88,
	[86][50] = 88,
	[86][51] = 88,
	[86][52] = 88,
	[86][53] = 88,
	[86][54] = 88,
	[86][55] = 88,
	[86][56] = 88,
	[86][57] = 88,
};
const unsigned zebu_starts[248] = {
	[1] = 1,
	[2] = 5,
	[3] = 7,
	[4] = 9,
	[5] = 7,
	[6] = 11,
	[7] = 16,
	[8] = 9,
	[9] = 20,
	[10] = 22,
	[11] = 24,
	[12] = 26,
	[13] = 1,
	[14] = 28,
	[15] = 30,
	[16] = 36,
	[17] = 36,
	[18] = 41,
	[19] = 41,
	[20] = 45,
	[21] = 45,
	[22] = 41,
	[23] = 48,
	[24] = 52,
	[25] = 11,
	[26] = 11,
	[27] = 45,
	[28] = 45,
	[29] = 11,
	[30] = 56,
	[31] = 56,
	[32] = 56,
	[33] = 56,
	[34] = 56,
	[35] = 52,
	[36] = 58,
	[37] = 60,
	[38] = 60,
	[39] = 11,
	[40] = 56,
	[41] = 52,
	[42] = 56,
	[43] = 58,
	[44] = 56,
	[45] = 56,
	[46] = 56,
	[47] = 56,
	[48] = 56,
	[49] = 56,
	[50] = 48,
	[51] = 45,
	[52] = 45,
	[53] = 48,
	[54] = 56,
	[55] = 56,
	[56] = 56,
	[57] = 56,
	[58] = 56,
	[59] = 56,
	[60] = 56,
	[61] = 56,
	[62] = 56,
	[63] = 56,
	[64] = 45,
	[65] = 56,
	[66] = 48,
	[67] = 56,
	[68] = 56,
	[69] = 56,
	[70] = 30,
	[71] = 41,
	[72] = 56,
	[73] = 45,
	[74] = 56,
	[75] = 48,
	[76] = 56,
	[77] = 56,
	[78] = 56,
	[79] = 1,
	[80] = 45,
	[81] = 45,
	[82] = 1,
	[83] = 56,
	[84] = 56,
	[85] = 56,
	[86] = 56,
	[87] = 56,
	[88] = 65,
	[89] = 67,
	[90] = 69,
	[91] = 7,
	[92] = 65,
	[93] = 1,
	[94] = 28,
	[95] = 30,
	[96] = 36,
	[97] = 36,
	[98] = 41,
	[99] = 41,
	[100] = 45,
	[101] = 45,
	[102] = 56,
	[103] = 41,
	[104] = 41,
	[105] = 45,
	[106] = 56,
	[107] = 71,
	[108] = 58,
	[109] = 76,
	[110] = 76,
	[111] = 16,
	[112] = 65,
	[113] = 67,
	[114] = 7,
	[115] = 9,
	[116] = 1,
	[117] = 28,
	[118] = 30,
	[119] = 36,
	[120] = 36,
	[121] = 41,
	[122] = 41,
	[123] = 45,
	[124] = 56,
	[125] = 82,
	[126] = 86,
	[127] = 86,
	[128] = 58,
	[129] = 56,
	[130] = 56,
	[131] = 56,
	[132] = 82,
	[133] = 45,
	[134] = 45,
	[135] = 82,
	[136] = 56,
	[137] = 56,
	[138] = 56,
	[139] = 56,
	[140] = 56,
	[141] = 56,
	[142] = 56,
	[143] = 45,
	[144] = 56,
	[145] = 82,
	[146] = 56,
	[147] = 56,
	[148] = 56,
	[149] = 30,
	[150] = 41,
	[151] = 56,
	[152] = 45,
	[153] = 56,
	[154] = 82,
	[155] = 56,
	[156] = 56,
	[157] = 56,
	[158] = 1,
	[159] = 45,
	[160] = 45,
	[161] = 1,
	[162] = 56,
	[163] = 56,
	[164] = 56,
	[165] = 56,
	[166] = 56,
	[167] = 56,
	[168] = 11,
	[169] = 56,
	[170] = 45,
	[171] = 56,
	[172] = 56,
	[173] = 56,
	[174] = 56,
	[175] = 76,
	[176] = 56,
	[177] = 71,
	[178] = 45,
	[179] = 45,
	[180] = 71,
	[181] = 56,
	[182] = 56,
	[183] = 56,
	[184] = 56,
	[185] = 56,
	[186] = 56,
	[187] = 56,
	[188] = 56,
	[189] = 71,
	[190] = 58,
	[191] = 36,
	[192] = 36,
	[193] = 41,
	[194] = 56,
	[195] = 45,
	[196] = 56,
	[197] = 71,
	[198] = 56,
	[199] = 56,
	[200] = 56,
	[201] = 36,
	[202] = 56,
	[203] = 71,
	[204] = 45,
	[205] = 45,
	[206] = 71,
	[207] = 56,
	[208] = 56,
	[209] = 56,
	[210] = 56,
	[211] = 56,
	[212] = 56,
	[213] = 56,
	[214] = 45,
	[215] = 56,
	[216] = 71,
	[217] = 56,
	[218] = 56,
	[219] = 56,
	[220] = 30,
	[221] = 41,
	[222] = 56,
	[223] = 45,
	[224] = 56,
	[225] = 71,
	[226] = 56,
	[227] = 56,
	[228] = 56,
	[229] = 1,
	[230] = 45,
	[231] = 45,
	[232] = 1,
	[233] = 56,
	[234] = 56,
	[235] = 56,
	[236] = 56,
	[237] = 56,
	[238] = 56,
	[239] = 56,
	[240] = 1,
	[241] = 45,
	[242] = 45,
	[243] = 1,
	[244] = 56,
	[245] = 56,
	[246] = 56,
	[247] = 56,
};
const unsigned zebu_defaults[61] = {
	[45] = 47,
	[52] = 55,
	[60] = 64,
};
const unsigned zebu_EOFs[77] = {
	[11] = 15,
	[56] = 57,
	[76] = 81,
};
const unsigned zebu_accepts[89] = {
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[6] = 5,
	[8] = 6,
	[10] = 7,
	[12] = 2,
	[13] = 3,
	[14] = 4,
	[15] = 8,
	[17] = 9,
	[18] = 10,
	[19] = 11,
	[21] = 12,
	[23] = 13,
	[25] = 14,
	[27] = 10,
	[29] = 15,
	[31] = 2,
	[32] = 3,
	[33] = 16,
	[34] = 17,
	[35] = 15,
	[37] = 2,
	[38] = 3,
	[39] = 16,
	[40] = 17,
	[42] = 2,
	[43] = 3,
	[44] = 16,
	[46] = 18,
	[47] = 19,
	[49] = 2,
	[50] = 20,
	[51] = 3,
	[53] = 20,
	[54] = 21,
	[55] = 22,
	[57] = 8,
	[59] = 17,
	[61] = 20,
	[62] = 17,
	[63] = 21,
	[64] = 22,
	[66] = 37,
	[68] = 38,
	[70] = 39,
	[72] = 2,
	[73] = 3,
	[74] = 42,
	[75] = 17,
	[77] = 2,
	[78] = 3,
	[79] = 4,
	[80] = 17,
	[81] = 8,
	[83] = 2,
	[84] = 3,
	[85] = 17,
	[87] = 4,
	[88] = 17,
};
const unsigned start_grammar_id = 63;
const char* zebu_grammar_names[66] = {
	[63] = "(start)",
	[24] = "(trie #0)",
	[36] = "(trie #1)",
	[26] = "(trie #10)",
	[29] = "(trie #11)",
	[35] = "(trie #12)",
	[61] = "(trie #13)",
	[60] = "(trie #14)",
	[59] = "(trie #15)",
	[55] = "(trie #16)",
	[40] = "(trie #17)",
	[41] = "(trie #18)",
	[53] = "(trie #19)",
	[34] = "(trie #2)",
	[44] = "(trie #20)",
	[52] = "(trie #21)",
	[23] = "(trie #22)",
	[54] = "(trie #23)",
	[57] = "(trie #24)",
	[56] = "(trie #25)",
	[58] = "(trie #26)",
	[62] = "(trie #27)",
	[50] = "(trie #28)",
	[49] = "(trie #29)",
	[33] = "(trie #3)",
	[48] = "(trie #30)",
	[43] = "(trie #31)",
	[46] = "(trie #32)",
	[45] = "(trie #33)",
	[47] = "(trie #34)",
	[51] = "(trie #35)",
	[64] = "(trie #36)",
	[32] = "(trie #4)",
	[30] = "(trie #5)",
	[31] = "(trie #6)",
	[28] = "(trie #7)",
	[25] = "(trie #8)",
	[27] = "(trie #9)",
};

#define _GNU_SOURCE

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#define argv0 (program_invocation_name)

#define N(array) (sizeof(array) / sizeof(*array))

struct cmdln
{
	const char* input;
};

void usage(int code)
{
	fprintf(stderr, "usage: %s <path/to/input/file>\n", argv0);
	exit(code);
}

struct cmdln* process_cmdln(int argc, char* const* argv)
{
	int opt;
	
	const char* input = NULL;
	
	while ((opt = getopt(argc, argv, "h")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			
			default:
				usage(1);
		}
	}
	
	input = argv[optind++];
	
	if (!input)
		usage(1);
	
	struct cmdln* retval = malloc(sizeof(*retval));
	assert(retval);
	retval->input = input;
	return retval;
}

struct lexer { unsigned char* data; unsigned n, cap; };

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

unsigned read_token(struct lexer* lexer, FILE* stream, unsigned state)
{
	void append(unsigned char c)
	{
		while (lexer->n + 1 >= lexer->cap)
		{
			lexer->cap = lexer->cap << 1 ?: 1;
			printf("lexer->cap == %u\n", lexer->cap);
			lexer->data = realloc(lexer->data, lexer->cap);
		}
		
		lexer->data[lexer->n++] = c;
	}
	
	unsigned i = 0;
	
	unsigned token = 0, fallback;
	
	printf("state = %u\n", state);
	
	while (1)
	{
		unsigned next, accept, c;
		
		if (i < lexer->n)
		{
			c = lexer->data[i];
			
			char escaped[10];
			
			escape(escaped, c);
			
			printf("c = %s (0x%X)\n", escaped, c);
			
			next = 0
				?: (c < N(*zebu_lexer) ? zebu_lexer[state][c] : 0)
				?: (state < N( zebu_defaults) ? zebu_defaults[state] : 0);
		}
		else if ((c = getc(stream)) != EOF)
		{
			append(c);
			
			char escaped[10];
			
			escape(escaped, c);
			
			printf("c = %s (0x%X)\n", escaped, c);
			
			next = 0
				?: (c < N(*zebu_lexer) ? zebu_lexer[state][c] : 0)
				?: (state < N( zebu_defaults) ? zebu_defaults[state] : 0);
		}
		else
		{
			c = EOF;
			
			printf("c = <EOF>\n");
			
			next = state < N(zebu_EOFs) ? zebu_EOFs[state] : 0;
		}
		
		accept = (state < N(zebu_accepts) ? zebu_accepts[state] : 0);
		
		if (next)
		{
			if (accept)
			{
				state = next, token = accept, fallback = i++;
				printf("state = %u\n", state);
			}
			else
			{
				state = next, i++;
				printf("state = %u\n", state);
			}
		}
		else if (accept)
		{
			lexer->n = 0;
			if (c != EOF) lexer->data[lexer->n++] = c;
			return accept;
		}
		else if (token)
		{
			memmove(lexer->data, lexer->data + fallback, lexer->n - fallback);
			lexer->n -= fallback;
			return token;
		}
		else
		{
			assert(!"168");
		}
	}
}

void parse(FILE* stream)
{
	struct { unsigned* data, n, cap; } stack = {};
	struct lexer lexer = {};
	
	void push(unsigned y)
	{
		if (stack.n + 1 >= stack.cap)
		{
			stack.cap = stack.cap << 1 ?: 1;
			stack.data = realloc(stack.data, sizeof(*stack.data) * stack.cap);
		}
		stack.data[stack.n++] = y;
	}
	
	push(1);
	
	unsigned g = 0, t = read_token(&lexer, stream, 1);
	
	while (stack.n)
	{
		unsigned y = stack.data[stack.n - 1], s, r;
		
		{
			for (unsigned i = 0, n = stack.n; i < n; i++)
			{
				printf("%u", stack.data[i]);
				
				if (i + 1 < n)
					printf(" | ");
			}
			puts("");
		}
		
		if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][g ?: t]))
		{
			push(s);
			if (g) g = 0;
			else t = read_token(&lexer, stream, zebu_starts[s]);
		}
		else if (y < N(zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
		{
			if (r == start_grammar_id)
				stack.n = 0;
			else
				stack.n -= zebu_popcounts[y][t], g = r;
		}
		else
		{
			assert(!"266");
		}
	}
	
	free(stack.data);
	free(lexer.data);
}

int main(int argc, char* const* argv)
{
	struct cmdln* cmdln = process_cmdln(argc, argv);
	
	FILE* input = fopen(cmdln->input, "r");
	
	if (!input)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, cmdln->input),
		exit(1);
	}
	
	parse(input);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















