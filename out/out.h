
#include <stdbool.h>

void out(
	struct yacc_state* start,
	struct yacc_shared* yshared,
	const char* output_path,
	const char* output_prefix,
	bool paste_parser_code,
	bool yacc_debugging);
