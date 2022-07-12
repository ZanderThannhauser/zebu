
#include <debug.h>

#include <parser/production/gegex/state/struct.h>

#include <tokenset/add.h>

#include <heap/push.h>

#include "../../shared.h"
#include "../../add_dep.h"

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
		// first = firsts.lookup.setdefault(grammar, set());
		struct tokenset* first;
		{
			struct avl_node_t* node = avl_search(shared->firsts.sets, &this->name);
			assert(node);
			struct named_tokenset* nt = node->item;
			first = nt->tokenset;
		}
		
		tokenset_print(first);
		
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
			heap_push(shared->todo, new_explore_firsts_task(
				this->name, this->node->lambda_transitions.data[i]));
		}
		
		super->refcount++;
		
		safe_avl_insert(shared->done, this);
	}
	
	EXIT;
}
















