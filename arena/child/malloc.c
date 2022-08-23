
#ifdef WITH_ARENAS

#include <debug.h>

#include <arena/malloc.h>

#include "../struct.h"

#include "malloc.h"

void* child_malloc(struct memory_arena* arena, size_t size)
{
	ENTER;
	
	dpv(size);
	
	void* ptr = arena_malloc(arena->child.parent, size);
	
	dpv(ptr);
	
	EXIT;
	return ptr;
}


#endif
