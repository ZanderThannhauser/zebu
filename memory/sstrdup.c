
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

#include <enums/error.h>

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

