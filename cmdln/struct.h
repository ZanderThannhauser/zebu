
#include <stdbool.h>

struct cmdln
{
	const char* input_path;
	const char* output_prefix;
	
	bool just_output_tables;
	
	struct {
		bool lex, yacc;
	} debug;
	
	bool verbose;
};

