
#include <stdlib.h>

#include <debug.h>

#include "free.h"

void free_pair(void* ptr)
{
	ENTER;
	
	free(ptr);
	
	EXIT;
}

