#include "xml.h"

#define _GNU_SOURCE

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

const unsigned zebu_shifts[27][10] = {
	[1][2] = 2,
	[1][3] = 3,
	[3][5] = 5,
	[5][5] = 6,
	[5][6] = 7,
	[6][7] = 9,
	[7][2] = 10,
	[7][3] = 11,
	[7][8] = 12,
	[9][9] = 15,
	[11][5] = 16,
	[14][2] = 10,
	[14][3] = 11,
	[14][8] = 12,
	[15][5] = 6,
	[15][6] = 7,
	[16][5] = 19,
	[16][6] = 20,
	[19][7] = 22,
	[20][2] = 10,
	[20][3] = 11,
	[20][8] = 23,
	[22][9] = 26,
	[25][2] = 10,
	[25][3] = 11,
	[25][8] = 23,
	[26][5] = 19,
	[26][6] = 20,
};


const unsigned zebu_reduces[29][9] = {
	[2][4] = 1,
	[4][4] = 2,
	[8][4] = 3,
	[10][2] = 1,
	[10][3] = 1,
	[10][8] = 1,
	[12][4] = 4,
	[13][4] = 5,
	[17][4] = 6,
	[18][4] = 7,
	[21][2] = 3,
	[21][3] = 3,
	[21][8] = 3,
	[23][2] = 4,
	[23][3] = 4,
	[23][8] = 4,
	[24][2] = 5,
	[24][3] = 5,
	[24][8] = 5,
	[27][2] = 6,
	[27][3] = 6,
	[27][8] = 6,
	[28][2] = 7,
	[28][3] = 7,
	[28][8] = 7,
};


const unsigned zebu_gotos[27][4] = {
	[1][1] = 4,
	[5][2] = 8,
	[7][1] = 14,
	[7][3] = 13,
	[14][1] = 14,
	[14][3] = 17,
	[15][2] = 18,
	[16][2] = 21,
	[20][1] = 25,
	[20][3] = 24,
	[25][1] = 25,
	[25][3] = 27,
	[26][2] = 28,
};


