
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include <tree/of_gegexes/clone.h>

#include "struct.h"
#include "new.h"

struct gegex_mapping* new_gegex_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* set, struct gegex* state)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct gegex_mapping* this = arena_malloc(arena, sizeof(*this));
	#else
	struct gegex_mapping* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->original_states = gegextree_clone(arena, set);
	#else
	this->original_states = gegextree_clone(set);
	#endif
	
	this->combined_state = state;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

