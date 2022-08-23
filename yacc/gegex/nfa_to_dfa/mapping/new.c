
#include <debug.h>

#include <arena/malloc.h>

#include <tree/of_gegexes/clone.h>

#include "struct.h"
#include "new.h"

struct gegex_mapping* new_gegex_mapping(
	struct memory_arena* arena,
	struct gegextree* set, struct gegex* state)
{
	ENTER;
	
	struct gegex_mapping* this = arena_malloc(arena, sizeof(*this));
	
	this->original_states = gegextree_clone(set, arena);
	
	this->combined_state = state;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