const unsigned zebu_lexer[67][123] = {
	[1][9] = 1,
	[1][10] = 1,
	[1][32] = 1,
	[1][60] = 8,
	[1][65] = 9,
	[1][66] = 9,
	[1][67] = 9,
	[1][68] = 9,
	[1][69] = 9,
	[1][70] = 9,
	[1][71] = 9,
	[1][72] = 9,
	[1][73] = 9,
	[1][74] = 9,
	[1][75] = 9,
	[1][76] = 9,
	[1][77] = 9,
	[1][78] = 9,
	[1][79] = 9,
	[1][80] = 9,
	[1][81] = 9,
	[1][82] = 9,
	[1][83] = 9,
	[1][84] = 9,
	[1][85] = 9,
	[1][86] = 9,
	[1][87] = 9,
	[1][88] = 9,
	[1][89] = 9,
	[1][90] = 9,
	[1][97] = 9,
	[1][98] = 9,
	[1][99] = 9,
	[1][100] = 9,
	[1][101] = 9,
	[1][102] = 9,
	[1][103] = 9,
	[1][104] = 9,
	[1][105] = 9,
	[1][106] = 9,
	[1][107] = 9,
	[1][108] = 9,
	[1][109] = 9,
	[1][110] = 9,
	[1][111] = 9,
	[1][112] = 9,
	[1][113] = 9,
	[1][114] = 9,
	[1][115] = 9,
	[1][116] = 9,
	[1][117] = 9,
	[1][118] = 9,
	[1][119] = 9,
	[1][120] = 9,
	[1][121] = 9,
	[1][122] = 9,
	[2][9] = 2,
	[2][10] = 2,
	[2][32] = 2,
	[2][60] = 10,
	[3][9] = 3,
	[3][10] = 3,
	[3][32] = 3,
	[3][60] = 12,
	[3][97] = 13,
	[3][98] = 13,
	[3][99] = 13,
	[3][100] = 13,
	[3][101] = 13,
	[3][102] = 13,
	[3][103] = 13,
	[3][104] = 13,
	[3][105] = 13,
	[3][106] = 13,
	[3][107] = 13,
	[3][108] = 13,
	[3][109] = 13,
	[3][110] = 13,
	[3][111] = 13,
	[3][112] = 13,
	[3][113] = 13,
	[3][114] = 13,
	[3][115] = 13,
	[3][116] = 13,
	[3][117] = 13,
	[3][118] = 13,
	[3][119] = 13,
	[3][120] = 13,
	[3][121] = 13,
	[3][122] = 13,
	[4][9] = 4,
	[4][10] = 4,
	[4][32] = 4,
	[4][60] = 14,
	[4][62] = 15,
	[4][97] = 13,
	[4][98] = 13,
	[4][99] = 13,
	[4][100] = 13,
	[4][101] = 13,
	[4][102] = 13,
	[4][103] = 13,
	[4][104] = 13,
	[4][105] = 13,
	[4][106] = 13,
	[4][107] = 13,
	[4][108] = 13,
	[4][109] = 13,
	[4][110] = 13,
	[4][111] = 13,
	[4][112] = 13,
	[4][113] = 13,
	[4][114] = 13,
	[4][115] = 13,
	[4][116] = 13,
	[4][117] = 13,
	[4][118] = 13,
	[4][119] = 13,
	[4][120] = 13,
	[4][121] = 13,
	[4][122] = 13,
	[5][9] = 5,
	[5][10] = 5,
	[5][32] = 5,
	[5][60] = 16,
	[5][61] = 17,
	[6][9] = 6,
	[6][10] = 6,
	[6][32] = 6,
	[6][60] = 18,
	[6][65] = 9,
	[6][66] = 9,
	[6][67] = 9,
	[6][68] = 9,
	[6][69] = 9,
	[6][70] = 9,
	[6][71] = 9,
	[6][72] = 9,
	[6][73] = 9,
	[6][74] = 9,
	[6][75] = 9,
	[6][76] = 9,
	[6][77] = 9,
	[6][78] = 9,
	[6][79] = 9,
	[6][80] = 9,
	[6][81] = 9,
	[6][82] = 9,
	[6][83] = 9,
	[6][84] = 9,
	[6][85] = 9,
	[6][86] = 9,
	[6][87] = 9,
	[6][88] = 9,
	[6][89] = 9,
	[6][90] = 9,
	[6][97] = 9,
	[6][98] = 9,
	[6][99] = 9,
	[6][100] = 9,
	[6][101] = 9,
	[6][102] = 9,
	[6][103] = 9,
	[6][104] = 9,
	[6][105] = 9,
	[6][106] = 9,
	[6][107] = 9,
	[6][108] = 9,
	[6][109] = 9,
	[6][110] = 9,
	[6][111] = 9,
	[6][112] = 9,
	[6][113] = 9,
	[6][114] = 9,
	[6][115] = 9,
	[6][116] = 9,
	[6][117] = 9,
	[6][118] = 9,
	[6][119] = 9,
	[6][120] = 9,
	[6][121] = 9,
	[6][122] = 9,
	[7][9] = 7,
	[7][10] = 7,
	[7][32] = 7,
	[7][34] = 19,
	[7][60] = 20,
	[8][33] = 21,
	[9][65] = 9,
	[9][66] = 9,
	[9][67] = 9,
	[9][68] = 9,
	[9][69] = 9,
	[9][70] = 9,
	[9][71] = 9,
	[9][72] = 9,
	[9][73] = 9,
	[9][74] = 9,
	[9][75] = 9,
	[9][76] = 9,
	[9][77] = 9,
	[9][78] = 9,
	[9][79] = 9,
	[9][80] = 9,
	[9][81] = 9,
	[9][82] = 9,
	[9][83] = 9,
	[9][84] = 9,
	[9][85] = 9,
	[9][86] = 9,
	[9][87] = 9,
	[9][88] = 9,
	[9][89] = 9,
	[9][90] = 9,
	[9][97] = 9,
	[9][98] = 9,
	[9][99] = 9,
	[9][100] = 9,
	[9][101] = 9,
	[9][102] = 9,
	[9][103] = 9,
	[9][104] = 9,
	[9][105] = 9,
	[9][106] = 9,
	[9][107] = 9,
	[9][108] = 9,
	[9][109] = 9,
	[9][110] = 9,
	[9][111] = 9,
	[9][112] = 9,
	[9][113] = 9,
	[9][114] = 9,
	[9][115] = 9,
	[9][116] = 9,
	[9][117] = 9,
	[9][118] = 9,
	[9][119] = 9,
	[9][120] = 9,
	[9][121] = 9,
	[9][122] = 9,
	[10][33] = 22,
	[12][33] = 23,
	[13][97] = 13,
	[13][98] = 13,
	[13][99] = 13,
	[13][100] = 13,
	[13][101] = 13,
	[13][102] = 13,
	[13][103] = 13,
	[13][104] = 13,
	[13][105] = 13,
	[13][106] = 13,
	[13][107] = 13,
	[13][108] = 13,
	[13][109] = 13,
	[13][110] = 13,
	[13][111] = 13,
	[13][112] = 13,
	[13][113] = 13,
	[13][114] = 13,
	[13][115] = 13,
	[13][116] = 13,
	[13][117] = 13,
	[13][118] = 13,
	[13][119] = 13,
	[13][120] = 13,
	[13][121] = 13,
	[13][122] = 13,
	[14][33] = 24,
	[16][33] = 25,
	[18][33] = 26,
	[18][47] = 27,
	[19][34] = 28,
	[19][97] = 19,
	[19][98] = 19,
	[19][99] = 19,
	[19][100] = 19,
	[19][101] = 19,
	[19][102] = 19,
	[19][103] = 19,
	[19][104] = 19,
	[19][105] = 19,
	[19][106] = 19,
	[19][107] = 19,
	[19][108] = 19,
	[19][109] = 19,
	[19][110] = 19,
	[19][111] = 19,
	[19][112] = 19,
	[19][113] = 19,
	[19][114] = 19,
	[19][115] = 19,
	[19][116] = 19,
	[19][117] = 19,
	[19][118] = 19,
	[19][119] = 19,
	[19][120] = 19,
	[19][121] = 19,
	[19][122] = 19,
	[20][33] = 29,
	[21][45] = 30,
	[22][45] = 31,
	[23][45] = 32,
	[24][45] = 33,
	[25][45] = 34,
	[26][45] = 35,
	[27][97] = 36,
	[27][98] = 36,
	[27][99] = 36,
	[27][100] = 36,
	[27][101] = 36,
	[27][102] = 36,
	[27][103] = 36,
	[27][104] = 36,
	[27][105] = 36,
	[27][106] = 36,
	[27][107] = 36,
	[27][108] = 36,
	[27][109] = 36,
	[27][110] = 36,
	[27][111] = 36,
	[27][112] = 36,
	[27][113] = 36,
	[27][114] = 36,
	[27][115] = 36,
	[27][116] = 36,
	[27][117] = 36,
	[27][118] = 36,
	[27][119] = 36,
	[27][120] = 36,
	[27][121] = 36,
	[27][122] = 36,
	[29][45] = 37,
	[30][45] = 38,
	[31][45] = 39,
	[32][45] = 40,
	[33][45] = 41,
	[34][45] = 42,
	[35][45] = 43,
	[36][62] = 44,
	[36][97] = 36,
	[36][98] = 36,
	[36][99] = 36,
	[36][100] = 36,
	[36][101] = 36,
	[36][102] = 36,
	[36][103] = 36,
	[36][104] = 36,
	[36][105] = 36,
	[36][106] = 36,
	[36][107] = 36,
	[36][108] = 36,
	[36][109] = 36,
	[36][110] = 36,
	[36][111] = 36,
	[36][112] = 36,
	[36][113] = 36,
	[36][114] = 36,
	[36][115] = 36,
	[36][116] = 36,
	[36][117] = 36,
	[36][118] = 36,
	[36][119] = 36,
	[36][120] = 36,
	[36][121] = 36,
	[36][122] = 36,
	[37][45] = 45,
	[38][9] = 46,
	[38][10] = 46,
	[38][32] = 46,
	[38][65] = 46,
	[38][66] = 46,
	[38][67] = 46,
	[38][68] = 46,
	[38][69] = 46,
	[38][70] = 46,
	[38][71] = 46,
	[38][72] = 46,
	[38][73] = 46,
	[38][74] = 46,
	[38][75] = 46,
	[38][76] = 46,
	[38][77] = 46,
	[38][78] = 46,
	[38][79] = 46,
	[38][80] = 46,
	[38][81] = 46,
	[38][82] = 46,
	[38][83] = 46,
	[38][84] = 46,
	[38][85] = 46,
	[38][86] = 46,
	[38][87] = 46,
	[38][88] = 46,
	[38][89] = 46,
	[38][90] = 46,
	[38][97] = 46,
	[38][98] = 46,
	[38][99] = 46,
	[38][100] = 46,
	[38][101] = 46,
	[38][102] = 46,
	[38][103] = 46,
	[38][104] = 46,
	[38][105] = 46,
	[38][106] = 46,
	[38][107] = 46,
	[38][108] = 46,
	[38][109] = 46,
	[38][110] = 46,
	[38][111] = 46,
	[38][112] = 46,
	[38][113] = 46,
	[38][114] = 46,
	[38][115] = 46,
	[38][116] = 46,
	[38][117] = 46,
	[38][118] = 46,
	[38][119] = 46,
	[38][120] = 46,
	[38][121] = 46,
	[38][122] = 46,
	[39][9] = 47,
	[39][10] = 47,
	[39][32] = 47,
	[39][65] = 47,
	[39][66] = 47,
	[39][67] = 47,
	[39][68] = 47,
	[39][69] = 47,
	[39][70] = 47,
	[39][71] = 47,
	[39][72] = 47,
	[39][73] = 47,
	[39][74] = 47,
	[39][75] = 47,
	[39][76] = 47,
	[39][77] = 47,
	[39][78] = 47,
	[39][79] = 47,
	[39][80] = 47,
	[39][81] = 47,
	[39][82] = 47,
	[39][83] = 47,
	[39][84] = 47,
	[39][85] = 47,
	[39][86] = 47,
	[39][87] = 47,
	[39][88] = 47,
	[39][89] = 47,
	[39][90] = 47,
	[39][97] = 47,
	[39][98] = 47,
	[39][99] = 47,
	[39][100] = 47,
	[39][101] = 47,
	[39][102] = 47,
	[39][103] = 47,
	[39][104] = 47,
	[39][105] = 47,
	[39][106] = 47,
	[39][107] = 47,
	[39][108] = 47,
	[39][109] = 47,
	[39][110] = 47,
	[39][111] = 47,
	[39][112] = 47,
	[39][113] = 47,
	[39][114] = 47,
	[39][115] = 47,
	[39][116] = 47,
	[39][117] = 47,
	[39][118] = 47,
	[39][119] = 47,
	[39][120] = 47,
	[39][121] = 47,
	[39][122] = 47,
	[40][9] = 48,
	[40][10] = 48,
	[40][32] = 48,
	[40][65] = 48,
	[40][66] = 48,
	[40][67] = 48,
	[40][68] = 48,
	[40][69] = 48,
	[40][70] = 48,
	[40][71] = 48,
	[40][72] = 48,
	[40][73] = 48,
	[40][74] = 48,
	[40][75] = 48,
	[40][76] = 48,
	[40][77] = 48,
	[40][78] = 48,
	[40][79] = 48,
	[40][80] = 48,
	[40][81] = 48,
	[40][82] = 48,
	[40][83] = 48,
	[40][84] = 48,
	[40][85] = 48,
	[40][86] = 48,
	[40][87] = 48,
	[40][88] = 48,
	[40][89] = 48,
	[40][90] = 48,
	[40][97] = 48,
	[40][98] = 48,
	[40][99] = 48,
	[40][100] = 48,
	[40][101] = 48,
	[40][102] = 48,
	[40][103] = 48,
	[40][104] = 48,
	[40][105] = 48,
	[40][106] = 48,
	[40][107] = 48,
	[40][108] = 48,
	[40][109] = 48,
	[40][110] = 48,
	[40][111] = 48,
	[40][112] = 48,
	[40][113] = 48,
	[40][114] = 48,
	[40][115] = 48,
	[40][116] = 48,
	[40][117] = 48,
	[40][118] = 48,
	[40][119] = 48,
	[40][120] = 48,
	[40][121] = 48,
	[40][122] = 48,
	[41][9] = 49,
	[41][10] = 49,
	[41][32] = 49,
	[41][65] = 49,
	[41][66] = 49,
	[41][67] = 49,
	[41][68] = 49,
	[41][69] = 49,
	[41][70] = 49,
	[41][71] = 49,
	[41][72] = 49,
	[41][73] = 49,
	[41][74] = 49,
	[41][75] = 49,
	[41][76] = 49,
	[41][77] = 49,
	[41][78] = 49,
	[41][79] = 49,
	[41][80] = 49,
	[41][81] = 49,
	[41][82] = 49,
	[41][83] = 49,
	[41][84] = 49,
	[41][85] = 49,
	[41][86] = 49,
	[41][87] = 49,
	[41][88] = 49,
	[41][89] = 49,
	[41][90] = 49,
	[41][97] = 49,
	[41][98] = 49,
	[41][99] = 49,
	[41][100] = 49,
	[41][101] = 49,
	[41][102] = 49,
	[41][103] = 49,
	[41][104] = 49,
	[41][105] = 49,
	[41][106] = 49,
	[41][107] = 49,
	[41][108] = 49,
	[41][109] = 49,
	[41][110] = 49,
	[41][111] = 49,
	[41][112] = 49,
	[41][113] = 49,
	[41][114] = 49,
	[41][115] = 49,
	[41][116] = 49,
	[41][117] = 49,
	[41][118] = 49,
	[41][119] = 49,
	[41][120] = 49,
	[41][121] = 49,
	[41][122] = 49,
	[42][9] = 50,
	[42][10] = 50,
	[42][32] = 50,
	[42][65] = 50,
	[42][66] = 50,
	[42][67] = 50,
	[42][68] = 50,
	[42][69] = 50,
	[42][70] = 50,
	[42][71] = 50,
	[42][72] = 50,
	[42][73] = 50,
	[42][74] = 50,
	[42][75] = 50,
	[42][76] = 50,
	[42][77] = 50,
	[42][78] = 50,
	[42][79] = 50,
	[42][80] = 50,
	[42][81] = 50,
	[42][82] = 50,
	[42][83] = 50,
	[42][84] = 50,
	[42][85] = 50,
	[42][86] = 50,
	[42][87] = 50,
	[42][88] = 50,
	[42][89] = 50,
	[42][90] = 50,
	[42][97] = 50,
	[42][98] = 50,
	[42][99] = 50,
	[42][100] = 50,
	[42][101] = 50,
	[42][102] = 50,
	[42][103] = 50,
	[42][104] = 50,
	[42][105] = 50,
	[42][106] = 50,
	[42][107] = 50,
	[42][108] = 50,
	[42][109] = 50,
	[42][110] = 50,
	[42][111] = 50,
	[42][112] = 50,
	[42][113] = 50,
	[42][114] = 50,
	[42][115] = 50,
	[42][116] = 50,
	[42][117] = 50,
	[42][118] = 50,
	[42][119] = 50,
	[42][120] = 50,
	[42][121] = 50,
	[42][122] = 50,
	[43][9] = 51,
	[43][10] = 51,
	[43][32] = 51,
	[43][65] = 51,
	[43][66] = 51,
	[43][67] = 51,
	[43][68] = 51,
	[43][69] = 51,
	[43][70] = 51,
	[43][71] = 51,
	[43][72] = 51,
	[43][73] = 51,
	[43][74] = 51,
	[43][75] = 51,
	[43][76] = 51,
	[43][77] = 51,
	[43][78] = 51,
	[43][79] = 51,
	[43][80] = 51,
	[43][81] = 51,
	[43][82] = 51,
	[43][83] = 51,
	[43][84] = 51,
	[43][85] = 51,
	[43][86] = 51,
	[43][87] = 51,
	[43][88] = 51,
	[43][89] = 51,
	[43][90] = 51,
	[43][97] = 51,
	[43][98] = 51,
	[43][99] = 51,
	[43][100] = 51,
	[43][101] = 51,
	[43][102] = 51,
	[43][103] = 51,
	[43][104] = 51,
	[43][105] = 51,
	[43][106] = 51,
	[43][107] = 51,
	[43][108] = 51,
	[43][109] = 51,
	[43][110] = 51,
	[43][111] = 51,
	[43][112] = 51,
	[43][113] = 51,
	[43][114] = 51,
	[43][115] = 51,
	[43][116] = 51,
	[43][117] = 51,
	[43][118] = 51,
	[43][119] = 51,
	[43][120] = 51,
	[43][121] = 51,
	[43][122] = 51,
	[45][9] = 52,
	[45][10] = 52,
	[45][32] = 52,
	[45][65] = 52,
	[45][66] = 52,
	[45][67] = 52,
	[45][68] = 52,
	[45][69] = 52,
	[45][70] = 52,
	[45][71] = 52,
	[45][72] = 52,
	[45][73] = 52,
	[45][74] = 52,
	[45][75] = 52,
	[45][76] = 52,
	[45][77] = 52,
	[45][78] = 52,
	[45][79] = 52,
	[45][80] = 52,
	[45][81] = 52,
	[45][82] = 52,
	[45][83] = 52,
	[45][84] = 52,
	[45][85] = 52,
	[45][86] = 52,
	[45][87] = 52,
	[45][88] = 52,
	[45][89] = 52,
	[45][90] = 52,
	[45][97] = 52,
	[45][98] = 52,
	[45][99] = 52,
	[45][100] = 52,
	[45][101] = 52,
	[45][102] = 52,
	[45][103] = 52,
	[45][104] = 52,
	[45][105] = 52,
	[45][106] = 52,
	[45][107] = 52,
	[45][108] = 52,
	[45][109] = 52,
	[45][110] = 52,
	[45][111] = 52,
	[45][112] = 52,
	[45][113] = 52,
	[45][114] = 52,
	[45][115] = 52,
	[45][116] = 52,
	[45][117] = 52,
	[45][118] = 52,
	[45][119] = 52,
	[45][120] = 52,
	[45][121] = 52,
	[45][122] = 52,
	[46][9] = 46,
	[46][10] = 46,
	[46][32] = 46,
	[46][45] = 53,
	[46][65] = 46,
	[46][66] = 46,
	[46][67] = 46,
	[46][68] = 46,
	[46][69] = 46,
	[46][70] = 46,
	[46][71] = 46,
	[46][72] = 46,
	[46][73] = 46,
	[46][74] = 46,
	[46][75] = 46,
	[46][76] = 46,
	[46][77] = 46,
	[46][78] = 46,
	[46][79] = 46,
	[46][80] = 46,
	[46][81] = 46,
	[46][82] = 46,
	[46][83] = 46,
	[46][84] = 46,
	[46][85] = 46,
	[46][86] = 46,
	[46][87] = 46,
	[46][88] = 46,
	[46][89] = 46,
	[46][90] = 46,
	[46][97] = 46,
	[46][98] = 46,
	[46][99] = 46,
	[46][100] = 46,
	[46][101] = 46,
	[46][102] = 46,
	[46][103] = 46,
	[46][104] = 46,
	[46][105] = 46,
	[46][106] = 46,
	[46][107] = 46,
	[46][108] = 46,
	[46][109] = 46,
	[46][110] = 46,
	[46][111] = 46,
	[46][112] = 46,
	[46][113] = 46,
	[46][114] = 46,
	[46][115] = 46,
	[46][116] = 46,
	[46][117] = 46,
	[46][118] = 46,
	[46][119] = 46,
	[46][120] = 46,
	[46][121] = 46,
	[46][122] = 46,
	[47][9] = 47,
	[47][10] = 47,
	[47][32] = 47,
	[47][45] = 54,
	[47][65] = 47,
	[47][66] = 47,
	[47][67] = 47,
	[47][68] = 47,
	[47][69] = 47,
	[47][70] = 47,
	[47][71] = 47,
	[47][72] = 47,
	[47][73] = 47,
	[47][74] = 47,
	[47][75] = 47,
	[47][76] = 47,
	[47][77] = 47,
	[47][78] = 47,
	[47][79] = 47,
	[47][80] = 47,
	[47][81] = 47,
	[47][82] = 47,
	[47][83] = 47,
	[47][84] = 47,
	[47][85] = 47,
	[47][86] = 47,
	[47][87] = 47,
	[47][88] = 47,
	[47][89] = 47,
	[47][90] = 47,
	[47][97] = 47,
	[47][98] = 47,
	[47][99] = 47,
	[47][100] = 47,
	[47][101] = 47,
	[47][102] = 47,
	[47][103] = 47,
	[47][104] = 47,
	[47][105] = 47,
	[47][106] = 47,
	[47][107] = 47,
	[47][108] = 47,
	[47][109] = 47,
	[47][110] = 47,
	[47][111] = 47,
	[47][112] = 47,
	[47][113] = 47,
	[47][114] = 47,
	[47][115] = 47,
	[47][116] = 47,
	[47][117] = 47,
	[47][118] = 47,
	[47][119] = 47,
	[47][120] = 47,
	[47][121] = 47,
	[47][122] = 47,
	[48][9] = 48,
	[48][10] = 48,
	[48][32] = 48,
	[48][45] = 55,
	[48][65] = 48,
	[48][66] = 48,
	[48][67] = 48,
	[48][68] = 48,
	[48][69] = 48,
	[48][70] = 48,
	[48][71] = 48,
	[48][72] = 48,
	[48][73] = 48,
	[48][74] = 48,
	[48][75] = 48,
	[48][76] = 48,
	[48][77] = 48,
	[48][78] = 48,
	[48][79] = 48,
	[48][80] = 48,
	[48][81] = 48,
	[48][82] = 48,
	[48][83] = 48,
	[48][84] = 48,
	[48][85] = 48,
	[48][86] = 48,
	[48][87] = 48,
	[48][88] = 48,
	[48][89] = 48,
	[48][90] = 48,
	[48][97] = 48,
	[48][98] = 48,
	[48][99] = 48,
	[48][100] = 48,
	[48][101] = 48,
	[48][102] = 48,
	[48][103] = 48,
	[48][104] = 48,
	[48][105] = 48,
	[48][106] = 48,
	[48][107] = 48,
	[48][108] = 48,
	[48][109] = 48,
	[48][110] = 48,
	[48][111] = 48,
	[48][112] = 48,
	[48][113] = 48,
	[48][114] = 48,
	[48][115] = 48,
	[48][116] = 48,
	[48][117] = 48,
	[48][118] = 48,
	[48][119] = 48,
	[48][120] = 48,
	[48][121] = 48,
	[48][122] = 48,
	[49][9] = 49,
	[49][10] = 49,
	[49][32] = 49,
	[49][45] = 56,
	[49][65] = 49,
	[49][66] = 49,
	[49][67] = 49,
	[49][68] = 49,
	[49][69] = 49,
	[49][70] = 49,
	[49][71] = 49,
	[49][72] = 49,
	[49][73] = 49,
	[49][74] = 49,
	[49][75] = 49,
	[49][76] = 49,
	[49][77] = 49,
	[49][78] = 49,
	[49][79] = 49,
	[49][80] = 49,
	[49][81] = 49,
	[49][82] = 49,
	[49][83] = 49,
	[49][84] = 49,
	[49][85] = 49,
	[49][86] = 49,
	[49][87] = 49,
	[49][88] = 49,
	[49][89] = 49,
	[49][90] = 49,
	[49][97] = 49,
	[49][98] = 49,
	[49][99] = 49,
	[49][100] = 49,
	[49][101] = 49,
	[49][102] = 49,
	[49][103] = 49,
	[49][104] = 49,
	[49][105] = 49,
	[49][106] = 49,
	[49][107] = 49,
	[49][108] = 49,
	[49][109] = 49,
	[49][110] = 49,
	[49][111] = 49,
	[49][112] = 49,
	[49][113] = 49,
	[49][114] = 49,
	[49][115] = 49,
	[49][116] = 49,
	[49][117] = 49,
	[49][118] = 49,
	[49][119] = 49,
	[49][120] = 49,
	[49][121] = 49,
	[49][122] = 49,
	[50][9] = 50,
	[50][10] = 50,
	[50][32] = 50,
	[50][45] = 57,
	[50][65] = 50,
	[50][66] = 50,
	[50][67] = 50,
	[50][68] = 50,
	[50][69] = 50,
	[50][70] = 50,
	[50][71] = 50,
	[50][72] = 50,
	[50][73] = 50,
	[50][74] = 50,
	[50][75] = 50,
	[50][76] = 50,
	[50][77] = 50,
	[50][78] = 50,
	[50][79] = 50,
	[50][80] = 50,
	[50][81] = 50,
	[50][82] = 50,
	[50][83] = 50,
	[50][84] = 50,
	[50][85] = 50,
	[50][86] = 50,
	[50][87] = 50,
	[50][88] = 50,
	[50][89] = 50,
	[50][90] = 50,
	[50][97] = 50,
	[50][98] = 50,
	[50][99] = 50,
	[50][100] = 50,
	[50][101] = 50,
	[50][102] = 50,
	[50][103] = 50,
	[50][104] = 50,
	[50][105] = 50,
	[50][106] = 50,
	[50][107] = 50,
	[50][108] = 50,
	[50][109] = 50,
	[50][110] = 50,
	[50][111] = 50,
	[50][112] = 50,
	[50][113] = 50,
	[50][114] = 50,
	[50][115] = 50,
	[50][116] = 50,
	[50][117] = 50,
	[50][118] = 50,
	[50][119] = 50,
	[50][120] = 50,
	[50][121] = 50,
	[50][122] = 50,
	[51][9] = 51,
	[51][10] = 51,
	[51][32] = 51,
	[51][45] = 58,
	[51][65] = 51,
	[51][66] = 51,
	[51][67] = 51,
	[51][68] = 51,
	[51][69] = 51,
	[51][70] = 51,
	[51][71] = 51,
	[51][72] = 51,
	[51][73] = 51,
	[51][74] = 51,
	[51][75] = 51,
	[51][76] = 51,
	[51][77] = 51,
	[51][78] = 51,
	[51][79] = 51,
	[51][80] = 51,
	[51][81] = 51,
	[51][82] = 51,
	[51][83] = 51,
	[51][84] = 51,
	[51][85] = 51,
	[51][86] = 51,
	[51][87] = 51,
	[51][88] = 51,
	[51][89] = 51,
	[51][90] = 51,
	[51][97] = 51,
	[51][98] = 51,
	[51][99] = 51,
	[51][100] = 51,
	[51][101] = 51,
	[51][102] = 51,
	[51][103] = 51,
	[51][104] = 51,
	[51][105] = 51,
	[51][106] = 51,
	[51][107] = 51,
	[51][108] = 51,
	[51][109] = 51,
	[51][110] = 51,
	[51][111] = 51,
	[51][112] = 51,
	[51][113] = 51,
	[51][114] = 51,
	[51][115] = 51,
	[51][116] = 51,
	[51][117] = 51,
	[51][118] = 51,
	[51][119] = 51,
	[51][120] = 51,
	[51][121] = 51,
	[51][122] = 51,
	[52][9] = 52,
	[52][10] = 52,
	[52][32] = 52,
	[52][45] = 59,
	[52][65] = 52,
	[52][66] = 52,
	[52][67] = 52,
	[52][68] = 52,
	[52][69] = 52,
	[52][70] = 52,
	[52][71] = 52,
	[52][72] = 52,
	[52][73] = 52,
	[52][74] = 52,
	[52][75] = 52,
	[52][76] = 52,
	[52][77] = 52,
	[52][78] = 52,
	[52][79] = 52,
	[52][80] = 52,
	[52][81] = 52,
	[52][82] = 52,
	[52][83] = 52,
	[52][84] = 52,
	[52][85] = 52,
	[52][86] = 52,
	[52][87] = 52,
	[52][88] = 52,
	[52][89] = 52,
	[52][90] = 52,
	[52][97] = 52,
	[52][98] = 52,
	[52][99] = 52,
	[52][100] = 52,
	[52][101] = 52,
	[52][102] = 52,
	[52][103] = 52,
	[52][104] = 52,
	[52][105] = 52,
	[52][106] = 52,
	[52][107] = 52,
	[52][108] = 52,
	[52][109] = 52,
	[52][110] = 52,
	[52][111] = 52,
	[52][112] = 52,
	[52][113] = 52,
	[52][114] = 52,
	[52][115] = 52,
	[52][116] = 52,
	[52][117] = 52,
	[52][118] = 52,
	[52][119] = 52,
	[52][120] = 52,
	[52][121] = 52,
	[52][122] = 52,
	[53][45] = 60,
	[54][45] = 61,
	[55][45] = 62,
	[56][45] = 63,
	[57][45] = 64,
	[58][45] = 65,
	[59][45] = 66,
	[60][62] = 1,
	[61][62] = 2,
	[62][62] = 3,
	[63][62] = 4,
	[64][62] = 5,
	[65][62] = 6,
	[66][62] = 7,
};


