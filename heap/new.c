
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct heap* new_heap(
	struct memory_arena* arena,
	int (*cmp)(const void*, const void*))
{
	ENTER;
	
	struct heap* this = arena_malloc(arena, sizeof(*this));
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

