
#include <stdbool.h>

#include <enums/parser_template.h>

void out(
	struct yacc_state* start,
	const char* output_path,
	const char* output_prefix,
	enum parser_template parser_template);
