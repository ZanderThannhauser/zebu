
#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include <yacc/gegex/state/struct.h>

#include <set/of_tokens/add.h>
#include <set/of_tokens/print.h>

#include <heap/push.h>

#include "../../shared.h"
#include "../../add_dep.h"
#include "../../lookup_tokenset.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void explore_firsts_task_process(struct task* super, struct shared* shared)
{
	struct explore_firsts_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	if (!avl_search(shared->done, this))
	{
		struct tokenset* first = lookup_tokenset(shared->firsts.sets, this->name);
		
		
		#ifdef DEBUGGING
		tokenset_print(first);
		#endif
		
		unsigned i, n;
		for (i = 0, n = this->node->transitions.n; i < n; i++)
		{
			tokenset_add(first, this->node->transitions.data[i]->token);
		}
		
		for (i = 0, n = this->node->grammar_transitions.n; i < n; i++)
		{
			const struct gtransition* const g = this->node->grammar_transitions.data[i];
			
			dpvs(g->grammar);
			
			add_dep(shared->firsts.dependant_on, this->name, g->grammar);
			add_dep(shared->firsts.dependant_of, g->grammar, this->name);
		}
		
		for (i = 0, n = this->node->lambda_transitions.n; i < n; i++)
		{
			struct gegex* to = this->node->lambda_transitions.data[i];
			
			heap_push(shared->todo, new_explore_firsts_task(this->name, to));
		}
		
		super->refcount++;
		safe_avl_insert(shared->done, this);
	}
	
	EXIT;
}
















