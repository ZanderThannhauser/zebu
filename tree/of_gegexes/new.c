
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

struct gegextree* new_gegextree(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegextree* this = arena_malloc(arena, sizeof(*this));
	#else
	struct gegextree* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->tree = avl_alloc_tree(arena, compare, NULL);
	#else
	this->tree = avl_alloc_tree(compare, NULL);
	#endif
	
	this->n = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

