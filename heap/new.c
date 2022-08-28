
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct heap* new_heap(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	int (*cmp)(const void*, const void*))
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct heap* this = arena_malloc(arena, sizeof(*this));
	#else
	struct heap* this = malloc(sizeof(*this));
	#endif
	
	this->cmp = cmp;
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

