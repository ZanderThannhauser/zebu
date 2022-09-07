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


const unsigned zebu_lexer_starts[33] = {
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
	[16] = 1,
	[17] = 1,
	[18] = 6,
	[19] = 1,
	[20] = 1,
	[21] = 1,
	[22] = 1,
	[23] = 2,
	[24] = 4,
	[25] = 4,
	[26] = 3,
	[27] = 3,
	[28] = 5,
	[29] = 7,
	[30] = 7,
	[31] = 6,
	[32] = 6,
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


const unsigned zebu_shifts[23][10] = {
	[1][2] = 2,
	[1][3] = 3,
	[3][2] = 8,
	[3][3] = 9,
	[5][4] = 14,
	[5][5] = 15,
	[6][6] = 16,
	[6][7] = 17,
	[9][2] = 8,
	[9][3] = 9,
	[11][4] = 19,
	[11][5] = 20,
	[12][6] = 21,
	[12][7] = 22,
	[13][9] = 23,
	[14][2] = 2,
	[14][3] = 3,
	[15][2] = 2,
	[15][3] = 3,
	[16][2] = 2,
	[16][3] = 3,
	[17][2] = 2,
	[17][3] = 3,
	[18][9] = 28,
	[19][2] = 8,
	[19][3] = 9,
	[20][2] = 8,
	[20][3] = 9,
	[21][2] = 8,
	[21][3] = 9,
	[22][2] = 8,
	[22][3] = 9,
};


const unsigned zebu_reduces[33][10] = {
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
	[23][4] = 6,
	[23][5] = 6,
	[23][6] = 6,
	[23][7] = 6,
	[23][8] = 6,
	[24][6] = 7,
	[24][7] = 7,
	[24][8] = 7,
	[25][6] = 8,
	[25][7] = 8,
	[25][8] = 8,
	[26][8] = 9,
	[27][8] = 10,
	[28][4] = 6,
	[28][5] = 6,
	[28][6] = 6,
	[28][7] = 6,
	[28][9] = 6,
	[29][6] = 7,
	[29][7] = 7,
	[29][9] = 7,
	[30][6] = 8,
	[30][7] = 8,
	[30][9] = 8,
	[31][9] = 9,
	[32][9] = 10,
};


const unsigned zebu_gotos[23][5] = {
	[1][1] = 4,
	[1][2] = 5,
	[1][3] = 6,
	[1][4] = 7,
	[3][1] = 10,
	[3][2] = 11,
	[3][3] = 12,
	[3][4] = 13,
	[9][1] = 10,
	[9][2] = 11,
	[9][3] = 12,
	[9][4] = 18,
	[14][2] = 5,
	[14][3] = 24,
	[15][2] = 5,
	[15][3] = 25,
	[16][1] = 26,
	[16][2] = 5,
	[16][3] = 6,
	[17][1] = 27,
	[17][2] = 5,
	[17][3] = 6,
	[19][2] = 11,
	[19][3] = 29,
	[20][2] = 11,
	[20][3] = 30,
	[21][1] = 31,
	[21][2] = 11,
	[21][3] = 12,
	[22][1] = 32,
	[22][2] = 11,
	[22][3] = 12,
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


