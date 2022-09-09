
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "smalloc.h"

void* smalloc(size_t size)
{
	ENTER;
	
	dpv(size);
	
	void* ptr = malloc(size);
	
	if (!ptr)
	{
		TODO;
	}
	
	dpv(ptr);
	
	EXIT;
	return ptr;
}

