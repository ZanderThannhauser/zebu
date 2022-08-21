
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct tokenset* new_tokenset(struct memory_arena* arena)
{
	ENTER;
	
	struct tokenset* this = arena_malloc(arena, sizeof(*this));
	
	this->arena = arena;
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

