
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct yacc_stateinfo* new_yacc_stateinfo(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct yacc_stateinfo* this = arena_malloc(arena, sizeof(*this));
	#else
	struct yacc_stateinfo* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->tree = avl_alloc_tree(arena, compare_yacc_stateinfo_nodes, free_yacc_stateinfo_node);
	#else
	this->tree = avl_alloc_tree(compare_yacc_stateinfo_nodes, free_yacc_stateinfo_node);
	#endif
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

