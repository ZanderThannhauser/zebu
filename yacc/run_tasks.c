
#include <assert.h>

#include <stdlib.h>

/*#include <memory/smalloc.h>*/

/*#include <macros/strequals.h>*/

#include <debug.h>

/*#include <avl/new.h>*/
/*#include <avl/safe_insert.h>*/
#include <avl/foreach.h>
/*#include <avl/free_tree.h>*/

/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/add.h>*/

#include <named/grammar/struct.h>

/*#include <named/tokenset/new.h>*/
/*#include <named/tokenset/compare.h>*/
/*#include <named/tokenset/free.h>*/

/*#include <named/strset/compare.h>*/
/*#include <named/strset/free.h>*/

#include "task/refcount/new.h"
#include "task/setup_trie/new.h"

/*#include "task/explore_firsts/new.h"*/
/*#include "task/percolate_firsts/new.h"*/
/*#include "task/explore_lookaheads/new.h"*/
/*#include "task/percolate_lookaheads/new.h"*/
/*#include "task/add_reductions/new.h"*/

/*#include "task/compare.h"*/
#include "task/process.h"
#include "task/dotout.h"
#include "task/free.h"

/*#include "heap/new.h"*/
#include "heap/pop.h"
#include "heap/is_nonempty.h"
#include "heap/push.h"
/*#include "heap/free.h"*/

#include "shared/struct.h"

#include "run_tasks.h"

void run_tasks(
	struct yacc_shared* shared,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct heap* const todo = shared->todo;
	
	avl_tree_foreach(shared->grammar, ({
		void run (const void* item) {
			const struct named_grammar* ng = item;
			heap_push(todo, new_refcount_task(scratchpad, ng->grammar, ng->grammar));
			heap_push(todo, new_setup_trie_task(scratchpad, ng->grammar, ng->name));
		}
		run;
	}));
	
	while (is_heap_nonempty(todo))
	{
		struct task* task = heap_pop(todo);
		
		task_process(task, shared);
		
		#ifdef DEBUGGING
		task_dotout(task, shared);
		#endif
		
		free_task(task);
	}
	
	EXIT;
}














