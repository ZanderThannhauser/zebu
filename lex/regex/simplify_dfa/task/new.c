
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct simplify_task* new_simplify_task(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a, struct regex* b,
	unsigned hopcount)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct simplify_task* this = arena_malloc(arena, sizeof(*this));
	#else
	struct simplify_task* this = malloc(sizeof(*this));
	#endif
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

