
#include <debug.h>

/*#include <misc/phase_counter.h>*/

/*#include <parser/production/gegex/state/struct.h>*/

/*#include "strset/new.h"*/
/*#include "strset/is_empty.h"*/
/*#include "strset/pop.h"*/
/*#include "strset/add.h"*/
/*#include "strset/print.h"*/
#include <avl/foreach.h>
/*#include "strset/update.h"*/
/*#include "strset/free.h"*/

/*#include "tokenset/new.h"*/
/*#include "tokenset/add.h"*/
/*#include "tokenset/print.h"*/
/*#include "tokenset/update.h"*/
/*#include "tokenset/free.h"*/

#include <named/grammar/struct.h>

#include <tokenset/new.h>
#include <tokenset/add.h>

#include <named/tokenset/new.h>
#include <named/tokenset/compare.h>
#include <named/tokenset/free.h>

#include <named/strset/new.h>
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

#include "shared.h"
#include "yacc.h"

void yacc(
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	// add_reductions_task(name, end):
		// reduce = new_gegex();
		// for l in lookaheads[name]:
			// end.add_lambda_transition(l, reduce);
	
	// lambda_subgrammars_task(node):
		// for g in grammars:
			// node.add_lambda_transition(g.start);
	
	// lookup = dict() # nodes -> unsigned state id
	
	// states   = list() # state id -> struct gegex* state
	// machines = list() # state id -> unsigned tokenizer id
	
	// machines = list() # tokenizer id -> struct regex* state
	
	// nfa_to_dfa_task(nodes):
		// tuple = ("nfa-to-dfa", nodes);
		// if tuple in done: return set();
		// done.add(tuple);
		// state = states[nodes];
		// acceptable_tokens = set();
		// for n in nodes:
			// acceptable_tokens.update(t.value for t in n.transitions)
			// acceptable_tokens.update(t.value for t in n.reduction_transitions)
		// machine_id, combined_tokens = get_tokenizer_id(acceptable_tokens);
		// iterators = set();
		// for n in nodes:
			// if n.transitions:
				// iterators.add(iter(n.transitions));
		
		// for combined_token in combined_tokens:
			// source_tokens = lex_lookup_combined_tokens(combined_token);
			// for i in iterators:
				// for t in i:
					// if t.value in source_tokens:
						// i.append(new transition(value = combined_token, to = t.to));
			
			// if we would reduce on this:
				// remember to fix other places:
				// todo.append(new insert_combined_tokens_transitions_task(combined_token));
		
		// while iterators:
			// next = min(i.value for i in iterators);
			// subnodes = set();
			// for i in iterators:
				// if i.current == next:
					// subnodes.add(i.to);
					// if !next(i):
						// iterators.remove(i);
			// add_lambda_transitions(subnodes);
			// substate = states.setdefault(subnodes, new state);
			// state.add_transition(next, substate);
			// todo.add(nfa_to_dfa_task(subnodes));
	
	// simplify_explore(node):
		// if unique:
			// add to lookup
	
	// simplify_clone(node):
		// todo
	
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
			
			avl_insert(shared->firsts.sets, new_named_tokenset(ng->name, firsts));
			
			avl_insert(shared->lookaheads.sets, new_named_tokenset(ng->name, lookaheads));
			
			heap_push(todo, new_explore_firsts_task(ng->name, ng->start));
			
			heap_push(todo, new_percolate_firsts_task(ng->name));
			
			heap_push(todo, new_explore_lookaheads_task(ng->name, ng->start, NULL, ng->end, scratchpad));
			
			heap_push(todo, new_percolate_lookaheads_task(ng->name));
			
			heap_push(todo, new_add_reductions_task(ng->name, ng->end, scratchpad));
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
	
	// heapush(heap, nfa_to_dfa_task(add_lambda_transitions(start->start)));
/*	TODO;*/
	
	// dfa-simplify
/*	TODO;*/
	
/*	avl_free_tree(firsts);*/
	
/*	avl_free_tree(lookaheads);*/
	
	EXIT;
	// return (start, machines)
}






