const unsigned zebu_lexer_starts[29] = {
	[1] = 1,
	[2] = 2,
	[3] = 3,
	[4] = 2,
	[5] = 4,
	[6] = 5,
	[7] = 6,
	[8] = 2,
	[9] = 7,
	[10] = 6,
	[11] = 3,
	[12] = 2,
	[13] = 2,
	[14] = 6,
	[15] = 4,
	[16] = 4,
	[17] = 2,
	[18] = 2,
	[19] = 5,
	[20] = 6,
	[21] = 6,
	[22] = 7,
	[23] = 6,
	[24] = 6,
	[25] = 6,
	[26] = 4,
	[27] = 6,
	[28] = 6,
};


const unsigned zebu_lexer_accepts[45] = {
	[8] = 3,
	[9] = 2,
	[11] = 4,
	[13] = 5,
	[15] = 6,
	[17] = 7,
	[18] = 3,
	[28] = 9,
	[44] = 8,
};


const unsigned zebu_lexer_EOFs[3] = {
	[2] = 11,
};


struct token
{
unsigned char* data;
unsigned len, refcount;
};
struct __start__
{
	struct value* root;
	unsigned refcount;
};

struct value
{
	struct {
		struct value** data;
		unsigned n, cap;
	} subvalues;
	struct token* tag;
	struct token* text;
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

void print_value_ptree(struct link* links, enum prefix p, const char* name, struct value* ptree);

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
	if (ptree->root)
		print_value_ptree(new ?: links, p_last_child, "root", ptree->root);
	else
		print_empty_leaf(new ?: links, p_last_child, "value", "root");
	free(new);
}
void print_value_ptree(struct link* links, enum prefix p, const char* name, struct value* ptree)
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
	printf("\e[34m%s\e[m (\e[36mvalue\e[m)\n", name);
	if (ptree->subvalues.n)
	{
		for (unsigned i = 0, n = ptree->subvalues.n; i < n; i++)
		{
			char label[9 + 30];
			snprintf(label, sizeof(label), "subvalues[%u]", i);
			print_value_ptree(new ?: links, i + 1 < n ? p_not_last_child : p_not_last_child, label, ptree->subvalues.data[i]);
		}
	}
	else
	{
		print_empty_leaf(new ?: links, p_not_last_child, "value[]", "subvalues");
	}
	if (ptree->tag)
		print_token_leaf(new ?: links, p_not_last_child, "tag", ptree->tag);
	else
		print_empty_leaf(new ?: links, p_not_last_child, "token", "tag");
	if (ptree->text)
		print_token_leaf(new ?: links, p_last_child, "text", ptree->text);
	else
		print_empty_leaf(new ?: links, p_last_child, "token", "text");
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

