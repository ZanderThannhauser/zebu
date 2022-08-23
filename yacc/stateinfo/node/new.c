
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>


#include "struct.h"
#include "new.h"

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct yacc_stateinfo_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct yacc_stateinfo_node* this = malloc(sizeof(*this));
	#endif
	
	this->state = state;
	this->grammar = grammar;
	this->lookaheads = lookaheads;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
	
}

