
#if 0
#include <debug.h>

#include "struct.h"
#include "print_header.h"

void dynvector_print_header(
	struct dynvector* this,
	FILE* stream)
{
	ENTER;
	
	dpvs(this->name);
	
	fprintf(stream, "extern const unsigned %s[%u];\n",
		this->name, this->length + 1);
	
	EXIT;
}

#endif
