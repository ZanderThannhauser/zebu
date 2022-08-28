
#if 0
#include <stdlib.h>
#include <debug.h>

#include <arena/dealloc.h>

#include <tree/of_gegexes/new.h>
#include <tree/of_gegexes/add.h>
#include <tree/of_gegexes/free.h>

#include "struct.h"
#include "free.h"

static void helper(
	struct gegextree* freed,
	struct gegex* this)
{
	ENTER;
	
	if (gegextree_add(freed, this))
	{
		#ifdef WITH_ARENAS
		struct memory_arena* const arena = this->arena;
		#endif
		
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct transition* t = this->transitions.data[i];
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, t);
			#else
			free(t);
			#endif
		}
		
		for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* t = this->grammar_transitions.data[i];
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, t->grammar);
			#else
			free(t->grammar);
			#endif
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, t);
			#else
			free(t);
			#endif
		}
		
		for (unsigned i = 0, n = this->reduction_transitions.n; i < n; i++)
		{
			struct rtransition* t = this->reduction_transitions.data[i];
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, t->reduce_as);
			#else
			free(t->reduce_as);
			#endif
			
			#ifdef WITH_ARENAS
			arena_dealloc(arena, t);
			#else
			free(t);
			#endif
		}
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->transitions.data);
		#else
		free(this->transitions.data);
		#endif
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->grammar_transitions.data);
		#else
		free(this->grammar_transitions.data);
		#endif
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->reduction_transitions.data);
		#else
		free(this->reduction_transitions.data);
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

void free_gegex(struct gegex* this)
{
	ENTER;
	
	if (this)
	{
		#ifdef WITH_ARENAS
		struct gegextree* freed = new_gegextree(this->arena);
		#else
		struct gegextree* freed = new_gegextree();
		#endif
		
		helper(freed, this);
		
		free_gegextree(freed);
	}
	
	EXIT;
}



















#endif
