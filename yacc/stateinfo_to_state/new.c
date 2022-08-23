
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct stateinfo_to_state* new_stateinfo_to_state(
	struct memory_arena* arena,
	struct yacc_stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	struct stateinfo_to_state* this = arena_malloc(arena, sizeof(*this));
	
	this->stateinfo = stateinfo;
	this->state = state;
	
	EXIT;
	return this;
}

