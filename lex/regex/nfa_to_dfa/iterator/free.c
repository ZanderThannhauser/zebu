
#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_iterator(
	struct iterator* this,
	struct memory_arena* arena)
{
	ENTER;
	
	arena_dealloc(arena, this);
	
	EXIT;
}

