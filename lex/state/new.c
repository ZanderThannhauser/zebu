
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct lex_state* new_lex_state(
	struct memory_arena* arena)
{
	ENTER;
	
	struct lex_state* this = arena_malloc(arena, sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->default_transition_to = NULL;
	
	this->EOF_transition_to = NULL;
	
	this->phase = 0;
	
	this->accepting = NULL;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

