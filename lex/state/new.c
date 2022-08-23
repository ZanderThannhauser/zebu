
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct lex_state* new_lex_state(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lex_state* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lex_state* this = malloc(sizeof(*this));
	#endif
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->default_transition_to = NULL;
	
	this->EOF_transition_to = NULL;
	
	this->phase = 0;
	
	this->accepting = NULL;
	
	this->is_freeing = false;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

