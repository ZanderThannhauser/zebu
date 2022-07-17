
#include <debug.h>

#include <memory/smalloc.h>

#include "../../state/struct.h"

#include "struct.h"
#include "new.h"

struct iterator* new_iterator(struct regex* state)
{
	ENTER;
	
	struct iterator* this = smalloc(sizeof(*this));
	
	this->moving = state->transitions.data;
	
	this->end = state->transitions.data + state->transitions.n;
	
	this->default_to = state->default_transition_to;
	
	this->last_used = -1;
	
	EXIT;
	return this;
}

