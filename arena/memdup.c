
#ifdef WITH_ARENAS

#include <string.h>

#include <debug.h>

#include "malloc.h"
#include "memdup.h"

void* arena_memdup(
	struct memory_arena* this,
	const void* data, size_t size)
{
	ENTER;
	
	void* retval = arena_malloc(this, size);
	
	memcpy(retval, data, size);
	
	EXIT;
	return retval;
}

#endif
