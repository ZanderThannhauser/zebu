
#include <debug.h>

#include <memory/arena/malloc.h>

#include "struct.h"
#include "new.h"

struct yacc_state* new_yacc_state(
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct yacc_state* this = arena_malloc(scratchpad, sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.n = 0;
	this->grammar_transitions.cap = 0;
	
	this->reduction_transitions.data = NULL;
	this->reduction_transitions.n = 0;
	this->reduction_transitions.cap = 0;
	
	EXIT;
	return this;
}

