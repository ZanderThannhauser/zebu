<<<<<<< HEAD
const unsigned zebu_shifts[53][16] = {
	[1][2] = 5,
	[1][3] = 4,
	[1][4] = 6,
	[1][5] = 3,
	[1][6] = 2,
	[1][7] = 48,
	[1][9] = 56,
	[6][2] = 10,
	[6][3] = 9,
	[6][4] = 11,
	[6][5] = 8,
	[6][6] = 7,
	[6][7] = 12,
	[6][9] = 44,
	[6][14] = 43,
	[11][2] = 10,
	[11][3] = 9,
	[11][4] = 11,
	[11][5] = 8,
	[11][6] = 7,
	[11][7] = 12,
	[11][9] = 39,
	[11][14] = 38,
	[12][2] = 13,
	[12][15] = 37,
	[13][12] = 14,
	[14][2] = 18,
	[14][3] = 17,
	[14][4] = 19,
	[14][5] = 16,
	[14][6] = 15,
	[14][7] = 25,
	[14][9] = 33,
	[19][2] = 10,
	[19][3] = 9,
	[19][4] = 11,
	[19][5] = 8,
	[19][6] = 7,
	[19][7] = 12,
	[19][9] = 21,
	[19][14] = 20,
	[21][10] = 22,
	[21][11] = 24,
	[22][2] = 10,
	[22][3] = 9,
	[22][4] = 11,
	[22][5] = 8,
	[22][6] = 7,
	[22][7] = 12,
	[22][9] = 21,
	[22][14] = 23,
	[25][2] = 26,
	[25][15] = 32,
	[26][12] = 27,
	[27][2] = 18,
	[27][3] = 17,
	[27][4] = 19,
	[27][5] = 16,
	[27][6] = 15,
	[27][7] = 25,
	[27][9] = 28,
	[28][10] = 29,
	[28][13] = 31,
	[29][2] = 26,
	[29][15] = 30,
	[33][10] = 34,
	[33][13] = 36,
	[34][2] = 13,
	[34][15] = 35,
	[39][10] = 40,
	[39][11] = 42,
	[40][2] = 10,
	[40][3] = 9,
	[40][4] = 11,
	[40][5] = 8,
	[40][6] = 7,
	[40][7] = 12,
	[40][9] = 39,
	[40][14] = 41,
	[44][10] = 45,
	[44][11] = 47,
	[45][2] = 10,
	[45][3] = 9,
	[45][4] = 11,
	[45][5] = 8,
	[45][6] = 7,
	[45][7] = 12,
	[45][9] = 44,
	[45][14] = 46,
	[48][2] = 49,
	[48][15] = 55,
	[49][12] = 50,
	[50][2] = 18,
	[50][3] = 17,
	[50][4] = 19,
	[50][5] = 16,
	[50][6] = 15,
	[50][7] = 25,
	[50][9] = 51,
	[51][10] = 52,
	[51][13] = 54,
	[52][2] = 49,
	[52][15] = 53,
};
const unsigned zebu_reduces[57][14] = {
	[2][8] = 9,
	[3][8] = 9,
	[4][8] = 9,
	[5][8] = 9,
	[7][10] = 9,
	[7][11] = 9,
	[8][10] = 9,
	[8][11] = 9,
	[9][10] = 9,
	[9][11] = 9,
	[10][10] = 9,
	[10][11] = 9,
	[15][10] = 9,
	[15][13] = 9,
	[16][10] = 9,
	[16][13] = 9,
	[17][10] = 9,
	[17][13] = 9,
	[18][10] = 9,
	[18][13] = 9,
	[20][10] = 9,
	[20][13] = 9,
	[23][10] = 14,
	[23][13] = 14,
	[24][10] = 14,
	[24][13] = 14,
	[30][10] = 15,
	[30][13] = 15,
	[31][10] = 15,
	[31][13] = 15,
	[32][10] = 9,
	[32][13] = 9,
	[35][10] = 15,
	[35][11] = 15,
	[36][10] = 15,
	[36][11] = 15,
	[37][10] = 9,
	[37][11] = 9,
	[38][10] = 9,
	[38][11] = 9,
	[41][10] = 14,
	[41][11] = 14,
	[42][10] = 14,
	[42][11] = 14,
	[43][8] = 9,
	[46][8] = 14,
	[47][8] = 14,
	[53][8] = 15,
	[54][8] = 15,
	[55][8] = 9,
	[56][8] = 16,
};
const unsigned zebu_popcounts[57][14] = {
	[2][8] = 1,
	[3][8] = 1,
	[4][8] = 1,
	[5][8] = 1,
	[7][10] = 1,
	[7][11] = 1,
	[8][10] = 1,
	[8][11] = 1,
	[9][10] = 1,
	[9][11] = 1,
	[10][10] = 1,
	[10][11] = 1,
	[15][10] = 1,
	[15][13] = 1,
	[16][10] = 1,
	[16][13] = 1,
	[17][10] = 1,
	[17][13] = 1,
	[18][10] = 1,
	[18][13] = 1,
	[20][10] = 2,
	[20][13] = 2,
	[23][10] = 3,
	[23][13] = 3,
	[24][10] = 2,
	[24][13] = 2,
	[30][10] = 5,
	[30][13] = 5,
	[31][10] = 4,
	[31][13] = 4,
	[32][10] = 2,
	[32][13] = 2,
	[35][10] = 5,
	[35][11] = 5,
	[36][10] = 4,
	[36][11] = 4,
	[37][10] = 2,
	[37][11] = 2,
	[38][10] = 2,
	[38][11] = 2,
	[41][10] = 3,
	[41][11] = 3,
	[42][10] = 2,
	[42][11] = 2,
	[43][8] = 2,
	[46][8] = 3,
	[47][8] = 2,
	[53][8] = 5,
	[54][8] = 4,
	[55][8] = 2,
	[56][8] = 1,
};
const unsigned zebu_lexer[26][126] = {
	[1][32] = 1,
	[1][34] = 2,
	[1][48] = 5,
	[1][49] = 5,
	[1][50] = 5,
	[1][51] = 5,
	[1][52] = 5,
	[1][53] = 5,
	[1][54] = 5,
	[1][55] = 5,
	[1][56] = 5,
	[1][57] = 5,
	[1][91] = 6,
	[1][102] = 7,
	[1][116] = 12,
	[1][123] = 16,
	[2][97] = 3,
	[2][98] = 3,
	[2][99] = 3,
	[2][100] = 3,
	[2][101] = 3,
	[2][102] = 3,
	[2][103] = 3,
	[2][104] = 3,
	[2][105] = 3,
	[2][106] = 3,
	[2][107] = 3,
	[2][108] = 3,
	[2][109] = 3,
	[2][110] = 3,
	[2][111] = 3,
	[2][112] = 3,
	[2][113] = 3,
	[2][114] = 3,
	[2][115] = 3,
	[2][116] = 3,
	[2][117] = 3,
	[2][118] = 3,
	[2][119] = 3,
	[2][120] = 3,
	[2][121] = 3,
	[2][122] = 3,
	[3][34] = 4,
	[3][97] = 3,
	[3][98] = 3,
	[3][99] = 3,
	[3][100] = 3,
	[3][101] = 3,
	[3][102] = 3,
	[3][103] = 3,
	[3][104] = 3,
	[3][105] = 3,
	[3][106] = 3,
	[3][107] = 3,
	[3][108] = 3,
	[3][109] = 3,
	[3][110] = 3,
	[3][111] = 3,
	[3][112] = 3,
	[3][113] = 3,
	[3][114] = 3,
	[3][115] = 3,
	[3][116] = 3,
	[3][117] = 3,
	[3][118] = 3,
	[3][119] = 3,
	[3][120] = 3,
	[3][121] = 3,
	[3][122] = 3,
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
	[7][97] = 8,
	[8][108] = 9,
	[9][115] = 10,
	[10][101] = 11,
	[12][114] = 13,
	[13][117] = 14,
	[14][101] = 15,
	[17][32] = 17,
	[19][32] = 19,
	[19][44] = 20,
	[19][93] = 21,
	[22][32] = 22,
	[22][34] = 2,
	[23][32] = 23,
	[23][58] = 24,
	[25][32] = 25,
	[25][44] = 20,
	[25][125] = 26,
=======
#include "json.h"

const unsigned zebu_lexer[25][126] = {
	[1][32] = 1,
	[1][34] = 7,
	[1][48] = 8,
	[1][49] = 8,
	[1][50] = 8,
	[1][51] = 8,
	[1][52] = 8,
	[1][53] = 8,
	[1][54] = 8,
	[1][55] = 8,
	[1][56] = 8,
	[1][57] = 8,
	[1][91] = 9,
	[1][102] = 10,
	[1][116] = 11,
	[1][123] = 12,
	[2][32] = 2,
	[3][32] = 3,
	[3][34] = 7,
	[4][32] = 4,
	[4][44] = 14,
	[4][93] = 15,
	[5][32] = 5,
	[5][58] = 16,
	[6][32] = 6,
	[6][44] = 14,
	[6][125] = 17,
	[7][97] = 18,
	[7][98] = 18,
	[7][99] = 18,
	[7][100] = 18,
	[7][101] = 18,
	[7][102] = 18,
	[7][103] = 18,
	[7][104] = 18,
	[7][105] = 18,
	[7][106] = 18,
	[7][107] = 18,
	[7][108] = 18,
	[7][109] = 18,
	[7][110] = 18,
	[7][111] = 18,
	[7][112] = 18,
	[7][113] = 18,
	[7][114] = 18,
	[7][115] = 18,
	[7][116] = 18,
	[7][117] = 18,
	[7][118] = 18,
	[7][119] = 18,
	[7][120] = 18,
	[7][121] = 18,
	[7][122] = 18,
	[8][48] = 8,
	[8][49] = 8,
	[8][50] = 8,
	[8][51] = 8,
	[8][52] = 8,
	[8][53] = 8,
	[8][54] = 8,
	[8][55] = 8,
	[8][56] = 8,
	[8][57] = 8,
	[10][97] = 19,
	[11][114] = 20,
	[18][34] = 21,
	[18][97] = 18,
	[18][98] = 18,
	[18][99] = 18,
	[18][100] = 18,
	[18][101] = 18,
	[18][102] = 18,
	[18][103] = 18,
	[18][104] = 18,
	[18][105] = 18,
	[18][106] = 18,
	[18][107] = 18,
	[18][108] = 18,
	[18][109] = 18,
	[18][110] = 18,
	[18][111] = 18,
	[18][112] = 18,
	[18][113] = 18,
	[18][114] = 18,
	[18][115] = 18,
	[18][116] = 18,
	[18][117] = 18,
	[18][118] = 18,
	[18][119] = 18,
	[18][120] = 18,
	[18][121] = 18,
	[18][122] = 18,
	[19][108] = 22,
	[20][117] = 23,
	[22][115] = 24,
	[23][101] = 25,
	[24][101] = 26,
>>>>>>> dev
};


const unsigned zebu_lexer_starts[54] = {
	[1] = 1,
<<<<<<< HEAD
	[2] = 17,
	[3] = 17,
	[4] = 17,
	[5] = 17,
	[6] = 1,
	[7] = 19,
	[8] = 19,
	[9] = 19,
	[10] = 19,
	[11] = 1,
	[12] = 22,
	[13] = 23,
	[14] = 1,
	[15] = 25,
	[16] = 25,
	[17] = 25,
	[18] = 25,
	[19] = 1,
	[20] = 25,
	[21] = 19,
	[22] = 1,
	[23] = 25,
	[24] = 25,
	[25] = 22,
	[26] = 23,
	[27] = 1,
	[28] = 25,
	[29] = 22,
	[30] = 25,
	[31] = 25,
	[32] = 25,
	[33] = 25,
	[34] = 22,
	[35] = 19,
	[36] = 19,
	[37] = 19,
	[38] = 19,
	[39] = 19,
	[40] = 1,
	[41] = 19,
	[42] = 19,
	[43] = 17,
	[44] = 19,
	[45] = 1,
	[46] = 17,
	[47] = 17,
	[48] = 22,
	[49] = 23,
	[50] = 1,
	[51] = 25,
	[52] = 22,
	[53] = 17,
	[54] = 17,
	[55] = 17,
	[56] = 17,
};
const unsigned zebu_defaults[1] = {
};
const unsigned zebu_EOFs[18] = {
	[17] = 18,
};
const unsigned zebu_accepts[27] = {
	[4] = 2,
	[5] = 3,
	[6] = 4,
	[11] = 5,
	[15] = 6,
	[16] = 7,
	[18] = 8,
	[20] = 10,
	[21] = 11,
	[24] = 12,
	[26] = 13,
};
const unsigned start_grammar_id = 16;
const char* zebu_grammar_names[18] = {
	[16] = "(start)",
	[14] = "(trie #1)",
	[15] = "(trie #2)",
	[9] = "value",
=======
	[2] = 2,
	[3] = 2,
	[4] = 2,
	[5] = 2,
	[6] = 1,
	[7] = 3,
	[8] = 2,
	[9] = 4,
	[10] = 4,
	[11] = 4,
	[12] = 4,
	[13] = 1,
	[14] = 3,
	[15] = 2,
	[16] = 4,
	[17] = 5,
	[18] = 2,
	[19] = 6,
	[20] = 4,
	[21] = 4,
	[22] = 4,
	[23] = 6,
	[24] = 1,
	[25] = 2,
	[26] = 1,
	[27] = 3,
	[28] = 2,
	[29] = 1,
	[30] = 4,
	[31] = 3,
	[32] = 4,
	[33] = 2,
	[34] = 6,
	[35] = 6,
	[36] = 6,
	[37] = 6,
	[38] = 1,
	[39] = 3,
	[40] = 6,
	[41] = 2,
	[42] = 4,
	[43] = 4,
	[44] = 6,
	[45] = 4,
	[46] = 6,
	[47] = 6,
	[48] = 1,
	[49] = 6,
	[50] = 3,
	[51] = 6,
	[52] = 6,
	[53] = 6,
};


const unsigned zebu_lexer_accepts[27] = {
	[8] = 5,
	[9] = 6,
	[12] = 7,
	[13] = 8,
	[14] = 9,
	[15] = 10,
	[16] = 11,
	[17] = 12,
	[21] = 2,
	[25] = 3,
	[26] = 4,
>>>>>>> dev
};


const unsigned zebu_lexer_EOFs[3] = {
	[2] = 13,
};


const unsigned zebu_shifts[51][13] = {
	[1][2] = 2,
	[1][3] = 3,
	[1][4] = 4,
	[1][5] = 5,
	[1][6] = 6,
	[1][7] = 7,
	[6][2] = 9,
	[6][3] = 10,
	[6][4] = 11,
	[6][5] = 12,
	[6][6] = 13,
	[6][7] = 14,
	[7][2] = 17,
	[13][2] = 9,
	[13][3] = 10,
	[13][4] = 11,
	[13][5] = 12,
	[13][6] = 13,
	[13][7] = 14,
	[14][2] = 17,
	[16][9] = 24,
	[16][10] = 25,
	[17][11] = 26,
	[19][9] = 27,
	[19][12] = 28,
	[21][9] = 29,
	[21][10] = 30,
	[23][9] = 31,
	[23][12] = 32,
	[24][2] = 9,
	[24][3] = 10,
	[24][4] = 11,
	[24][5] = 12,
	[24][6] = 13,
	[24][7] = 14,
	[26][2] = 34,
	[26][3] = 35,
	[26][4] = 36,
	[26][5] = 37,
	[26][6] = 38,
	[26][7] = 39,
	[27][2] = 17,
	[29][2] = 9,
	[29][3] = 10,
	[29][4] = 11,
	[29][5] = 12,
	[29][6] = 13,
	[29][7] = 14,
	[31][2] = 17,
	[38][2] = 9,
	[38][3] = 10,
	[38][4] = 11,
	[38][5] = 12,
	[38][6] = 13,
	[38][7] = 14,
	[39][2] = 17,
	[45][9] = 48,
	[45][10] = 49,
	[47][9] = 50,
	[47][12] = 51,
	[48][2] = 9,
	[48][3] = 10,
	[48][4] = 11,
	[48][5] = 12,
	[48][6] = 13,
	[48][7] = 14,
	[50][2] = 17,
};


const unsigned zebu_reduces[54][13] = {
	[2][8] = 1,
	[3][8] = 2,
	[4][8] = 3,
	[5][8] = 4,
	[8][8] = 5,
	[9][9] = 1,
	[9][10] = 1,
	[10][9] = 2,
	[10][10] = 2,
	[11][9] = 3,
	[11][10] = 3,
	[12][9] = 4,
	[12][10] = 4,
	[15][8] = 6,
	[18][8] = 7,
	[20][9] = 6,
	[20][10] = 6,
	[22][9] = 7,
	[22][10] = 7,
	[25][8] = 8,
	[28][8] = 9,
	[30][9] = 8,
	[30][10] = 8,
	[32][9] = 9,
	[32][10] = 9,
	[33][8] = 10,
	[34][9] = 1,
	[34][12] = 1,
	[35][9] = 2,
	[35][12] = 2,
	[36][9] = 3,
	[36][12] = 3,
	[37][9] = 4,
	[37][12] = 4,
	[40][9] = 11,
	[40][12] = 11,
	[41][8] = 12,
	[42][9] = 10,
	[42][10] = 10,
	[43][9] = 12,
	[43][10] = 12,
	[44][9] = 6,
	[44][12] = 6,
	[46][9] = 7,
	[46][12] = 7,
	[49][9] = 8,
	[49][12] = 8,
	[51][9] = 9,
	[51][12] = 9,
	[52][9] = 10,
	[52][12] = 10,
	[53][9] = 12,
	[53][12] = 12,
};


const unsigned zebu_gotos[51][5] = {
	[1][1] = 8,
	[6][1] = 16,
	[6][2] = 15,
	[7][3] = 18,
	[7][4] = 19,
	[13][1] = 21,
	[13][2] = 20,
	[14][3] = 22,
	[14][4] = 23,
	[24][1] = 16,
	[24][2] = 33,
	[26][1] = 40,
	[27][3] = 41,
	[27][4] = 19,
	[29][1] = 21,
	[29][2] = 42,
	[31][3] = 43,
	[31][4] = 23,
	[38][1] = 45,
	[38][2] = 44,
	[39][3] = 46,
	[39][4] = 47,
	[48][1] = 45,
	[48][2] = 52,
	[50][3] = 53,
	[50][4] = 47,
};


// expected more than just tables?

// try these options to have zebu paste pre-constructed parsers into this file:

// --yacc=just-tables:
	// print tables and this message, this is the default.

// --yacc=really-just-tables:
	// generate just the tables, don't print this help message.

// --yacc=buffer-driven
	// generates functions to link into a larger program:
		// struct <PREFIX>_state* new_<PREFIX>_state()
			// allocates space using malloc() for maintaining the state of the
			// parser
		
		// void <PREFIX>_reset(struct <PREFIX>_state* this);
			// resets the state of the parser, this is useful in applications
			// where the parser needs to switch to processing a new input stream.
		
		// void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length);
			// makes the parser process the input buffer `text`, expected to be `length` long.
		
		// void <PREFIX>_parse_EOF(struct <PREFIX>_state* this);
			// used to communicate the the parser that the input stream has ended
			// performs all the final reductions.
		
		// void free_<PREFIX>_state(struct <PREFIX>_state* this);
			// frees the struct and all internal datastructures.
	
	// remember that <PREFIX> can be defined with the --prefix=<PREFIX>
	// argument.

// --yacc=readline
	// generates a bottom-up parser that uses the readline library to feed
	// input strings into the parser. Bewteen each line the parser is reset.

// --yacc=readline-debug
	// generates a bottom-up parser that uses the readline library to feed
	// input strings into the parser. Bewteen each line the parser is reset.
	// variables internal to the parser are printed, along with the stack used.

// --yacc=fileio-graphviz
	// creates a program that parses the contents of the file refered to by
	// the first parameter, and builds a parser tree that it outputs as a
	// DOT graphviz input file named by the second parameter.


