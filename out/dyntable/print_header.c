
#include <debug.h>

#include "struct.h"
#include "print_header.h"

void dyntable_print_header(struct dyntable* this, const char* prefix, FILE* stream)
{
	ENTER;
	
	fprintf(stream, "extern const unsigned %s_%s[%u][%u];\n", prefix, this->name, this->width + 1, this->height + 1);
	
	EXIT;
}







