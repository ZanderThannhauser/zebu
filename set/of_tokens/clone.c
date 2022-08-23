
#include <string.h>
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct tokenset* tokenset_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct tokenset* other
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct tokenset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct tokenset* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->data = arena_memdup(arena, other->data, sizeof(*other->data) * other->n);
	#else
	this->data = memcpy(malloc(sizeof(*other->data) * other->n), other->data, sizeof(*other->data) * other->n);
	#endif
	
	this->n = other->n;
	this->cap = other->n;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

