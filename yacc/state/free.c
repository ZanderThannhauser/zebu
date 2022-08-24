
#ifdef WITHOUT_ARENAS

#include <assert.h>
#include <stdlib.h>
#include <debug.h>

#include <lex/state/free.h>

#include <arena/dealloc.h>

#include <tree/of_ystates/new.h>
#include <tree/of_ystates/add.h>
#include <tree/of_ystates/free.h>

#include <tree/of_lstates/new.h>
#include <tree/of_lstates/free.h>

#include "struct.h"
#include "free.h"

static void helper(
	struct ystatetree* yfreed,
	struct lstatetree* lfreed,
	struct yacc_state* this)
{
	ENTER;
	
	if (ystatetree_add(yfreed, this))
	{
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct ytransition* ele = this->transitions.data[i];
			
			helper(yfreed, lfreed, ele->to);
			
			free(ele);
		}
		
		for (unsigned i = 0, n = this->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* ele = this->reduction_transitions.data[i];
			
			free(ele->reduce_as);
			
			free(ele);
		}
		
		for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* ele = this->grammar_transitions.data[i];
			
			helper(yfreed, lfreed, ele->to);
			
			free(ele->grammar);
			free(ele);
		}
		
		if (this->tokenizer_start)
		{
			free_lex_state(lfreed, this->tokenizer_start);
		}
		
		free(this->transitions.data);
		free(this->reduction_transitions.data);
		free(this->grammar_transitions.data);
		free(this);
	}
	
	EXIT;
}

void free_yacc_state(
	struct yacc_state* this)
{
	ENTER;
	
	if (this)
	{
		struct ystatetree* yfreed = new_ystatetree();
		struct lstatetree* lfreed = new_lstatetree();
		
		helper(yfreed, lfreed, this);
		
		free_ystatetree(yfreed);
		free_lstatetree(lfreed);
	}
	
	EXIT;
}

#endif



































