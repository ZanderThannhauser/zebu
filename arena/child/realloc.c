
#ifdef WITH_ARENAS

#include <debug.h>

#include <arena/realloc.h>

#include "../struct.h"

#include "realloc.h"

void* child_realloc(struct memory_arena* arena, void* old, size_t newsize)
{
	ENTER;
	
	dpv(newsize);
	
	void* new = arena_realloc(arena->child.parent, old, newsize);
	
	dpv(new);
	
	EXIT;
	return new;
}


#endif
