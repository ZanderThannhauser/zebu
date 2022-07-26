
#include <debug.h>

#include "scalloc.h"

void *scalloc(size_t nmemb, size_t size)
{
	ENTER;
	
	void* ptr = calloc(nmemb, size);
	
	if (!ptr)
	{
		TODO;
	}
	
	EXIT;
	return ptr;
}

