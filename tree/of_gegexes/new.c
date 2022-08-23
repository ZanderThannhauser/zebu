
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

struct gegextree* new_gegextree(struct memory_arena* arena)
{
	ENTER;
	
	struct gegextree* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare, NULL);
	this->n = 0;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

