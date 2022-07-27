
#include <stdbool.h>

struct cmdln
{
	const char* input_path;
	const char* output_path;
	
	bool paste_parser_code;
	
	const char* output_prefix;
	
	struct {
		bool lex, yacc;
	} debug;
	
	bool verbose;
};

