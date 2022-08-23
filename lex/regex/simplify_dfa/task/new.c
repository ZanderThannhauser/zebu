
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct simplify_task* new_simplify_task(
	struct memory_arena* arena,
	struct regex* a, struct regex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct simplify_task* this = arena_malloc(arena, sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

