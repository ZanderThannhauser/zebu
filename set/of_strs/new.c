
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct strset* new_strset(
	struct memory_arena* arena)
{
	ENTER;
	
	struct strset* this = arena_malloc(arena, sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

