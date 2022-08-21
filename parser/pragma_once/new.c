
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "struct.h"
#include "compare.h"
#include "new.h"

struct pragma_once* new_pragma_once(
	struct memory_arena* arena)
{
	ENTER;
	
	struct pragma_once* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_node, NULL);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

