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
	"// --template=just-tables:" "\n"
	"\t// Print tables and this message, this is the default." "\n"
	"" "\n"
	"// --template=really-just-tables:" "\n"
	"\t// Generate just the tables, don\'t print this help message." "\n"
	"" "\n"
	"// --template=charbuffer:" "\n"
	"\t// Generates a parser function that will read \'len\' number of characters" "\n"
	"\t// from the given (unsigned) character buffer, and returns the parse-tree:" "\n"
	"\t" "\n"
	"\t// struct {{PREFIX}}_$start* {{PREFIX}}_parse(const unsigned char* buffer, unsigned long len);" "\n"
	"\t" "\n"
	"\t// Recompile the generated function with `-D ZEBU_DEBUG` to insert code to" "\n"
	"\t// pretty-print the parse-tree." "\n"
	"\t" "\n"
	"// --template=piecewise-charbuffer:" "\n"
	"\t// Generates several functions for maintaining and using a thread-safe parser" "\n"
	"\t// that can save/restore its state between parser invocations:" "\n"
	"\t" "\n"
	"\t// struct {{PREFIX}}_state* new_{{PREFIX}}_state();" "\n"
	"\t\t// Allocates parser state, and initializes internal data structures" "\n"
	"\t\t// to be ready to parse" "\n"
	"\t" "\n"
	"\t// void {{PREFIX}}_parse(struct {{PREFIX}}_state* this," "\n"
	"\t\t\t// const unsigned char* buffer, unsigned len);" "\n"
	"\t\t// Processes the chracters of the given buffer, saving parser-state" "\n"
	"\t\t// when complete." "\n"
	"\t" "\n"
	"\t// struct zebu_$start* {{PREFIX}}_close(struct {{PREFIX}}_state* this);" "\n"
	"\t\t// Indicates that the input-stream has ended, and that the parser" "\n"
	"\t\t// should finish any last-minute paperwork it needs to do before" "\n"
	"\t\t// returning a parse-tree" "\n"
	"\t" "\n"
	"\t\t// Recompile the generated function with `-D ZEBU_DEBUG` to insert code" "\n"
	"\t\t// to pretty-print the parse-tree." "\n"
	"\t" "\n"
	"\t// void {{PREFIX}}_reset(struct {{PREFIX}}_state* this);" "\n"
	"\t\t// Reinitailizes the data structures used for parsing. This is useful" "\n"
	"\t\t// when processing multiple parse-streams. This should be called after" "\n"
	"\t\t// close(), and before the first parse()-call of the new stream." "\n"
	"\t\t" "\n"
	"\t\t// If this function is called before the current parse-stream has reached" "\n"
	"\t\t// its end, there will be memory-leaks" "\n"
	"" "\n"
	"\t// void free_{{PREFIX}}_state(struct {{PREFIX}}_state* this);" "\n"
	"\t\t// deallocates the given state and it\'s internal datastructures" "\n"
	"" "\n"
	"// --template=fileio" "\n"
	"\t// generates a parser function that will read from the given `FILE*` stream" "\n"
	"\t// until it reaches an EOF, and returns the parse-tree:" "\n"
	"\t" "\n"
	"\t// struct zebu_$start* {{PREFIX}}_parse(FILE* stream);" "\n"
	"\t" "\n"
	"\t// recompile the generated function with `-D ZEBU_DEBUG` to insert code to" "\n"
	"\t// pretty-print the parse-tree." "\n"
	"\t" "\n"
	"// --template=fileio-with-driver" "\n"
	"\t// generates a *program* that will read the file refered to through" "\n"
	"\t// the first argument to on the command-line. The file is parsed, and" "\n"
	"\t// the parse-tree is pretty-printed." "\n"
	"" "\n"
	"// --template=readline:" "\n"
	"\t// generates a parser function that will call use the GNU Readline Library" "\n"
	"\t// to read a line of text from the terminal. The function parses the line" "\n"
	"\t// and returns the parse-tree:" "\n"
	"\t" "\n"
	"\t// struct {{PREFIX}}_$start* {{PREFIX}}_parse();" "\n"
	"\t" "\n"
	"\t// remember to link the resultant program with `-lreadline`" "\n"
	"" "\n"
	"\t// recompile the generated function with `-D ZEBU_DEBUG` to insert code to" "\n"
	"\t// pretty-print the parse-tree." "\n"
	"\t" "\n"
	"// --template=readline-with-driver" "\n"
	"\t// generates a *program* that will repeatedly invoke the GNU Readline" "\n"
	"\t// Library to read lines from the terminal. Each line is parsed, and" "\n"
	"\t// pretty-printed." "\n"
	"\t" "\n"
	"\t// remember to link the resultant program with `-lreadline`" "\n"
	"\t" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"" "\n"
	"";
