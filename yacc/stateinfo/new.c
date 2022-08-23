
#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct yacc_stateinfo* new_yacc_stateinfo(
	struct memory_arena* arena)
{
	ENTER;
	
	struct yacc_stateinfo* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_yacc_stateinfo_nodes, free_yacc_stateinfo_node);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

