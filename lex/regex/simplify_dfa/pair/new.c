
#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct pair* new_pair(
	struct memory_arena* arena,
	struct regex* a, struct regex* b)
{
	struct pair* this = arena_malloc(arena, sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	this->arena = arena;
	
	return this;
}

