
#include <debug.h>

#include <arena/dealloc.h>

#include <set/of_tokens/free.h>

#include "struct.h"
#include "free.h"

void free_regex(struct regex* this)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		this->is_freeing = true;
		
		struct memory_arena* const arena = this->arena;
		
		for (size_t i = 0, n = this->transitions.n; i < n; i++)
		{
			struct transition* ele = this->transitions.data[i];
			
			free_regex(ele->to);
			
			arena_dealloc(arena, ele);
		}
		
		for (size_t i = 0, n = this->lambda_transitions.n; i < n; i++)
		{
			struct regex* ele = this->lambda_transitions.data[i];
			
			free_regex(ele);
		}
		
		arena_dealloc(arena, this->transitions.data);
		
		arena_dealloc(arena, this->lambda_transitions.data);
		
		free_regex(this->default_transition_to);
		
		arena_dealloc(arena, this);
	}
	
	EXIT;
}












