
#if 0
#include <debug.h>

#include "struct.h"
#include "print_header.h"

void dyntable_print_header(
	struct dyntable* this,
	FILE* stream)
{
	ENTER;
	
	dpvs(this->name);
	
	fprintf(stream, "extern const unsigned %s[%u][%u];\n",
		this->name, this->width + 1, this->height + 1);
	
	EXIT;
}

#endif
