
#include <debug.h>

#include <memory/arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex(struct gegex* this, struct memory_arena* arena)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		this->is_freeing = true;
		
		arena_dealloc(arena, this->transitions.data);
		arena_dealloc(arena, this->grammar_transitions.data);
		arena_dealloc(arena, this->lambda_transitions.data);
		
		arena_dealloc(arena, this);
	}
	
	EXIT;
}

