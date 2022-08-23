
#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct dependent_of_node* new_dependent_of_node(
	struct memory_arena* arena,
	struct regex* a, struct regex* b)
{
	ENTER;
	
	struct dependent_of_node* this = arena_malloc(arena, sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(arena, compare_pairs, free_pair);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

