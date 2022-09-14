#include "csv.h"

#define _GNU_SOURCE

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

const unsigned zebu_shifts[8][5] = {
	[1][2] = 2,
	[2][3] = 4,
	[2][4] = 5,
	[3][2] = 2,
	[4][2] = 2,
	[7][2] = 2,
};


const unsigned zebu_reduces[10][6] = {
	[3][5] = 1,
	[5][2] = 2,
	[5][5] = 2,
	[6][5] = 3,
	[7][5] = 4,
	[8][2] = 5,
	[8][5] = 5,
	[9][5] = 6,
};


const unsigned zebu_gotos[8][3] = {
	[1][1] = 3,
	[3][1] = 7,
	[3][2] = 6,
	[4][1] = 8,
	[7][1] = 7,
	[7][2] = 9,
};


const unsigned zebu_lexer[7][256] = {
	[1][0] = 1,
	[1][1] = 1,
	[1][2] = 1,
	[1][3] = 1,
	[1][4] = 1,
	[1][5] = 1,
	[1][6] = 1,
	[1][7] = 1,
	[1][8] = 1,
	[1][9] = 1,
	[1][11] = 1,
	[1][12] = 1,
	[1][13] = 1,
	[1][14] = 1,
	[1][15] = 1,
	[1][16] = 1,
	[1][17] = 1,
	[1][18] = 1,
	[1][19] = 1,
	[1][20] = 1,
	[1][21] = 1,
	[1][22] = 1,
	[1][23] = 1,
	[1][24] = 1,
	[1][25] = 1,
	[1][26] = 1,
	[1][27] = 1,
	[1][28] = 1,
	[1][29] = 1,
	[1][30] = 1,
	[1][31] = 1,
	[1][32] = 1,
	[1][33] = 1,
	[1][34] = 5,
	[1][35] = 1,
	[1][36] = 1,
	[1][37] = 1,
	[1][38] = 1,
	[1][39] = 1,
	[1][40] = 1,
	[1][41] = 1,
	[1][42] = 1,
	[1][43] = 1,
	[1][45] = 1,
	[1][46] = 1,
	[1][47] = 1,
	[1][48] = 1,
	[1][49] = 1,
	[1][50] = 1,
	[1][51] = 1,
	[1][52] = 1,
	[1][53] = 1,
	[1][54] = 1,
	[1][55] = 1,
	[1][56] = 1,
	[1][57] = 1,
	[1][58] = 1,
	[1][59] = 1,
	[1][60] = 1,
	[1][61] = 1,
	[1][62] = 1,
	[1][63] = 1,
	[1][64] = 1,
	[1][65] = 1,
	[1][66] = 1,
	[1][67] = 1,
	[1][68] = 1,
	[1][69] = 1,
	[1][70] = 1,
	[1][71] = 1,
	[1][72] = 1,
	[1][73] = 1,
	[1][74] = 1,
	[1][75] = 1,
	[1][76] = 1,
	[1][77] = 1,
	[1][78] = 1,
	[1][79] = 1,
	[1][80] = 1,
	[1][81] = 1,
	[1][82] = 1,
	[1][83] = 1,
	[1][84] = 1,
	[1][85] = 1,
	[1][86] = 1,
	[1][87] = 1,
	[1][88] = 1,
	[1][89] = 1,
	[1][90] = 1,
	[1][91] = 1,
	[1][92] = 1,
	[1][93] = 1,
	[1][94] = 1,
	[1][95] = 1,
	[1][96] = 1,
	[1][97] = 1,
	[1][98] = 1,
	[1][99] = 1,
	[1][100] = 1,
	[1][101] = 1,
	[1][102] = 1,
	[1][103] = 1,
	[1][104] = 1,
	[1][105] = 1,
	[1][106] = 1,
	[1][107] = 1,
	[1][108] = 1,
	[1][109] = 1,
	[1][110] = 1,
	[1][111] = 1,
	[1][112] = 1,
	[1][113] = 1,
	[1][114] = 1,
	[1][115] = 1,
	[1][116] = 1,
	[1][117] = 1,
	[1][118] = 1,
	[1][119] = 1,
	[1][120] = 1,
	[1][121] = 1,
	[1][122] = 1,
	[1][123] = 1,
	[1][124] = 1,
	[1][125] = 1,
	[1][126] = 1,
	[1][127] = 1,
	[1][128] = 1,
	[1][129] = 1,
	[1][130] = 1,
	[1][131] = 1,
	[1][132] = 1,
	[1][133] = 1,
	[1][134] = 1,
	[1][135] = 1,
	[1][136] = 1,
	[1][137] = 1,
	[1][138] = 1,
	[1][139] = 1,
	[1][140] = 1,
	[1][141] = 1,
	[1][142] = 1,
	[1][143] = 1,
	[1][144] = 1,
	[1][145] = 1,
	[1][146] = 1,
	[1][147] = 1,
	[1][148] = 1,
	[1][149] = 1,
	[1][150] = 1,
	[1][151] = 1,
	[1][152] = 1,
	[1][153] = 1,
	[1][154] = 1,
	[1][155] = 1,
	[1][156] = 1,
	[1][157] = 1,
	[1][158] = 1,
	[1][159] = 1,
	[1][160] = 1,
	[1][161] = 1,
	[1][162] = 1,
	[1][163] = 1,
	[1][164] = 1,
	[1][165] = 1,
	[1][166] = 1,
	[1][167] = 1,
	[1][168] = 1,
	[1][169] = 1,
	[1][170] = 1,
	[1][171] = 1,
	[1][172] = 1,
	[1][173] = 1,
	[1][174] = 1,
	[1][175] = 1,
	[1][176] = 1,
	[1][177] = 1,
	[1][178] = 1,
	[1][179] = 1,
	[1][180] = 1,
	[1][181] = 1,
	[1][182] = 1,
	[1][183] = 1,
	[1][184] = 1,
	[1][185] = 1,
	[1][186] = 1,
	[1][187] = 1,
	[1][188] = 1,
	[1][189] = 1,
	[1][190] = 1,
	[1][191] = 1,
	[1][192] = 1,
	[1][193] = 1,
	[1][194] = 1,
	[1][195] = 1,
	[1][196] = 1,
	[1][197] = 1,
	[1][198] = 1,
	[1][199] = 1,
	[1][200] = 1,
	[1][201] = 1,
	[1][202] = 1,
	[1][203] = 1,
	[1][204] = 1,
	[1][205] = 1,
	[1][206] = 1,
	[1][207] = 1,
	[1][208] = 1,
	[1][209] = 1,
	[1][210] = 1,
	[1][211] = 1,
	[1][212] = 1,
	[1][213] = 1,
	[1][214] = 1,
	[1][215] = 1,
	[1][216] = 1,
	[1][217] = 1,
	[1][218] = 1,
	[1][219] = 1,
	[1][220] = 1,
	[1][221] = 1,
	[1][222] = 1,
	[1][223] = 1,
	[1][224] = 1,
	[1][225] = 1,
	[1][226] = 1,
	[1][227] = 1,
	[1][228] = 1,
	[1][229] = 1,
	[1][230] = 1,
	[1][231] = 1,
	[1][232] = 1,
	[1][233] = 1,
	[1][234] = 1,
	[1][235] = 1,
	[1][236] = 1,
	[1][237] = 1,
	[1][238] = 1,
	[1][239] = 1,
	[1][240] = 1,
	[1][241] = 1,
	[1][242] = 1,
	[1][243] = 1,
	[1][244] = 1,
	[1][245] = 1,
	[1][246] = 1,
	[1][247] = 1,
	[1][248] = 1,
	[1][249] = 1,
	[1][250] = 1,
	[1][251] = 1,
	[1][252] = 1,
	[1][253] = 1,
	[1][254] = 1,
	[1][255] = 1,
	[2][10] = 6,
	[2][44] = 7,
	[3][0] = 1,
	[3][1] = 1,
	[3][2] = 1,
	[3][3] = 1,
	[3][4] = 1,
	[3][5] = 1,
	[3][6] = 1,
	[3][7] = 1,
	[3][8] = 1,
	[3][9] = 1,
	[3][11] = 1,
	[3][12] = 1,
	[3][13] = 1,
	[3][14] = 1,
	[3][15] = 1,
	[3][16] = 1,
	[3][17] = 1,
	[3][18] = 1,
	[3][19] = 1,
	[3][20] = 1,
	[3][21] = 1,
	[3][22] = 1,
	[3][23] = 1,
	[3][24] = 1,
	[3][25] = 1,
	[3][26] = 1,
	[3][27] = 1,
	[3][28] = 1,
	[3][29] = 1,
	[3][30] = 1,
	[3][31] = 1,
	[3][32] = 1,
	[3][33] = 1,
	[3][34] = 5,
	[3][35] = 1,
	[3][36] = 1,
	[3][37] = 1,
	[3][38] = 1,
	[3][39] = 1,
	[3][40] = 1,
	[3][41] = 1,
	[3][42] = 1,
	[3][43] = 1,
	[3][45] = 1,
	[3][46] = 1,
	[3][47] = 1,
	[3][48] = 1,
	[3][49] = 1,
	[3][50] = 1,
	[3][51] = 1,
	[3][52] = 1,
	[3][53] = 1,
	[3][54] = 1,
	[3][55] = 1,
	[3][56] = 1,
	[3][57] = 1,
	[3][58] = 1,
	[3][59] = 1,
	[3][60] = 1,
	[3][61] = 1,
	[3][62] = 1,
	[3][63] = 1,
	[3][64] = 1,
	[3][65] = 1,
	[3][66] = 1,
	[3][67] = 1,
	[3][68] = 1,
	[3][69] = 1,
	[3][70] = 1,
	[3][71] = 1,
	[3][72] = 1,
	[3][73] = 1,
	[3][74] = 1,
	[3][75] = 1,
	[3][76] = 1,
	[3][77] = 1,
	[3][78] = 1,
	[3][79] = 1,
	[3][80] = 1,
	[3][81] = 1,
	[3][82] = 1,
	[3][83] = 1,
	[3][84] = 1,
	[3][85] = 1,
	[3][86] = 1,
	[3][87] = 1,
	[3][88] = 1,
	[3][89] = 1,
	[3][90] = 1,
	[3][91] = 1,
	[3][92] = 1,
	[3][93] = 1,
	[3][94] = 1,
	[3][95] = 1,
	[3][96] = 1,
	[3][97] = 1,
	[3][98] = 1,
	[3][99] = 1,
	[3][100] = 1,
	[3][101] = 1,
	[3][102] = 1,
	[3][103] = 1,
	[3][104] = 1,
	[3][105] = 1,
	[3][106] = 1,
	[3][107] = 1,
	[3][108] = 1,
	[3][109] = 1,
	[3][110] = 1,
	[3][111] = 1,
	[3][112] = 1,
	[3][113] = 1,
	[3][114] = 1,
	[3][115] = 1,
	[3][116] = 1,
	[3][117] = 1,
	[3][118] = 1,
	[3][119] = 1,
	[3][120] = 1,
	[3][121] = 1,
	[3][122] = 1,
	[3][123] = 1,
	[3][124] = 1,
	[3][125] = 1,
	[3][126] = 1,
	[3][127] = 1,
	[3][128] = 1,
	[3][129] = 1,
	[3][130] = 1,
	[3][131] = 1,
	[3][132] = 1,
	[3][133] = 1,
	[3][134] = 1,
	[3][135] = 1,
	[3][136] = 1,
	[3][137] = 1,
	[3][138] = 1,
	[3][139] = 1,
	[3][140] = 1,
	[3][141] = 1,
	[3][142] = 1,
	[3][143] = 1,
	[3][144] = 1,
	[3][145] = 1,
	[3][146] = 1,
	[3][147] = 1,
	[3][148] = 1,
	[3][149] = 1,
	[3][150] = 1,
	[3][151] = 1,
	[3][152] = 1,
	[3][153] = 1,
	[3][154] = 1,
	[3][155] = 1,
	[3][156] = 1,
	[3][157] = 1,
	[3][158] = 1,
	[3][159] = 1,
	[3][160] = 1,
	[3][161] = 1,
	[3][162] = 1,
	[3][163] = 1,
	[3][164] = 1,
	[3][165] = 1,
	[3][166] = 1,
	[3][167] = 1,
	[3][168] = 1,
	[3][169] = 1,
	[3][170] = 1,
	[3][171] = 1,
	[3][172] = 1,
	[3][173] = 1,
	[3][174] = 1,
	[3][175] = 1,
	[3][176] = 1,
	[3][177] = 1,
	[3][178] = 1,
	[3][179] = 1,
	[3][180] = 1,
	[3][181] = 1,
	[3][182] = 1,
	[3][183] = 1,
	[3][184] = 1,
	[3][185] = 1,
	[3][186] = 1,
	[3][187] = 1,
	[3][188] = 1,
	[3][189] = 1,
	[3][190] = 1,
	[3][191] = 1,
	[3][192] = 1,
	[3][193] = 1,
	[3][194] = 1,
	[3][195] = 1,
	[3][196] = 1,
	[3][197] = 1,
	[3][198] = 1,
	[3][199] = 1,
	[3][200] = 1,
	[3][201] = 1,
	[3][202] = 1,
	[3][203] = 1,
	[3][204] = 1,
	[3][205] = 1,
	[3][206] = 1,
	[3][207] = 1,
	[3][208] = 1,
	[3][209] = 1,
	[3][210] = 1,
	[3][211] = 1,
	[3][212] = 1,
	[3][213] = 1,
	[3][214] = 1,
	[3][215] = 1,
	[3][216] = 1,
	[3][217] = 1,
	[3][218] = 1,
	[3][219] = 1,
	[3][220] = 1,
	[3][221] = 1,
	[3][222] = 1,
	[3][223] = 1,
	[3][224] = 1,
	[3][225] = 1,
	[3][226] = 1,
	[3][227] = 1,
	[3][228] = 1,
	[3][229] = 1,
	[3][230] = 1,
	[3][231] = 1,
	[3][232] = 1,
	[3][233] = 1,
	[3][234] = 1,
	[3][235] = 1,
	[3][236] = 1,
	[3][237] = 1,
	[3][238] = 1,
	[3][239] = 1,
	[3][240] = 1,
	[3][241] = 1,
	[3][242] = 1,
	[3][243] = 1,
	[3][244] = 1,
	[3][245] = 1,
	[3][246] = 1,
	[3][247] = 1,
	[3][248] = 1,
	[3][249] = 1,
	[3][250] = 1,
	[3][251] = 1,
	[3][252] = 1,
	[3][253] = 1,
	[3][254] = 1,
	[3][255] = 1,
	[5][0] = 5,
	[5][1] = 5,
	[5][2] = 5,
	[5][3] = 5,
	[5][4] = 5,
	[5][5] = 5,
	[5][6] = 5,
	[5][7] = 5,
	[5][8] = 5,
	[5][9] = 5,
	[5][11] = 5,
	[5][12] = 5,
	[5][13] = 5,
	[5][14] = 5,
	[5][15] = 5,
	[5][16] = 5,
	[5][17] = 5,
	[5][18] = 5,
	[5][19] = 5,
	[5][20] = 5,
	[5][21] = 5,
	[5][22] = 5,
	[5][23] = 5,
	[5][24] = 5,
	[5][25] = 5,
	[5][26] = 5,
	[5][27] = 5,
	[5][28] = 5,
	[5][29] = 5,
	[5][30] = 5,
	[5][31] = 5,
	[5][32] = 5,
	[5][33] = 5,
	[5][34] = 1,
	[5][35] = 5,
	[5][36] = 5,
	[5][37] = 5,
	[5][38] = 5,
	[5][39] = 5,
	[5][40] = 5,
	[5][41] = 5,
	[5][42] = 5,
	[5][43] = 5,
	[5][44] = 5,
	[5][45] = 5,
	[5][46] = 5,
	[5][47] = 5,
	[5][48] = 5,
	[5][49] = 5,
	[5][50] = 5,
	[5][51] = 5,
	[5][52] = 5,
	[5][53] = 5,
	[5][54] = 5,
	[5][55] = 5,
	[5][56] = 5,
	[5][57] = 5,
	[5][58] = 5,
	[5][59] = 5,
	[5][60] = 5,
	[5][61] = 5,
	[5][62] = 5,
	[5][63] = 5,
	[5][64] = 5,
	[5][65] = 5,
	[5][66] = 5,
	[5][67] = 5,
	[5][68] = 5,
	[5][69] = 5,
	[5][70] = 5,
	[5][71] = 5,
	[5][72] = 5,
	[5][73] = 5,
	[5][74] = 5,
	[5][75] = 5,
	[5][76] = 5,
	[5][77] = 5,
	[5][78] = 5,
	[5][79] = 5,
	[5][80] = 5,
	[5][81] = 5,
	[5][82] = 5,
	[5][83] = 5,
	[5][84] = 5,
	[5][85] = 5,
	[5][86] = 5,
	[5][87] = 5,
	[5][88] = 5,
	[5][89] = 5,
	[5][90] = 5,
	[5][91] = 5,
	[5][92] = 5,
	[5][93] = 5,
	[5][94] = 5,
	[5][95] = 5,
	[5][96] = 5,
	[5][97] = 5,
	[5][98] = 5,
	[5][99] = 5,
	[5][100] = 5,
	[5][101] = 5,
	[5][102] = 5,
	[5][103] = 5,
	[5][104] = 5,
	[5][105] = 5,
	[5][106] = 5,
	[5][107] = 5,
	[5][108] = 5,
	[5][109] = 5,
	[5][110] = 5,
	[5][111] = 5,
	[5][112] = 5,
	[5][113] = 5,
	[5][114] = 5,
	[5][115] = 5,
	[5][116] = 5,
	[5][117] = 5,
	[5][118] = 5,
	[5][119] = 5,
	[5][120] = 5,
	[5][121] = 5,
	[5][122] = 5,
	[5][123] = 5,
	[5][124] = 5,
	[5][125] = 5,
	[5][126] = 5,
	[5][127] = 5,
	[5][128] = 5,
	[5][129] = 5,
	[5][130] = 5,
	[5][131] = 5,
	[5][132] = 5,
	[5][133] = 5,
	[5][134] = 5,
	[5][135] = 5,
	[5][136] = 5,
	[5][137] = 5,
	[5][138] = 5,
	[5][139] = 5,
	[5][140] = 5,
	[5][141] = 5,
	[5][142] = 5,
	[5][143] = 5,
	[5][144] = 5,
	[5][145] = 5,
	[5][146] = 5,
	[5][147] = 5,
	[5][148] = 5,
	[5][149] = 5,
	[5][150] = 5,
	[5][151] = 5,
	[5][152] = 5,
	[5][153] = 5,
	[5][154] = 5,
	[5][155] = 5,
	[5][156] = 5,
	[5][157] = 5,
	[5][158] = 5,
	[5][159] = 5,
	[5][160] = 5,
	[5][161] = 5,
	[5][162] = 5,
	[5][163] = 5,
	[5][164] = 5,
	[5][165] = 5,
	[5][166] = 5,
	[5][167] = 5,
	[5][168] = 5,
	[5][169] = 5,
	[5][170] = 5,
	[5][171] = 5,
	[5][172] = 5,
	[5][173] = 5,
	[5][174] = 5,
	[5][175] = 5,
	[5][176] = 5,
	[5][177] = 5,
	[5][178] = 5,
	[5][179] = 5,
	[5][180] = 5,
	[5][181] = 5,
	[5][182] = 5,
	[5][183] = 5,
	[5][184] = 5,
	[5][185] = 5,
	[5][186] = 5,
	[5][187] = 5,
	[5][188] = 5,
	[5][189] = 5,
	[5][190] = 5,
	[5][191] = 5,
	[5][192] = 5,
	[5][193] = 5,
	[5][194] = 5,
	[5][195] = 5,
	[5][196] = 5,
	[5][197] = 5,
	[5][198] = 5,
	[5][199] = 5,
	[5][200] = 5,
	[5][201] = 5,
	[5][202] = 5,
	[5][203] = 5,
	[5][204] = 5,
	[5][205] = 5,
	[5][206] = 5,
	[5][207] = 5,
	[5][208] = 5,
	[5][209] = 5,
	[5][210] = 5,
	[5][211] = 5,
	[5][212] = 5,
	[5][213] = 5,
	[5][214] = 5,
	[5][215] = 5,
	[5][216] = 5,
	[5][217] = 5,
	[5][218] = 5,
	[5][219] = 5,
	[5][220] = 5,
	[5][221] = 5,
	[5][222] = 5,
	[5][223] = 5,
	[5][224] = 5,
	[5][225] = 5,
	[5][226] = 5,
	[5][227] = 5,
	[5][228] = 5,
	[5][229] = 5,
	[5][230] = 5,
	[5][231] = 5,
	[5][232] = 5,
	[5][233] = 5,
	[5][234] = 5,
	[5][235] = 5,
	[5][236] = 5,
	[5][237] = 5,
	[5][238] = 5,
	[5][239] = 5,
	[5][240] = 5,
	[5][241] = 5,
	[5][242] = 5,
	[5][243] = 5,
	[5][244] = 5,
	[5][245] = 5,
	[5][246] = 5,
	[5][247] = 5,
	[5][248] = 5,
	[5][249] = 5,
	[5][250] = 5,
	[5][251] = 5,
	[5][252] = 5,
	[5][253] = 5,
	[5][254] = 5,
	[5][255] = 5,
	[6][10] = 6,
};


