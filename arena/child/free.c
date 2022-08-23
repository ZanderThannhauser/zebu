
#include <debug.h>

#include <arena/dealloc.h>

#include "../struct.h"

#include "free.h"

void child_free(struct memory_arena* arena, void* ptr, size_t oldsize)
{
	ENTER;
	
	arena_dealloc(arena->child.parent, ptr);
	
	EXIT;
}
