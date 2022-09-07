
{{LEXER_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

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