const unsigned zebu_lexer_starts[10] = {
	[1] = 1,
	[2] = 2,
	[3] = 3,
	[4] = 1,
	[5] = 3,
	[6] = 4,
	[7] = 3,
	[8] = 3,
	[9] = 4,
};


const unsigned zebu_lexer_accepts[9] = {
	[1] = 2,
	[3] = 2,
	[6] = 4,
	[7] = 3,
	[8] = 5,
};


const unsigned zebu_lexer_EOFs[5] = {
	[3] = 8,
	[4] = 8,
};


struct token
{
unsigned char* data;
unsigned len, refcount;
};
struct __start__
{
	struct {
		struct row** data;
		unsigned n, cap;
	} rows;
	unsigned refcount;
};

struct row
{
	struct {
		struct token** data;
		unsigned n, cap;
	} cells;
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
void print___start___ptree(struct link* links, enum prefix p, const char* name, struct __start__* ptree);

void print_row_ptree(struct link* links, enum prefix p, const char* name, struct row* ptree);

void print___start___ptree(struct link* links, enum prefix p, const char* name, struct __start__* ptree)
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
	if (ptree->rows.n)
	{
		for (unsigned i = 0, n = ptree->rows.n; i < n; i++)
		{
			char label[4 + 30];
			snprintf(label, sizeof(label), "rows[%u]", i);
			print_row_ptree(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->rows.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_last_child, "row[]", "rows");
	}
	free(new);
}
void print_row_ptree(struct link* links, enum prefix p, const char* name, struct row* ptree)
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
	printf("\e[34m%s\e[m (\e[36mrow\e[m)\n", name);
	if (ptree->cells.n)
	{
		for (unsigned i = 0, n = ptree->cells.n; i < n; i++)
		{
			char label[5 + 30];
			snprintf(label, sizeof(label), "cells[%u]", i);
			print_token_leaf(new ?: links, i + 1 < n ? p_not_last_child : p_last_child, label, ptree->cells.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_last_child, "token[]", "cells");
	}
	free(new);
}


struct token* inc_token(struct token* this)
{
	if (this) this->refcount++;
	return this;
}
struct __start__* inc___start___ptree(struct __start__* ptree)
{
	if (ptree) ptree->refcount++;
	return ptree;
}

struct row* inc_row_ptree(struct row* ptree)
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
void free___start___ptree(struct __start__* ptree);

void free_row_ptree(struct row* ptree);

void free___start___ptree(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->rows.n; i < n; i++)
			free_row_ptree(ptree->rows.data[i]);
		free(ptree->rows.data);
		free(ptree);
	}
}

