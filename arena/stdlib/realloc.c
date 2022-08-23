
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "realloc.h"

void* stdlib_realloc(struct memory_arena* this, void* ptr, size_t newsize)
{
	ENTER;
	
	dpv(newsize);
	
	void* new = realloc(ptr, newsize);
	
	if (!new && newsize)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return new;
}

