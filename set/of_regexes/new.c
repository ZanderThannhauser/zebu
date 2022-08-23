
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct regexset* new_regexset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct regexset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct regexset* this = malloc(sizeof(*this));
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

