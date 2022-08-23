
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct stateinfo_to_state* new_stateinfo_to_state(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct yacc_stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct stateinfo_to_state* this = arena_malloc(arena, sizeof(*this));
	#else
	struct stateinfo_to_state* this = malloc(sizeof(*this));
	#endif
	
	this->stateinfo = stateinfo;
	this->state = state;
	
	EXIT;
	return this;
}

