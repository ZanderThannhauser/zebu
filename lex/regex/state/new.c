
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct regex* new_regex(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regex* this = arena_malloc(arena, sizeof(*this));
	#else
	struct regex* this = malloc(sizeof(*this));
	#endif
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	this->transitions.data = NULL;
	this->transitions.cap = 0;
	this->transitions.n = 0;
	
	this->default_transition_to = NULL;
	
	this->EOF_transition_to = NULL;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	this->phase = 0;
	
	#ifdef DOTOUT
	this->dotout_phase = 0;
	#endif
	
	this->is_accepting = 0;
	this->priority = 0;
	
	EXIT;
	return this;
}

