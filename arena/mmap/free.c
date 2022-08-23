
#ifdef WITH_ARENAS

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include "free.h"

void mmap_free(struct memory_arena* this, void* ptr, size_t oldsize)
{
	ENTER;
	
	if (munmap(ptr, oldsize) < 0)
	{
		fprintf(stderr, "%s: munmap(): %m\n", argv0);
		exit(1);
	}
	
	EXIT;
}



#endif
