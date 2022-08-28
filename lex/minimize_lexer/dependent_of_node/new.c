
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct lex_dependent_of_node* new_lex_dependent_of_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lex_dependent_of_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lex_dependent_of_node* this = malloc(sizeof(*this));
	#endif
	
	this->pair.a = a;
	this->pair.b = b;
	
	#ifdef WITH_ARENAS
	this->dependent_of = avl_alloc_tree(arena, compare_lex_pairs, free_lex_pair);
	#else
	this->dependent_of = avl_alloc_tree(compare_lex_pairs, free_lex_pair);
	#endif
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}
#endif
