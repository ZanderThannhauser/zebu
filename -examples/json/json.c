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
};


const unsigned zebu_lexer_starts[54] = {
	[1] = 1,
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


