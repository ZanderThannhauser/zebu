
#include <stdlib.h>

#include <debug.h>

#include <charset/free.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/foreach.h>
#include <set/regex/free.h>

#include "struct.h"
#include "transition/struct.h"
#include "free.h"

static void helper(
	struct regexset* freed,
	struct regex* this)
{
	ENTER;
	
	if (regexset_add(freed, this))
	{
		for (struct avl_node_t* node = this->transitions->head; node; node = node->next)
		{
			struct regex_transition* ele = node->item;
			helper(freed, ele->to);
		}
		
		avl_free_tree(this->transitions);
		
		regexset_foreach(this->lambda_transitions, ({
			void runme(struct regex* substate)
			{
				helper(freed, substate);
			}
			runme;
		}));
		
		free_regexset(this->lambda_transitions);
		
		if (this->default_transition_to)
		{
			helper(freed, this->default_transition_to);
		}
		
		free(this);
	}
	
	EXIT;
}

void free_regex(struct regex* this)
{
	ENTER;
	
	if (this)
	{
		struct regexset* freed = new_regexset();
		
		helper(freed, this);
		
		free_regexset(freed);
	}
	
	EXIT;
}











