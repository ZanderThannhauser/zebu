
#include <debug.h>

#include <defines/argv0.h>

#include "smemdup.h"

int smemdup(
	void** out,
	const void* in,
	size_t size)
{
	int error = 0;
	void* new;
	ENTER;
	
	if ((new = malloc(size)))
	{
		memcpy(new, in, size);
		*out = new;
	}
	else
	{
		fprintf(stderr, "%s: malloc(size = %lu): %m\n", argv0, size),
		error = e_out_of_memory;
	}
	
	EXIT;
	return error;
}

