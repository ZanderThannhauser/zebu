

#include <debug.h>

#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/foreach.h>
#include <avl/free_tree.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>

#include <named/grammar/struct.h>

#include <named/tokenset/new.h>
#include <named/tokenset/compare.h>
#include <named/tokenset/free.h>

/*#include <named/strset/new.h>*/
#include <named/strset/compare.h>
#include <named/strset/free.h>

#include "task/explore_firsts/new.h"
#include "task/percolate_firsts/new.h"
#include "task/explore_lookaheads/new.h"
#include "task/percolate_lookaheads/new.h"
#include "task/add_reductions/new.h"

#include "task/compare.h"
#include "task/process.h"
#include "task/dotout.h"
#include "task/free.h"

#include "heap/new.h"
#include "heap/pop.h"
#include "heap/is_nonempty.h"
#include "heap/push.h"
#include "heap/free.h"

#include "shared.h"
#include "run_tasks.h"

void run_tasks(
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct shared* shared = smalloc(sizeof(*shared));
	
	struct heap* todo = new_heap(compare_tasks);
	
	shared->done = new_avl_tree(compare_tasks, free_task);
	shared->grammars = grammars;
	shared->todo = todo;
	
	shared->firsts.sets = new_avl_tree(compare_named_tokensets, free_named_tokenset);
	shared->firsts.dependant_of = new_avl_tree(compare_named_strsets, free_named_strset);
	shared->firsts.dependant_on = new_avl_tree(compare_named_strsets, free_named_strset);
	
	shared->lookaheads.sets = new_avl_tree(compare_named_tokensets, free_named_tokenset);
	shared->lookaheads.dependant_of = new_avl_tree(compare_named_strsets, free_named_strset);
	shared->lookaheads.dependant_on = new_avl_tree(compare_named_strsets, free_named_strset);
	
	avl_tree_foreach(grammars, ({
		void run (const void* item) {
			const struct named_grammar* ng = item;
			
			dpvs(ng->name);
			
			struct tokenset* firsts = new_tokenset();
			
			struct tokenset* lookaheads = new_tokenset();
			
			if (strequals(ng->name, "(start)"))
				tokenset_add(lookaheads, /* EOF token: */ 0);
			
			safe_avl_insert(shared->firsts.sets, new_named_tokenset(ng->name, firsts));
			safe_avl_insert(shared->lookaheads.sets, new_named_tokenset(ng->name, lookaheads));
			
			heap_push(todo, new_explore_firsts_task(ng->name, ng->start));
			heap_push(todo, new_percolate_firsts_task(ng->name));
			heap_push(todo, new_explore_lookaheads_task(ng->name, ng->start, NULL, ng->end, scratchpad));
			heap_push(todo, new_percolate_lookaheads_task(ng->name));
			heap_push(todo, new_add_reductions_task(ng->name, ng->end, scratchpad));
			// heap.push(new lambda_subgrammars()) //
 		}
		run;
	}));
	
	while (is_heap_nonempty(todo))
	{
		struct task* task = heap_pop(todo);
		
		task_process(task, shared);
		
		task_dotout(task, shared);
		
		free_task(task);
	}
	
	avl_free_tree(shared->done);
	
	avl_free_tree(shared->firsts.sets);
	avl_free_tree(shared->firsts.dependant_of);
	avl_free_tree(shared->firsts.dependant_on);
	
	avl_free_tree(shared->lookaheads.sets);
	avl_free_tree(shared->lookaheads.dependant_of);
	avl_free_tree(shared->lookaheads.dependant_on);
	
	free_heap(todo);
	
	free(shared);
	
	EXIT;
}

