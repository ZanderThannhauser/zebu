
#include <stdlib.h>
#include <debug.h>

#include <arena/dealloc.h>

#include "struct.h"
#include "free.h"

void free_gegex(struct gegex* this)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		#ifdef WITH_ARENAS
		struct memory_arena* const arena = this->arena;
		#endif
		
		this->is_freeing = true;
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->transitions.data);
		#else
		free(this->transitions.data);
		#endif
		
		for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
		{
			#ifdef WITH_ARENAS
			arena_dealloc(arena, this->grammar_transitions.data[i]->grammar);
			#else
			free(this->grammar_transitions.data[i]->grammar);
			#endif
		}
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, this->grammar_transitions.data);
		#else
		free(this->grammar_transitions.data);
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

