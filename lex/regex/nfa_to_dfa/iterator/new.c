
#include <debug.h>

#include <arena/malloc.h>

#include "../../state/struct.h"

#include "struct.h"
#include "new.h"

struct iterator* new_iterator(
	struct memory_arena* arena,
	struct regex* state)
{
	ENTER;
	
	struct iterator* this = arena_malloc(arena, sizeof(*this));
	
	this->moving = state->transitions.data;
	
	this->end = state->transitions.data + state->transitions.n;
	
	this->default_to = state->default_transition_to;
	
	this->last_used = -1;
	
	EXIT;
	return this;
}

