
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct tokenset* tokenset_clone(
	const struct tokenset* other,
	struct memory_arena* arena)
{
	ENTER;
	
	struct tokenset* this = arena_malloc(arena, sizeof(*this));
	
	this->data = arena_memdup(arena, other->data, sizeof(*other->data) * other->n);
	
	this->n = other->n;
	this->cap = other->n;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

