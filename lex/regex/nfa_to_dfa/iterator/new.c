
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "../../state/struct.h"

#include "struct.h"
#include "new.h"

struct iterator* new_iterator(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* state)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct iterator* this = arena_malloc(arena, sizeof(*this));
	#else
	struct iterator* this = malloc(sizeof(*this));
	#endif
	
	this->moving = state->transitions.data;
	
	this->end = state->transitions.data + state->transitions.n;
	
	this->default_to = state->default_transition_to;
	
	this->last_used = -1;
	
	EXIT;
	return this;
}

