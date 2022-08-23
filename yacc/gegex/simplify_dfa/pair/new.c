
#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct gegex_pair* new_gegex_pair(
	struct memory_arena* arena,
	struct gegex* a, struct gegex* b)
{
	struct gegex_pair* this = arena_malloc(arena, sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	this->arena = arena;
	
	return this;
}

