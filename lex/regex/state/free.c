
#include <stdlib.h>

#include <debug.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/foreach.h>
#include <set/regex/free.h>

#include "struct.h"
#include "free.h"

static void helper(
	struct regexset* freed,
	struct regex* this)
{
	ENTER;
	
	if (regexset_add(freed, this))
	{
		for (unsigned i = 0, n = this->transitions.n; i < n; i++)
		{
			struct regex_transition* ele = this->transitions.data[i];
			helper(freed, ele->to);
		}
		
		free(this->transitions.data);
		
		for (unsigned i = 0, n = this->lambda_transitions.n; i < n; i++)
		{
			helper(freed, this->lambda_transitions.data[i]);
		}
		
		free(this->lambda_transitions.data);
		
		if (this->default_transition_to)
		{
			helper(freed, this->default_transition_to);
		}
		
		if (this->EOF_transition_to)
		{
			helper(freed, this->EOF_transition_to);
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











