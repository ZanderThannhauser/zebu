
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <set/of_regexes/clone.h>

#include "struct.h"
#include "new.h"

struct regex_mapping* new_regex_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regexset* set, struct regex* state)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regex_mapping* this = arena_malloc(arena, sizeof(*this));
	#else
	struct regex_mapping* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->original_states = regexset_clone(arena, set);
	#else
	this->original_states = regexset_clone(set);
	#endif
	
	this->combined_state = state;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

