
#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct lookahead_deps* new_lookahead_deps(
	struct memory_arena* arena)
{
	ENTER;
	
	struct lookahead_deps* this = arena_malloc(arena, sizeof(*this));
	
	this->dependant_of = avl_alloc_tree(arena, compare_lookahead_deps_nodes, free_lookahead_deps_node);
	this->dependant_on = avl_alloc_tree(arena, compare_lookahead_deps_nodes, free_lookahead_deps_node);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

