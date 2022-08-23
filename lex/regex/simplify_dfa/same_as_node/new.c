
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct same_as_node* new_same_as_node(
	struct memory_arena* arena,
	struct regex* state, struct regextree* set)
{
	ENTER;
	
	struct same_as_node* this = arena_malloc(arena, sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

