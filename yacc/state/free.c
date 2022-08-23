
#include <stdlib.h>
#include <debug.h>

#include <lex/state/free.h>

#include "struct.h"
#include "free.h"

void free_yacc_state(
	struct yacc_state* this)
{
	ENTER;
	
	if (this && !this->is_freeing)
	{
		this->is_freeing = true;
		
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct ytransition* ele = this->transitions.data[i];
			
			free_yacc_state(ele->to);
			
			#ifdef WITH_ARENAS
			TODO;
			#else
			free(ele);
			#endif
		}
		
		for (unsigned i = 0, n = this->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* ele = this->reduction_transitions.data[i];
			
			#ifdef WITH_ARENAS
			TODO;
			#else
			free(ele->reduce_as);
			free(ele);
			#endif
		}
		
		for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* ele = this->grammar_transitions.data[i];
			
			free_yacc_state(ele->to);
			
			#ifdef WITH_ARENAS
			TODO;
			#else
			free(ele->grammar);
			free(ele);
			#endif
		}
		
		free_lex_state(this->tokenizer_start);
		
		#ifdef WITH_ARENAS
		TODO;
		#else
		free(this->transitions.data);
		free(this->reduction_transitions.data);
		free(this->grammar_transitions.data);
		free(this);
		#endif
	}
	
	EXIT;
}

