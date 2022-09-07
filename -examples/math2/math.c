#include "math.h"

const unsigned zebu_lexer[10][58] = {
	[1][32] = 1,
	[1][40] = 8,
	[1][48] = 9,
	[1][49] = 9,
	[1][50] = 9,
	[1][51] = 9,
	[1][52] = 9,
	[1][53] = 9,
	[1][54] = 9,
	[1][55] = 9,
	[1][56] = 9,
	[1][57] = 9,
	[2][32] = 2,
	[2][42] = 10,
	[2][43] = 11,
	[2][45] = 12,
	[2][47] = 13,
	[3][32] = 3,
	[4][32] = 4,
	[4][43] = 11,
	[4][45] = 12,
	[5][32] = 5,
	[5][41] = 15,
	[5][42] = 10,
	[5][43] = 11,
	[5][45] = 12,
	[5][47] = 13,
	[6][32] = 6,
	[6][41] = 15,
	[7][32] = 7,
	[7][41] = 15,
	[7][43] = 11,
	[7][45] = 12,
	[9][48] = 9,
	[9][49] = 9,
	[9][50] = 9,
	[9][51] = 9,
	[9][52] = 9,
	[9][53] = 9,
	[9][54] = 9,
	[9][55] = 9,
	[9][56] = 9,
	[9][57] = 9,
};


const unsigned zebu_lexer_starts[45] = {
	[1] = 1,
	[2] = 2,
	[3] = 1,
	[4] = 3,
	[5] = 2,
	[6] = 4,
	[7] = 3,
	[8] = 5,
	[9] = 1,
	[10] = 6,
	[11] = 5,
	[12] = 7,
	[13] = 6,
	[14] = 1,
	[15] = 1,
	[16] = 4,
	[17] = 1,
	[18] = 1,
	[19] = 3,
	[20] = 6,
	[21] = 1,
	[22] = 1,
	[23] = 7,
	[24] = 1,
	[25] = 1,
	[26] = 6,
	[27] = 2,
	[28] = 2,
	[29] = 2,
	[30] = 4,
	[31] = 4,
	[32] = 5,
	[33] = 5,
	[34] = 5,
	[35] = 7,
	[36] = 7,
	[37] = 4,
	[38] = 4,
	[39] = 3,
	[40] = 3,
	[41] = 7,
	[42] = 7,
	[43] = 6,
	[44] = 6,
};


const unsigned zebu_lexer_accepts[16] = {
	[8] = 3,
	[9] = 2,
	[10] = 4,
	[11] = 6,
	[12] = 7,
	[13] = 5,
	[14] = 8,
	[15] = 9,
};


const unsigned zebu_lexer_EOFs[5] = {
	[2] = 14,
	[3] = 14,
	[4] = 14,
};


const unsigned zebu_shifts[37][10] = {
	[1][2] = 2,
	[1][3] = 3,
	[3][2] = 8,
	[3][3] = 9,
	[5][4] = 14,
	[5][5] = 15,
	[6][6] = 17,
	[6][7] = 18,
	[9][2] = 8,
	[9][3] = 9,
	[11][4] = 21,
	[11][5] = 22,
	[12][6] = 24,
	[12][7] = 25,
	[13][9] = 27,
	[14][2] = 2,
	[14][3] = 3,
	[15][2] = 2,
	[15][3] = 3,
	[17][2] = 2,
	[17][3] = 3,
	[18][2] = 2,
	[18][3] = 3,
	[20][9] = 32,
	[21][2] = 8,
	[21][3] = 9,
	[22][2] = 8,
	[22][3] = 9,
	[24][2] = 8,
	[24][3] = 9,
	[25][2] = 8,
	[25][3] = 9,
	[28][4] = 14,
	[28][5] = 15,
	[29][4] = 14,
	[29][5] = 15,
	[30][6] = 17,
	[30][7] = 18,
	[31][6] = 17,
	[31][7] = 18,
	[33][4] = 21,
	[33][5] = 22,
	[34][4] = 21,
	[34][5] = 22,
	[35][6] = 24,
	[35][7] = 25,
	[36][6] = 24,
	[36][7] = 25,
};


const unsigned zebu_reduces[45][10] = {
	[2][4] = 1,
	[2][5] = 1,
	[2][6] = 1,
	[2][7] = 1,
	[2][8] = 1,
	[4][8] = 2,
	[5][6] = 3,
	[5][7] = 3,
	[5][8] = 3,
	[6][8] = 4,
	[7][8] = 5,
	[8][4] = 1,
	[8][5] = 1,
	[8][6] = 1,
	[8][7] = 1,
	[8][9] = 1,
	[10][9] = 2,
	[11][6] = 3,
	[11][7] = 3,
	[11][9] = 3,
	[12][9] = 4,
	[16][6] = 6,
	[16][7] = 6,
	[16][8] = 6,
	[19][8] = 7,
	[23][6] = 6,
	[23][7] = 6,
	[23][9] = 6,
	[26][9] = 7,
	[27][4] = 8,
	[27][5] = 8,
	[27][6] = 8,
	[27][7] = 8,
	[27][8] = 8,
	[28][6] = 9,
	[28][7] = 9,
	[28][8] = 9,
	[29][6] = 10,
	[29][7] = 10,
	[29][8] = 10,
	[30][8] = 11,
	[31][8] = 12,
	[32][4] = 8,
	[32][5] = 8,
	[32][6] = 8,
	[32][7] = 8,
	[32][9] = 8,
	[33][6] = 9,
	[33][7] = 9,
	[33][9] = 9,
	[34][6] = 10,
	[34][7] = 10,
	[34][9] = 10,
	[35][9] = 11,
	[36][9] = 12,
	[37][6] = 13,
	[37][7] = 13,
	[37][8] = 13,
	[38][6] = 14,
	[38][7] = 14,
	[38][8] = 14,
	[39][8] = 15,
	[40][8] = 16,
	[41][6] = 13,
	[41][7] = 13,
	[41][9] = 13,
	[42][6] = 14,
	[42][7] = 14,
	[42][9] = 14,
	[43][9] = 15,
	[44][9] = 16,
};


const unsigned zebu_gotos[37][7] = {
	[1][1] = 4,
	[1][2] = 5,
	[1][3] = 6,
	[1][4] = 7,
	[3][1] = 10,
	[3][2] = 11,
	[3][3] = 12,
	[3][4] = 13,
	[5][5] = 16,
	[6][6] = 19,
	[9][1] = 10,
	[9][2] = 11,
	[9][3] = 12,
	[9][4] = 20,
	[11][5] = 23,
	[12][6] = 26,
	[14][2] = 28,
	[15][2] = 29,
	[17][2] = 5,
	[17][3] = 30,
	[18][2] = 5,
	[18][3] = 31,
	[21][2] = 33,
	[22][2] = 34,
	[24][2] = 11,
	[24][3] = 35,
	[25][2] = 11,
	[25][3] = 36,
	[28][5] = 37,
	[29][5] = 38,
	[30][6] = 39,
	[31][6] = 40,
	[33][5] = 41,
	[34][5] = 42,
	[35][6] = 43,
	[36][6] = 44,
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


