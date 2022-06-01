
#include <debug.h>

#include <memory/arena/malloc.h>

#include "struct.h"
#include "new.h"

int new_regex_state(struct regex_state** new, struct memory_arena* arena)
{
	int error = 0;
	ENTER;
	
	struct regex_state* this;
	
	error = arena_malloc(arena, (void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->is_accepting = false;
		
		this->default_transition_to = NULL;
		
		this->lambda_transitions.data = NULL;
		this->lambda_transitions.cap = 0;
		this->lambda_transitions.n = 0;
		
		this->transitions.data = NULL;
		this->transitions.cap = 0;
		this->transitions.n = 0;
		
		this->phase = 0;
		
		*new = this;
	}
	
	EXIT;
	return error;
}

