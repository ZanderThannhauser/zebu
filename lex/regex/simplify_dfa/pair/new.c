
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct pair* new_pair(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct pair* this = arena_malloc(arena, sizeof(*this));
	#else
	struct pair* this = malloc(sizeof(*this));
	#endif
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

