
#if 0
#include <debug.h>

#include "struct.h"
#include "print_header.h"

void grammar_to_id_print_header(
	struct grammar_to_id* this,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, "extern const char* grammar_names[%u];\n", this->next + 1);
	
	EXIT;
}

#endif
