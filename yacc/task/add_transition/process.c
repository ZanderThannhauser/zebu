
#include <debug.h>

#include <avl/search.h>

/*#include <yacc/gegex/state/struct.h>*/

/*#include <named/grammar/struct.h>*/

/*#include <set/of_tokens/free.h>*/

/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/add.h>*/
/*#include <set/of_tokens/update.h>*/
/*#include <set/of_tokens/clone.h>*/

#include <heap/push.h>

#include <yacc/state/new.h>

/*#include "../../tree/new.h"*/
/*#include "../../tree/contains.h"*/
#include "../../stateinfo/free.h"

/*#include "../expand_tree/new.h"*/

/*#include "../../lookahead_deps/new.h"*/
/*#include "../../lookahead_deps/add.h"*/

#include "../../stateinfo_to_state/struct.h"
#include "../../stateinfo_to_state/new.h"

#include "../build_ystate/new.h"

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
/*#include "new.h"*/
#include "process.h"

void add_transition_task_process(struct task* super, struct yacc_shared* shared)
{
	struct add_transition_task* const this = (void*) super;
	ENTER;
	
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(shared->stateinfo_to_state, &this->stateinfo);
	
	if (node)
	{
		struct stateinfo_to_state* tos = node->item;
		
		*this->write_to_me = tos->state;
		
		free_yacc_stateinfo(this->stateinfo);
	}
	else
	{
		struct yacc_state* state = new_yacc_state(shared->scratchpad);
		
		*this->write_to_me = state;
		
		// add state to mapping:
		{
			struct stateinfo_to_state* tos = new_stateinfo_to_state(this->stateinfo, state);
			safe_avl_insert(shared->stateinfo_to_state, tos);
		}
		
		// submit task to consider transitions from new state
		heap_push(shared->todo, new_build_ystate_task(state, this->stateinfo));
	}
	#endif
	
	EXIT;
}




































