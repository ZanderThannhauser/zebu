

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <enums/error.h>

#include <debug.h>

#include <defines/argv0.h>

#include "srealloc.h"

void* srealloc(void* old, size_t size)
{
	void* new = realloc(old, size);
	
	if (!new)
	{
		fprintf(stderr, "%s: realloc(%lu): %m\n", argv0, size),
		exit(e_out_of_memory);
	}
	
	return new;
}

