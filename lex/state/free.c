
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_lex_state(struct lex_state* this)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		this->is_freeing = true;
		
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct ltransition* t = this->transitions.data[i];
			
			free_lex_state(t->to);
			
			#ifdef WITH_ARENAS
			TODO;
			#else
			free(t);
			#endif
		}
		
		free_lex_state(this->default_transition_to);
		
		free_lex_state(this->EOF_transition_to);
	
		#ifdef WITH_ARENAS
		TODO;
		#else
		free(this->transitions.data);
		free(this);
		#endif
	}
	
	EXIT;
}

