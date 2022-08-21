
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
/*#include <avl/safe_insert.h>*/

/*#include <yacc/gegex/state/struct.h>*/

#include <named/grammar/struct.h>

/*#include <set/of_tokens/free.h>*/

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
/*#include <set/of_tokens/update.h>*/
/*#include <set/of_tokens/clone.h>*/

#include <heap/push.h>

#include "../../stateinfo/new.h"
/*#include "../../tree/contains.h"*/
/*#include "../../tree/add.h"*/

#include "../expand_tree/new.h"
#include "../free_lookahead_deps/new.h"
#include "../add_transition/new.h"

#include "../../lookahead_deps/new.h"
/*#include "../../lookahead_deps/add.h"*/

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
#include "new.h"
#include "process.h"

void setup_start_task_process(struct task* super, struct yacc_shared* shared)
{
	// struct setup_start_task* const this = (void*) super;
	ENTER;
	
	TODO;
	#if 0
	struct yacc_stateinfo* tree = new_yacc_stateinfo();
	
	struct lookahead_deps* ldeps = new_lookahead_deps();
	
	struct tokenset* lookahead = new_tokenset();
	
	tokenset_add(lookahead, shared->EOF_token_id);
	
	struct gegex* start;
	{
		struct avl_node_t* node = avl_search(shared->new_grammar, (char*[]) {"(start)"});
		assert(node);
		struct named_grammar* ng = node->item;
		start = ng->grammar;
	}
	
	dpv(start);
	
	heap_push(shared->todo, new_expand_tree_task(tree, ldeps, start, "(start)", lookahead));
	
	//// heap_push(todo, new_percolate_lookaheads_task(ldeps, gegex));
	
	heap_push(shared->todo, new_free_lookahead_deps_task(ldeps));
	
	heap_push(shared->todo, new_add_transition_task(&shared->yacc_start, tree));
	
	//// heap_push(todo, new_expand_state_task(tree, state));
	#endif
	
	EXIT;
}
















