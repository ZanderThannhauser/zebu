
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include "smalloc.h"

void* smalloc(size_t size)
{
	void* ptr = malloc(size);
	
	if (!ptr)
	{
		fprintf(stderr, "%s: malloc(size = %lu): %m\n", argv0, size),
		exit(e_out_of_memory);
	}
	
	return ptr;
}
