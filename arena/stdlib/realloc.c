
#include <debug.h>

#include "realloc.h"

void* stdlib_realloc(struct memory_arena* this, void* ptr, size_t newsize)
{
	ENTER;
	
	void* new = realloc(ptr, newsize);
	
	if (!new)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return new;
}

