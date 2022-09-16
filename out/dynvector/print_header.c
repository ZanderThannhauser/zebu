
#include <debug.h>

#include "struct.h"
#include "print_header.h"

void dynvector_print_header(
	struct dynvector* this,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	fprintf(stream, "extern const unsigned %s_%s[%u];\n", prefix, this->name, this->length + 1);
	
	EXIT;
}














