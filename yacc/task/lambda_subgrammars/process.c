
#include <debug.h>

#include <parser/production/gegex/state/struct.h>
#include <parser/production/gegex/state/add_lambda_transition.h>

/*#include <tokenset/add.h>*/

/*#include <strset/foreach.h>*/
/*#include <tokenset/update.h>*/

/*#include <heap/push.h>*/

#include "../../shared.h"
/*#include "../../add_dep.h"*/
/*#include "../../get_deps.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
/*#include "new.h"*/
#include "process.h"

void lambda_subgrammars_task_process(struct task* super, struct shared* shared)
{
	struct lambda_subgrammars_task* const this = (void*) super;
	ENTER;
	
	if (!avl_search(shared->done, this))
	{
		dpvs(this->name);
		
		unsigned i, n = this->node->grammar_transitions.n;
		
		assert(n);
		
		for (i = 0; i < n;i++)
		{
			struct gtransition* ele = this->node->grammar_transitions.data[i];
			
			dpvs(ele->grammar);
			
			gegex_add_lambda_transition(this->node, this->scratchpad, ele->start);
		}
		
		super->refcount++;
		safe_avl_insert(shared->done, this);
	}
	
	EXIT;
}
















