
#include <debug.h>

#include <memory/arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_regex(
	struct regex* this,
	struct memory_arena* arena)
{
	ENTER;
	
	if (!this->is_freeing)
	{
		this->is_freeing = true;
		
		for (size_t i = 0, n = this->transitions.n; i < n; i++)
		{
			struct transition* ele = this->transitions.data[i];
			
			free_regex(ele->to, arena);
			
			arena_dealloc(arena, ele);
		}
		
		arena_dealloc(arena, this->transitions.data);
		
		for (size_t i = 0, n = this->lambda_transitions.n; i < n; i++)
		{
			struct regex* ele = this->lambda_transitions.data[i];
			
			free_regex(ele, arena);
		}
		
		arena_dealloc(arena, this->lambda_transitions.data);
		
		arena_dealloc(arena, this->default_transition_to);
		
		arena_dealloc(arena, this);
	}
	
	EXIT;
}












