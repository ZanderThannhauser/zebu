
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct gegexset* gegexset_clone(
	const struct gegexset* other,
	struct memory_arena* arena)
{
	ENTER;
	
	struct gegexset* this = arena_malloc(arena, sizeof(*this));
	
	this->data = arena_memdup(arena, other->data, sizeof(*other->data) * other->n);
	this->n = other->n;
	this->cap = other->n;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

