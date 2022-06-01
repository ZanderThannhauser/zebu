
#include <stdbool.h>

struct cmdln
{
	const char* input_path;
	const char* output_path;
	
	struct {
		bool lex, yacc;
	} debug;
	
	bool verbose;
};

