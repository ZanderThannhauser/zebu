
#include <debug.h>

#include "sstrdup.h"

int sstrdup(char** out, const char* in)
{
	int error = 0;
	char* new;
	ENTER;
	
	if ((new = strdup(in)))
	{
		*out = new;
	}
	else
	{
		TODO;
		error = e_out_of_memory;
	}
	
	EXIT;
	return error;
}

