
#include <debug.h>

#include <avl/search.h>
/*#include <avl/safe_insert.h>*/

#include <yacc/gegex/state/struct.h>

#include <named/grammar/struct.h>

#include <set/of_tokens/free.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
/*#include <set/of_tokens/add.h>*/
#include <set/of_tokens/update.h>

#include <heap/push.h>

#include "../../stateinfo/contains.h"
#include "../../stateinfo/add.h"
#include "../../stateinfo/get.h"

#include "../../lookahead_deps/add.h"

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
#include "../../shared/lookup_firsts.h"

#include "../percolate_lookaheads/new.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void expand_tree_task_process(struct task* super, struct yacc_shared* shared)
{
	struct expand_tree_task* const this = (void*) super;
	ENTER;
	
	dpv(this->state);
	
	if (yacc_stateinfo_contains(this->stateinfo, this->state))
	{
		struct tokenset* ts = yacc_stateinfo_get(this->stateinfo, this->state);
		
		tokenset_update(ts, this->lookaheads);
		
		free_tokenset(this->lookaheads);
	}
	else
	{
		// add new entry to tree
		yacc_stateinfo_add(this->stateinfo, this->state, this->reduce_as, this->lookaheads);
		
		for (unsigned i = 0, n = this->state->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const t = this->state->grammar_transitions.data[i];
			
			dpvs(t->grammar);
			
			struct avl_node_t* node = avl_search(shared->new_grammar, &t->grammar);
			
			assert(node);
			
			struct named_grammar* ng = node->item;
			
			struct gegex* substate = ng->grammar;
			
			struct tokenset* lookaheads = new_tokenset();
			
			struct gegex* to = t->to;
			
			if (to->is_reduction_point)
			{
				tokenset_update(lookaheads, this->lookaheads);
				
				lookahead_deps_add(this->ldeps, this->state, substate);
			}
			
			for (unsigned i = 0, n = to->transitions.n; i < n; i++)
			{
				tokenset_add(lookaheads, to->transitions.data[i]->token);
			}
			
			for (unsigned i = 0, n = to->grammar_transitions.n; i < n; i++)
			{
				const char* grammar = to->grammar_transitions.data[i]->grammar;
				
				dpvs(grammar);
				
				tokenset_update(lookaheads, shared_lookup_firsts(shared, grammar));
			}
			
			// submit this new task
			heap_push(shared->todo, new_expand_tree_task(this->stateinfo, this->ldeps, substate, t->grammar, lookaheads));
		}
		
		heap_push(shared->todo, new_percolate_lookaheads_task(this->stateinfo, this->state, this->ldeps));
	}
	
	EXIT;
}
















