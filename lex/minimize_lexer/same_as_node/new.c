
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct lex_same_as_node* new_lex_same_as_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* state, struct lstatetree* set)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lex_same_as_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lex_same_as_node* this = malloc(sizeof(*this));
	#endif
	
	this->state = state;
	
	this->set = set;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}
#endif
