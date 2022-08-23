
#include <stdlib.h>

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
		
		#ifdef WITH_ARENAS
		struct memory_arena* const arena = this->arena;
		#endif
		
		for (size_t i = 0, n = this->transitions.n; i < n; i++)
		{
			struct transition* ele = this->transitions.data[i];
			
			free_regex(ele->to);
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, ele);
			#else
			free(ele);
			#endif
		}
		
		for (size_t i = 0, n = this->lambda_transitions.n; i < n; i++)
		{
			struct regex* ele = this->lambda_transitions.data[i];
			
			free_regex(ele);
		}
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->transitions.data);
		#else
		free(this->transitions.data);
		#endif
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->lambda_transitions.data);
		#else
		free(this->lambda_transitions.data);
		#endif
		
		free_regex(this->default_transition_to);
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this);
		#else
		free(this);
		#endif
	}
	
	EXIT;
}












