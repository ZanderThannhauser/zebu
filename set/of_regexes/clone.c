
#include <string.h>

#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct regexset* regexset_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct regexset* other
) {
	ENTER;
	
	dpv(other->n);
	
	#ifdef WITH_ARENAS
	struct regexset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct regexset* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->data = arena_memdup(arena, other->data, sizeof(*other->data) * other->n);
	#else
	this->data = memcpy(malloc(sizeof(other->data) * other->n), other->data, sizeof(*other->data) * other->n);
	#endif
	
	this->n = other->n;
	this->cap = other->n;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	dpv(this->n);
	
	EXIT;
	return this;
}

