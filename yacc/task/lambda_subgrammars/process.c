
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
/*#include <avl/safe_insert.h>*/

#include <named/grammar/struct.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/add_lambda_transition.h>

#include "../../shared/struct.h"

#include "struct.h"
#include "process.h"

void lambda_subgrammars_task_process(struct task* super, struct yacc_shared* shared)
{
	struct lambda_subgrammars_task* const this = (void*) super;
	ENTER;
	
	unsigned i, n = this->node->grammar_transitions.n;
	
	assert(n);
	
	for (i = 0; i < n;i++)
	{
		struct gtransition* ele = this->node->grammar_transitions.data[i];
		
		dpvs(ele->grammar);
		
		struct avl_node_t* node = avl_search(shared->new_grammar, &ele->grammar);
		
		assert(node);
		
		struct named_grammar* ng = node->item;
		
		dpv(ng->grammar);
		
		gegex_add_lambda_transition(this->node, this->scratchpad, ng->grammar);
	}

	EXIT;
}
















