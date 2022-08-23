
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct regexset* regexset_clone(
	const struct regexset* other,
	struct memory_arena* arena)
{
	ENTER;
	
	dpv(other->n);
	
	struct regexset* this = arena_malloc(arena, sizeof(*this));
	
	this->data = arena_memdup(arena, other->data, sizeof(*other->data) * other->n);
	this->n = other->n;
	this->cap = other->n;
	
	this->arena = arena;
	
	dpv(this->n);
	
	EXIT;
	return this;
}

