
#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include <yacc/gegex/state/struct.h>

#include <set/of_tokens/add.h>
#include <set/of_tokens/update.h>

#include <heap/push.h>

#include "../../shared/struct.h"
#include "../../add_dep.h"
#include "../../lookup_tokenset.h"

#include "../lambda_subgrammars/new.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void explore_lookaheads_task_process(struct task* super, struct yacc_shared* shared)
{
	struct explore_lookaheads_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	dpvs(this->invocation);
	
	if (!avl_search(shared->done, this))
	{
		if (this->invocation && this->node == this->end)
		{
			add_dep(shared->lookaheads.dependant_on, this->invocation, this->name);
			add_dep(shared->lookaheads.dependant_of, this->name, this->invocation);
		}
		
		unsigned i, n;
		for (i = 0, n = this->node->transitions.n; i < n; i++)
		{
			struct transition* ele = this->node->transitions.data[i];
			
			if (this->invocation)
			{
				struct tokenset* lookaheads = lookup_tokenset(shared->lookaheads.sets, this->invocation);
				tokenset_add(lookaheads, ele->token);
			}
			
			heap_push(shared->todo, new_explore_lookaheads_task(
				this->name, ele->to, NULL, this->end, this->scratchpad));
		}
		
		i = 0, n = this->node->grammar_transitions.n;
		if (n)
		{
			heap_push(shared->todo, new_lambda_subgrammars_task(this->name, this->node, this->scratchpad));
			
			for (; i < n; i++)
			{
				const struct gtransition* const ele = this->node->grammar_transitions.data[i];
				
				dpvs(ele->grammar);
				
				if (this->invocation)
				{
					struct tokenset* lookaheads = lookup_tokenset(shared->lookaheads.sets, this->invocation);
					struct tokenset* firsts = lookup_tokenset(shared->firsts.sets, ele->grammar);
					tokenset_update(lookaheads, firsts);
				}
				
				heap_push(shared->todo, new_explore_lookaheads_task(
					this->name, ele->to, ele->grammar, this->end, this->scratchpad));
			}
		}
		
		for (i = 0, n = this->node->lambda_transitions.n; i < n; i++)
		{
			struct gegex* to = this->node->lambda_transitions.data[i];
			
			heap_push(shared->todo, new_explore_lookaheads_task(
				this->name, to, this->invocation, this->end, this->scratchpad));
		}
		
		super->refcount++;
		
		safe_avl_insert(shared->done, this);
	}
	
	EXIT;
}
















