
#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/safe_insert.h>*/

#include <yacc/gegex/state/struct.h>

#include <set/of_tokens/add.h>
/*#include <set/of_tokens/print.h>*/

/*#include <heap/push.h>*/

#include "../../shared/struct.h"
#include "../../shared/add_firsts_dep.h"
#include "../../shared/lookup_firsts.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void explore_firsts_task_process(struct task* super, struct yacc_shared* shared)
{
	struct explore_firsts_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	struct tokenset* first = shared_lookup_firsts(shared, this->name);
	
	unsigned i, n;
	for (i = 0, n = this->node->transitions.n; i < n; i++)
	{
		tokenset_add(first, this->node->transitions.data[i]->token);
	}
	
	for (i = 0, n = this->node->grammar_transitions.n; i < n; i++)
	{
		const struct gtransition* const g = this->node->grammar_transitions.data[i];
		
		dpvs(g->grammar);
		
		add_firsts_dep(shared, shared->firsts.dependant_on, this->name, g->grammar);
		add_firsts_dep(shared, shared->firsts.dependant_of, g->grammar, this->name);
	}
	
	EXIT;
}
















