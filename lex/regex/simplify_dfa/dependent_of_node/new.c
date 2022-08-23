
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct dependent_of_node* new_dependent_of_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct dependent_of_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct dependent_of_node* this = malloc(sizeof(*this));
	#endif
	
	this->pair.a = a;
	this->pair.b = b;
	
	#ifdef WITH_ARENAS
	this->dependent_of = avl_alloc_tree(arena, compare_pairs, free_pair);
	#else
	this->dependent_of = avl_alloc_tree(compare_pairs, free_pair);
	#endif
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

