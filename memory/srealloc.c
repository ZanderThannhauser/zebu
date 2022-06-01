
#undef DEBUGGING

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <enums/error.h>

#include <debug.h>

#include <defines/argv0.h>

#include "srealloc.h"

int srealloc(void** retval, size_t size)
{
	int error = 0;
	void* old = *retval, *new;
	ENTER;
	
	dpv(old);
	dpv(size);
	
	new = realloc(old, size);
	
	if (!new)
		fprintf(stderr, "%s: realloc(%lu): %s\n", argv0, size, strerror(errno)),
		error = e_out_of_memory;
	else
		*retval = new;
	
	EXIT;
	return error;
}

