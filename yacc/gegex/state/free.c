
#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex(struct gegex* this)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		struct memory_arena* const arena = this->arena;
		
		this->is_freeing = true;
		
		arena_dealloc(arena, this->transitions.data);
		
		for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
			arena_dealloc(arena, this->grammar_transitions.data[i]->grammar);
		
		arena_dealloc(arena, this->grammar_transitions.data);
		
		arena_dealloc(arena, this->lambda_transitions.data);
		
		arena_dealloc(arena, this);
	}
	
	EXIT;
}

