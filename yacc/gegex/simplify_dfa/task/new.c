
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct gegex_simplify_task* new_gegex_simplify_task(
	struct memory_arena* arena,
	struct gegex* a, struct gegex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct gegex_simplify_task* this = arena_malloc(arena, sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

