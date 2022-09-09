const char* just_tables_source = ""
	"" "\n"
	"{{LEXER_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_STARTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_ACCEPTS_TABLE}}" "\n"
	"" "\n"
	"{{LEXER_EOF_TABLE}}" "\n"
	"" "\n"
	"{{SHIFT_TABLE}}" "\n"
	"" "\n"
	"{{REDUCE_TABLE}}" "\n"
	"" "\n"
	"{{GOTO_TABLE}}" "\n"
	"" "\n"
	"// expected more than just tables?" "\n"
	"" "\n"
	"// try these options to have zebu paste pre-constructed parsers into this file:" "\n"
	"" "\n"
	"// --yacc=just-tables:" "\n"
	"\t// print tables and this message, this is the default." "\n"
	"" "\n"
	"// --yacc=really-just-tables:" "\n"
	"\t// generate just the tables, don\'t print this help message." "\n"
	"" "\n"
	"// --yacc=buffer-driven" "\n"
	"\t// generates functions to link into a larger program:" "\n"
	"\t\t// struct <PREFIX>_state* new_<PREFIX>_state()" "\n"
	"\t\t\t// allocates space using malloc() for maintaining the state of the" "\n"
	"\t\t\t// parser" "\n"
	"\t\t" "\n"
	"\t\t// void <PREFIX>_reset(struct <PREFIX>_state* this);" "\n"
	"\t\t\t// resets the state of the parser, this is useful in applications" "\n"
	"\t\t\t// where the parser needs to switch to processing a new input stream." "\n"
	"\t\t" "\n"
	"\t\t// void <PREFIX>_parse(struct <PREFIX>_state* this, const unsigned char* text, size_t length);" "\n"
	"\t\t\t// makes the parser process the input buffer `text`, expected to be `length` long." "\n"
	"\t\t" "\n"
	"\t\t// void <PREFIX>_parse_EOF(struct <PREFIX>_state* this);" "\n"
	"\t\t\t// used to communicate the the parser that the input stream has ended" "\n"
	"\t\t\t// performs all the final reductions." "\n"
	"\t\t" "\n"
	"\t\t// void free_<PREFIX>_state(struct <PREFIX>_state* this);" "\n"
	"\t\t\t// frees the struct and all internal datastructures." "\n"
	"\t" "\n"
	"\t// remember that <PREFIX> can be defined with the --prefix=<PREFIX>" "\n"
	"\t// argument." "\n"
	"" "\n"
	"// --yacc=readline" "\n"
	"\t// generates a bottom-up parser that uses the readline library to feed" "\n"
	"\t// input strings into the parser. Bewteen each line the parser is reset." "\n"
	"" "\n"
	"// --yacc=readline-debug" "\n"
	"\t// generates a bottom-up parser that uses the readline library to feed" "\n"
	"\t// input strings into the parser. Bewteen each line the parser is reset." "\n"
	"\t// variables internal to the parser are printed, along with the stack used." "\n"
	"" "\n"
	"// --yacc=fileio-graphviz" "\n"
	"\t// creates a program that parses the contents of the file refered to by" "\n"
	"\t// the first parameter, and builds a parser tree that it outputs as a" "\n"
	"\t// DOT graphviz input file named by the second parameter." "\n"
	"" "\n"
	"" "\n"
	"";