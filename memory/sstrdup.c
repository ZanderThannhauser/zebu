
#include <debug.h>

#include "sstrdup.h"

char* sstrdup(const char* in)
{
	char* new = strdup(in);
	
	if (!new)
	{
		TODO;
		exit(e_out_of_memory);
	}
	
	return new;
}

