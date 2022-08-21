
#include <debug.h>

#include "resize.h"

bool stdlib_resize(struct memory_arena* this, void* _, size_t __, size_t ___)
{
	bool retval = false;
	ENTER;
	
	dpvb(retval);
	
	EXIT;
	return retval;
}

