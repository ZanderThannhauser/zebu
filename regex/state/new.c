
#include <debug.h>

#include <memory/arena/malloc.h>

#include "struct.h"
#include "new.h"

struct regex* new_regex(struct memory_arena* arena)
{
	ENTER;
	
	struct regex* this = arena_malloc(arena, sizeof(*this));
	
	this->is_accepting = false;
	
	this->default_transition_to = NULL;
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	this->transitions.data = NULL;
	this->transitions.cap = 0;
	this->transitions.n = 0;
	
	this->phase = 0;
		
	EXIT;
	return this;
}

