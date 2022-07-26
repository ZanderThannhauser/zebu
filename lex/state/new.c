
#include <debug.h>

#include <memory/arena/malloc.h>

#include "struct.h"
#include "new.h"

struct lex_state* new_lex_state(
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct lex_state* this = arena_malloc(scratchpad, sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->default_transition_to = NULL;
	
	this->phase = 0;
	
	this->accepting = NULL;
	
	EXIT;
	return this;
}

