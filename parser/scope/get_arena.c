
#include <debug.h>

#include "struct.h"
#include "get_arena.h"

struct memory_arena* scope_get_arena(struct scope* this)
{
	assert(this->layer);
	return this->layer->arena;
}

