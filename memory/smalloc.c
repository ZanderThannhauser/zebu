
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include "smalloc.h"

int smalloc(void** retval, size_t size)
{
	int error = 0;
	void* ptr;
	
	ptr = malloc(size);
	
	if (!ptr)
		fprintf(stderr, "%s: malloc(size = %lu): %m\n", argv0, size),
		error = e_out_of_memory;
	else
		*retval = ptr;
	
	return error;
}
