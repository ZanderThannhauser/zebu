
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include <set/of_tokens/free.h>

#include <tree/of_regexes/new.h>
#include <tree/of_regexes/add.h>
#include <tree/of_regexes/free.h>

#include "struct.h"
#include "free.h"

static void helper(
	struct regextree* freed,
	struct regex* this)
{
	ENTER;
	
	if (regextree_add(freed, this))
	{
		#ifdef WITH_ARENAS
		struct memory_arena* const arena = this->arena;
		#endif
		
		for (size_t i = 0, n = this->transitions.n; i < n; i++)
		{
			struct transition* ele = this->transitions.data[i];
			
			helper(freed, ele->to);
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, ele);
			#else
			free(ele);
			#endif
		}
		
		for (size_t i = 0, n = this->lambda_transitions.n; i < n; i++)
		{
			struct regex* ele = this->lambda_transitions.data[i];
			
			helper(freed, ele);
		}
		
		if (this->default_transition_to)
		{
			helper(freed, this->default_transition_to);
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
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this);
		#else
		free(this);
		#endif
	}
	
	EXIT;
}



void free_regex(struct regex* this)
{
	ENTER;
	
	if (this)
	{
		#ifdef WITH_ARENAS
		struct regextree* freed = new_regextree(this->arena);
		#else
		struct regextree* freed = new_regextree();
		#endif
		
		helper(freed, this);
		
		free_regextree(freed);
	}
	
	EXIT;
}












