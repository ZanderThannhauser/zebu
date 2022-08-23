
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct gegex* new_gegex(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex* this = arena_malloc(arena, sizeof(*this));
	#else
	struct gegex* this = malloc(sizeof(*this));
	#endif
	
	this->transitions.data = NULL;
	this->transitions.cap = 0;
	this->transitions.n = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.cap = 0;
	this->grammar_transitions.n = 0;
	
	this->reduction_transitions.data = NULL;
	this->reduction_transitions.cap = 0;
	this->reduction_transitions.n = 0;
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	this->is_reduction_point = false;
	
	this->is_freeing = false;
	
	this->popcount = 0;
	
	this->refcount = 0;
	
	this->phase = 0;
	
	dpv(this);
	
	EXIT;
	return this;
}

