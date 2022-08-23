
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct yacc_state* new_yacc_state(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct yacc_state* this = arena_malloc(arena, sizeof(*this));
	#else
	struct yacc_state* this = malloc(sizeof(*this));
	#endif
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.n = 0;
	this->grammar_transitions.cap = 0;
	
	this->reduction_transitions.data = NULL;
	this->reduction_transitions.n = 0;
	this->reduction_transitions.cap = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	this->phase = 0;
	
	EXIT;
	return this;
}

