
#ifdef WITHOUT_ARENAS

#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <tree/of_lstates/add.h>

#include "struct.h"
#include "free.h"

// needs to keep a list of what it has already freed
// instead of using these booleans

void free_lex_state(
	struct lstatetree* freed,
	struct lex_state* this)
{
	ENTER;
	
	if (lstatetree_add(freed, this))
	{
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct ltransition* t = this->transitions.data[i];
			
			free_lex_state(freed, t->to);
			
			free(t);
		}
		
		if (this->default_transition_to)
		{
			free_lex_state(freed, this->default_transition_to);
		}
		
		if (this->EOF_transition_to)
		{
			free_lex_state(freed, this->EOF_transition_to);
		}
		
		free(this->transitions.data);
		
		free(this);
	}
	
	EXIT;
}

#endif
