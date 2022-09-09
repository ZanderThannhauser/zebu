
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "srealloc.h"

void* srealloc(void* ptr, size_t newsize)
{
	ENTER;
	
	dpv(ptr);
	dpv(newsize);
	
	void* newptr = realloc(ptr, newsize);
	
	if (!newptr)
	{
		TODO;
	}
	
	dpv(newptr);
	
	EXIT;
	return newptr;
}

