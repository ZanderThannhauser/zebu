
#include <debug.h>

#include <arena/malloc.h>


#include "struct.h"
#include "new.h"

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	struct memory_arena* arena,
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads)
{
	ENTER;
	
	struct yacc_stateinfo_node* this = arena_malloc(arena, sizeof(*this));
	
	this->state = state;
	this->grammar = grammar;
	this->lookaheads = lookaheads;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

