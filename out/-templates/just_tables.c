
{{LEXER_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

// expected more than just tables?

// try these options to have zebu paste pre-constructed parsers into this file:

// --template=just-tables:
	// print tables and this message, this is the default.

// --template=really-just-tables:
	// generate just the tables, don't print this help message.

// --template=charbuffer:
	// generates a parser function that will read 'len' number of characters
	// from the given (unsigned) character buffer, and returns the parse-tree:
	
	// struct {{PREFIX}}_$start* {{PREFIX}}_parse(const unsigned char* buffer, unsigned long len);
	
	// recompile the generated function with `-D ZEBU_DEBUG` to insert code to
	// pretty-print the parse-tree.
	
// --template=fileio
	// generates a parser function that will read from the given `FILE*` stream
	// until it reaches an EOF, and returns the parse-tree:
	
	// struct zebu_$start* {{PREFIX}}_parse(FILE* stream);
	
	// recompile the generated function with `-D ZEBU_DEBUG` to insert code to
	// pretty-print the parse-tree.
	
// --template=fileio-with-driver
	// generates a *program* that will read the file refered to through
	// the first argument to on the command-line. The file is parsed, and
	// the parse-tree is pretty-printed.

// --template=readline:
	// generates a parser function that will call use the GNU Readline Library
	// to read a line of text from the terminal. The function parses the line
	// and returns the parse-tree:
	
	// struct {{PREFIX}}_$start* {{PREFIX}}_parse();
	
	// remember to link the resultant program with `-lreadline`

	// recompile the generated function with `-D ZEBU_DEBUG` to insert code to
	// pretty-print the parse-tree.
	
// --template=readline-with-driver
	// generates a *program* that will repeatedly invoke the GNU Readline
	// Library to read lines from the terminal. Each line is parsed, and
	// pretty-printed.
	
	// remember to link the resultant program with `-lreadline`
	