void free_row_ptree(struct row* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->cells.n; i < n; i++)
			free_token(ptree->cells.data[i]);
		free(ptree->cells.data);
		free(ptree);
	}
}



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

void* parse(FILE* stream)
{
	void* root;
	struct { unsigned* data, n, cap; } yacc = {};
	struct { void** data; unsigned n, cap; } data = {};
	struct { unsigned char* data; unsigned n, cap; } lexer = {};
	
	void push_state(unsigned y)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		yacc.data[yacc.n++] = y;
	}
	
	void push_data(void* d)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		data.data[data.n++] = d;
	}
	
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
	
	unsigned y, t, s, r;
	void* td;
	
	void read_token(unsigned l)
	{
		void append(unsigned char c)
		{
			while (lexer.n + 1 >= lexer.cap)
			{
				lexer.cap = lexer.cap << 1 ?: 1;
				ddprintf("lexer.cap == %u\n", lexer.cap);
				lexer.data = realloc(lexer.data, lexer.cap);
			}
			
			lexer.data[lexer.n++] = c;
		}
		
		unsigned i = 0, f, a, b, c;
		
		t = 0;
		
		ddprintf("l = %u\n", l);
		
		while (1)
		{
			if (i < lexer.n)
			{
				c = lexer.data[i];
				
				char escaped[10];
				
				escape(escaped, c);
				
				printf("c = '%s' (0x%X) (from cache)\n", escaped, c);
				
				assert(!"163");
				#if 0
				next = 0
					?: (state < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[state][c] : 0)
					?: (state < N(zebu_defaults) ? zebu_defaults[state] : 0);
				#endif
			}
			else if ((c = getc(stream)) != EOF)
			{
				append(c);
				
				char escaped[10];
				
				escape(escaped, c);
				
				ddprintf("c = '%s' (0x%X)\n", escaped, c);
				
				a = l < N(zebu_lexer) && c < N(*zebu_lexer) ? zebu_lexer[l][c] : 0;
			}
			else
			{
				c = EOF;
				
				ddprintf("c = <EOF>\n");
				
				a = l < N(zebu_lexer_EOFs) ? zebu_lexer_EOFs[l] : 0;
			}
			
			b = l < N(zebu_lexer_accepts) ? zebu_lexer_accepts[l] : 0;
			
			ddprintf("a = %u, b = %u\n", a, b);
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = i++;
					ddprintf("l = %u\n", l);
				}
				else
				{
					l = a, i++;
					ddprintf("l = %u\n", l);
				}
			}
			else if (b)
			{
				if (c != EOF)
				{
					lexer.n--, ungetc(c, stream);
				}
				
				ddprintf("lexer.n == %u\n", lexer.n);
				ddprintf("lexer: \"%.*s\"\n", lexer.n, lexer.data);
				
				append('\0');
				
				struct token* token = malloc(sizeof(*token));
				token->refcount = 1;
				token->data = memcpy(malloc(lexer.n), lexer.data, lexer.n);
				t = b, td = token, lexer.n = 0;
				break;
			}
			else if (t)
			{
				assert(!"235");
				#if 0
				memmove(lexer.data, lexer.data + fallback, lexer.n - fallback);
				lexer.n -= fallback;
				return token;
				#endif
			}
			else
			{
				assert(!"168");
			}
		}
	}
	
	push_state(1), y = 1, read_token(1);
	
	ddprintf("y = %u, t = %u\n", y, t);
	
	while (yacc.n)
	{
		if (y < N(zebu_shifts) && t < N(*zebu_shifts) && (s = zebu_shifts[y][t]))
		{
			ddprintf("s == %u\n", s);
			
			y = s, push_state(y), push_data(td);
			
			read_token(zebu_lexer_starts[y]);
			
			ddprintf("t = %u\n", t);
		}
		else if (y < N( zebu_reduces) && t < N(*zebu_reduces) && (r = zebu_reduces[y][t]))
		{
			ddprintf("r == %u\n", r);
			
			unsigned g;
			void* d;
			
			switch (r)
{
	case 4:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->rows.n == value->rows.cap)
		{
			value->rows.cap = value->rows.cap << 1 ?: 1;
			value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
		}
		memmove(value->rows.data + 1, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
		value->rows.data[0] = data.data[--yacc.n, --data.n], value->rows.n++;
		d = value, g = 2;
		break;
	}
	case 6:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->rows.n)
			{
				while (value->rows.n + trie->rows.n > value->rows.cap)
				{
					value->rows.cap = value->rows.cap << 1 ?: 1;
					value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
				}
				memmove(value->rows.data + trie->rows.n, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
				for (unsigned i = 0, n = trie->rows.n; i < n; i++)
					value->rows.data[i] = inc_row_ptree(trie->rows.data[i]);
				value->rows.n += trie->rows.n;
			}
			free___start___ptree(trie);
		}
		if (value->rows.n == value->rows.cap)
		{
			value->rows.cap = value->rows.cap << 1 ?: 1;
			value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
		}
		memmove(value->rows.data + 1, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
		value->rows.data[0] = data.data[--yacc.n, --data.n], value->rows.n++;
		d = value, g = 2;
		break;
	}
	case 3:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct __start__* trie = data.data[--yacc.n, --data.n];
			if (trie->rows.n)
			{
				while (value->rows.n + trie->rows.n > value->rows.cap)
				{
					value->rows.cap = value->rows.cap << 1 ?: 1;
					value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
				}
				memmove(value->rows.data + trie->rows.n, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
				for (unsigned i = 0, n = trie->rows.n; i < n; i++)
					value->rows.data[i] = inc_row_ptree(trie->rows.data[i]);
				value->rows.n += trie->rows.n;
			}
			free___start___ptree(trie);
		}
		if (value->rows.n == value->rows.cap)
		{
			value->rows.cap = value->rows.cap << 1 ?: 1;
			value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
		}
		memmove(value->rows.data + 1, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
		value->rows.data[0] = data.data[--yacc.n, --data.n], value->rows.n++;
		d = value, g = 3;
		break;
	}
	case 1:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		if (value->rows.n == value->rows.cap)
		{
			value->rows.cap = value->rows.cap << 1 ?: 1;
			value->rows.data = realloc(value->rows.data, sizeof(*value->rows.data) * value->rows.cap);
		}
		memmove(value->rows.data + 1, value->rows.data, sizeof(*value->rows.data) * value->rows.n);
		value->rows.data[0] = data.data[--yacc.n, --data.n], value->rows.n++;
		d = value, g = 3;
		break;
	}
	case 5:
	{
		struct row* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct row* trie = data.data[--yacc.n, --data.n];
			if (trie->cells.n)			{
				while (value->cells.n + trie->cells.n > value->cells.cap)
				{
					value->cells.cap = value->cells.cap << 1 ?: 1;
					value->cells.data = realloc(value->cells.data, sizeof(*value->cells.data) * value->cells.cap);
				}
				memmove(value->cells.data + trie->cells.n, value->cells.data, sizeof(*value->cells.data) * value->cells.n);
				for (unsigned i = 0, n = trie->cells.n; i < n; i++)
					value->cells.data[i] = inc_token(trie->cells.data[i]);
				value->cells.n += trie->cells.n;
			}
			free_row_ptree(trie);
		}
		free_token(data.data[--yacc.n, --data.n]);
		if (value->cells.n == value->cells.cap)
		{
			value->cells.cap = value->cells.cap << 1 ?: 1;
			value->cells.data = realloc(value->cells.data, sizeof(*value->cells.data) * value->cells.cap);
		}
		memmove(value->cells.data + 1, value->cells.data, sizeof(*value->cells.data) * value->cells.n);
		value->cells.data[0] = data.data[--yacc.n, --data.n], value->cells.n++;
		d = value, g = 1;
		break;
	}
	case 2:
	{
		struct row* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		if (value->cells.n == value->cells.cap)
		{
			value->cells.cap = value->cells.cap << 1 ?: 1;
			value->cells.data = realloc(value->cells.data, sizeof(*value->cells.data) * value->cells.cap);
		}
		memmove(value->cells.data + 1, value->cells.data, sizeof(*value->cells.data) * value->cells.n);
		value->cells.data[0] = data.data[--yacc.n, --data.n], value->cells.n++;
		d = value, g = 1;
		break;
	}
}
			
			if (g == 3)
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
			assert(!"266");
		}
	}
	
	free(yacc.data);
	free(data.data);
	free(lexer.data);
	
	return root;
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
	
	void* root = parse(input);
	
	print___start___ptree(NULL, p_root, "start", root);
	
	free___start___ptree(root);
	
	fclose(input);
	
	free(cmdln);
	
	return 0;
}


















