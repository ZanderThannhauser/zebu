
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "srealloc.h"

void* srealloc(void* ptr, size_t newsize)
{
	void* newptr = realloc(ptr, newsize);
	
	if (!newptr)
	{
		TODO;
	}
	
	return newptr;
}