struct value* inc_value_ptree(struct value* ptree)
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

void free_value_ptree(struct value* ptree);

void free___start___ptree(struct __start__* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		free_value_ptree(ptree->root);
		free(ptree);
	}
}

void free_value_ptree(struct value* ptree)
{
	if (ptree && !--ptree->refcount)
	{
		for (unsigned i = 0, n = ptree->subvalues.n; i < n; i++)
			free_value_ptree(ptree->subvalues.data[i]);
		free(ptree->subvalues.data);
		free_token(ptree->tag);
		free_token(ptree->text);
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
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 3;
		break;
	}
	case 6:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->subvalues.n)
			{
				while (value->subvalues.n + trie->subvalues.n > value->subvalues.cap)
				{
					value->subvalues.cap = value->subvalues.cap << 1 ?: 1;
					value->subvalues.data = realloc(value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.cap);
				}
				memmove(value->subvalues.data + trie->subvalues.n, value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.n);
				for (unsigned i = 0, n = trie->subvalues.n; i < n; i++)
					value->subvalues.data[i] = inc_value_ptree(trie->subvalues.data[i]);
				value->subvalues.n += trie->subvalues.n;
			}
			if (trie->tag) { free_token(value->tag); value->tag = inc_token(trie->tag); }
			if (trie->text) { free_token(value->text); value->text = inc_token(trie->text); }
			free_value_ptree(trie);
		}
		if (value->subvalues.n == value->subvalues.cap)
		{
			value->subvalues.cap = value->subvalues.cap << 1 ?: 1;
			value->subvalues.data = realloc(value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.cap);
		}
		memmove(value->subvalues.data + 1, value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.n);
		value->subvalues.data[0] = data.data[--yacc.n, --data.n], value->subvalues.n++;
		d = value, g = 3;
		break;
	}
	case 5:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->subvalues.n)
			{
				while (value->subvalues.n + trie->subvalues.n > value->subvalues.cap)
				{
					value->subvalues.cap = value->subvalues.cap << 1 ?: 1;
					value->subvalues.data = realloc(value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.cap);
				}
				memmove(value->subvalues.data + trie->subvalues.n, value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.n);
				for (unsigned i = 0, n = trie->subvalues.n; i < n; i++)
					value->subvalues.data[i] = inc_value_ptree(trie->subvalues.data[i]);
				value->subvalues.n += trie->subvalues.n;
			}
			if (trie->tag) { free_token(value->tag); value->tag = inc_token(trie->tag); }
			if (trie->text) { free_token(value->text); value->text = inc_token(trie->text); }
			free_value_ptree(trie);
		}
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 7:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->subvalues.n)
			{
				while (value->subvalues.n + trie->subvalues.n > value->subvalues.cap)
				{
					value->subvalues.cap = value->subvalues.cap << 1 ?: 1;
					value->subvalues.data = realloc(value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.cap);
				}
				memmove(value->subvalues.data + trie->subvalues.n, value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.n);
				for (unsigned i = 0, n = trie->subvalues.n; i < n; i++)
					value->subvalues.data[i] = inc_value_ptree(trie->subvalues.data[i]);
				value->subvalues.n += trie->subvalues.n;
			}
			if (trie->tag) { free_token(value->tag); value->tag = inc_token(trie->tag); }
			if (trie->text) { free_token(value->text); value->text = inc_token(trie->text); }
			free_value_ptree(trie);
		}
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 2;
		break;
	}
	case 2:
	{
		struct __start__* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_value_ptree(value->root), value->root = data.data[--yacc.n, --data.n];
		d = value, g = 4;
		break;
	}
	case 3:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		{
			struct value* trie = data.data[--yacc.n, --data.n];
			if (trie->subvalues.n)
			{
				while (value->subvalues.n + trie->subvalues.n > value->subvalues.cap)
				{
					value->subvalues.cap = value->subvalues.cap << 1 ?: 1;
					value->subvalues.data = realloc(value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.cap);
				}
				memmove(value->subvalues.data + trie->subvalues.n, value->subvalues.data, sizeof(*value->subvalues.data) * value->subvalues.n);
				for (unsigned i = 0, n = trie->subvalues.n; i < n; i++)
					value->subvalues.data[i] = inc_value_ptree(trie->subvalues.data[i]);
				value->subvalues.n += trie->subvalues.n;
			}
			if (trie->tag) { free_token(value->tag); value->tag = inc_token(trie->tag); }
			if (trie->text) { free_token(value->text); value->text = inc_token(trie->text); }
			free_value_ptree(trie);
		}
		free_token(value->tag), value->tag = data.data[--yacc.n, --data.n];
		free_token(data.data[--yacc.n, --data.n]);
		d = value, g = 1;
		break;
	}
	case 1:
	{
		struct value* value = memset(malloc(sizeof(*value)), 0, sizeof(*value));
		value->refcount = 1;
		free_token(value->text), value->text = data.data[--yacc.n, --data.n];
		d = value, g = 1;
		break;
	}
}
			
			if (g == 4)
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


















