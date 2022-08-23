
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct yacc_state* new_yacc_state(
	struct memory_arena* arena)
{
	ENTER;
	
	struct yacc_state* this = arena_malloc(arena, sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.n = 0;
	this->grammar_transitions.cap = 0;
	
	this->reduction_transitions.data = NULL;
	this->reduction_transitions.n = 0;
	this->reduction_transitions.cap = 0;
	
	this->arena = arena;
	
	this->phase = 0;
	
	EXIT;
	return this;
}

