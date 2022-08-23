
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct tokensetset* new_tokensetset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct tokensetset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct tokensetset* this = malloc(sizeof(*this));
	#endif
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

