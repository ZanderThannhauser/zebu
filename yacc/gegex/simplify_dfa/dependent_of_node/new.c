
#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct gegex_dependent_of_node* new_gegex_dependent_of_node(
	struct memory_arena* arena,
	struct gegex* a, struct gegex* b)
{
	ENTER;
	
	struct gegex_dependent_of_node* this = arena_malloc(arena, sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(arena, compare_gegex_pairs, free_gegex_pair);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

