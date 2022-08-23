
#include <debug.h>

#include <arena/malloc.h>

#include <set/of_regexes/clone.h>

#include "struct.h"
#include "new.h"

struct regex_mapping* new_regex_mapping(
	struct memory_arena* arena,
	struct regexset* set, struct regex* state)
{
	ENTER;
	
	struct regex_mapping* this = arena_malloc(arena, sizeof(*this));
	
	this->original_states = regexset_clone(set, arena);
	this->combined_state = state;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

