
#include <stdbool.h>

#include <enums/parser_template.h>

struct cmdln
{
	const char* input_path;
	const char* output_path;
	
	const char* output_prefix;
	
	enum parser_template parser_template;
	
	bool verbose;
};

