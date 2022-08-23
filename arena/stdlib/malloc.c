
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "malloc.h"

void* stdlib_malloc(struct memory_arena* this, size_t size)
{
	ENTER;
	
	dpv(size);
	
	void* ptr = malloc(size);
	
	if (!ptr)
	{
		TODO;
		exit(1);
	}
	
	dpv(ptr);
	
	EXIT;
	return ptr;
}

