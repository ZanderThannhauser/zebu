
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct strset* new_strset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct strset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct strset* this = malloc(sizeof(*this));
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

