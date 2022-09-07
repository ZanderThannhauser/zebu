#include "output.h"

const unsigned zebu_lexer[26][101] = {
	[1][44] = 10,
	[1][97] = 11,
	[2][44] = 12,
	[2][66] = 13,
	[2][98] = 14,
	[3][44] = 15,
	[3][67] = 16,
	[3][97] = 11,
	[3][99] = 17,
	[3][100] = 18,
	[4][44] = 19,
	[4][67] = 16,
	[4][99] = 17,
	[5][44] = 20,
	[5][67] = 16,
	[6][44] = 21,
	[6][97] = 11,
	[6][99] = 17,
	[6][100] = 18,
	[7][44] = 22,
	[8][44] = 24,
	[8][98] = 14,
	[9][44] = 25,
	[9][97] = 11,
	[9][100] = 18,
	[10][32] = 1,
	[12][32] = 2,
	[15][32] = 3,
	[19][32] = 4,
	[20][32] = 5,
	[21][32] = 6,
	[22][32] = 7,
	[24][32] = 8,
	[25][32] = 9,
};


const unsigned zebu_lexer_starts[25] = {
	[1] = 1,
	[2] = 2,
	[3] = 3,
	[4] = 4,
	[5] = 5,
	[6] = 6,
	[7] = 1,
	[8] = 7,
	[9] = 1,
	[10] = 7,
	[11] = 8,
	[12] = 1,
	[13] = 7,
	[14] = 7,
	[15] = 7,
	[16] = 1,
	[17] = 7,
	[18] = 7,
	[19] = 8,
	[20] = 9,
	[21] = 9,
	[22] = 8,
	[23] = 7,
	[24] = 7,
};


const unsigned zebu_lexer_accepts[24] = {
	[11] = 2,
	[13] = 4,
	[14] = 3,
	[16] = 5,
	[17] = 6,
	[18] = 7,
	[23] = 8,
};


const unsigned zebu_lexer_EOFs[8] = {
	[7] = 23,
};


const unsigned zebu_shifts[23][8] = {
	[1][2] = 2,
	[2][3] = 3,
	[2][4] = 4,
	[3][5] = 7,
	[4][6] = 9,
	[5][5] = 7,
	[6][2] = 11,
	[6][6] = 12,
	[6][7] = 13,
	[7][2] = 2,
	[9][2] = 2,
	[11][3] = 16,
	[12][2] = 2,
	[16][2] = 19,
	[19][3] = 20,
	[21][2] = 22,
	[21][7] = 23,
	[22][3] = 16,
};


const unsigned zebu_reduces[25][9] = {
	[3][2] = 1,
	[3][6] = 1,
	[3][7] = 1,
	[4][5] = 2,
	[8][8] = 3,
	[10][8] = 4,
	[13][8] = 5,
	[14][8] = 6,
	[15][8] = 7,
	[17][8] = 8,
	[18][8] = 9,
	[20][2] = 1,
	[20][7] = 1,
	[23][8] = 10,
	[24][8] = 11,
};


const unsigned zebu_gotos[23][6] = {
	[2][1] = 5,
	[2][2] = 6,
	[3][3] = 8,
	[5][3] = 10,
	[7][4] = 14,
	[9][4] = 15,
	[11][5] = 17,
	[12][4] = 18,
	[19][2] = 21,
	[22][5] = 24,
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


