
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
	// Print tables and this message, this is the default.

// --template=really-just-tables:
	// Generate just the tables, don't print this help message.

// --template=charbuffer:
	// Generates a parser function that will read 'len' number of characters
	// from the given (unsigned) character buffer, and returns the parse-tree:
	
	// struct {{PREFIX}}_$start* {{PREFIX}}_parse(const unsigned char* buffer, unsigned long len);
	
	// Recompile the generated function with `-D ZEBU_DEBUG` to insert code to
	// pretty-print the parse-tree.
	
// --template=piecewise-charbuffer:
	// Generates several functions for maintaining and using a thread-safe parser
	// that can save/restore its state bewteen parser invocations:
	
	// struct {{PREFIX}}_state* new_{{PREFIX}}_state();
		// Allocates parser state, and initializes internal data structures
		// to be ready to parse
	
	// void {{PREFIX}}_parse(struct {{PREFIX}}_state* this,
			// const unsigned char* buffer, unsigned len);
		// Processes the chracters of the given buffer, saving parser-state
		// when complete.
	
	// struct zebu_$start* {{PREFIX}}_close(struct {{PREFIX}}_state* this);
		// Indicates that the input-stream has ended, and that the parser
		// should finish any last-minute paperwork it needs to do before
		// returning a parse-tree
	
		// Recompile the generated function with `-D ZEBU_DEBUG` to insert code
		// to pretty-print the parse-tree.
	
	// void {{PREFIX}}_reset(struct {{PREFIX}}_state* this);
		// Reinitailizes the data structures used for parsing. This is useful
		// when processing multiple parse-streams. This should be called after
		// close(), and before the first parse()-call of the new stream.
		
		// If this function is called before the current parse-stream has reached
		// its end, there will be memory-leaks

	// void free_{{PREFIX}}_state(struct {{PREFIX}}_state* this);
		// deallocates the given state and it's internal datastructures

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
	













