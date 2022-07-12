
#include <debug.h>

#include <misc/phase_counter.h>

#include <parser/production/gegex/state/struct.h>

#include "strset/new.h"
#include "strset/is_empty.h"
#include "strset/pop.h"
#include "strset/add.h"
#include "strset/print.h"
#include "strset/foreach.h"
#include "strset/update.h"
#include "strset/free.h"

#include "tokenset/new.h"
#include "tokenset/add.h"
#include "tokenset/print.h"
#include "tokenset/update.h"
#include "tokenset/free.h"

#include "yacc.h"

void yacc(struct avl_tree_t* grammar)
{
	ENTER;
	
	// explore_first_task::process(grammar, node):
		// tuple = ("explore-first", node);
		// if tuple in done: return set();
		// done.add(tuple);
		// todo = set();
		// first = firsts.lookup.setdefault(grammar, set());
		// first.update(t.value for t in node->transitions)
		// for g in node->grammars:
			// firsts.dependant_on.setdefault(grammar, set()).add(g->name);
			// firsts.dependant_of.setdefault(g->name, set()).add(grammar);
		// for l in node->lambdas:
			// todo.add(new explore_first_task(l));
		// return todo;
	
	// percolate_first_task(grammar):
		// tuple = ("percolate-first", node);
		// if tuple in done: return set();
		// done.add(tuple);
		// before = firsts[grammar];
		// after = before.copy();
		// for dep in firsts.dependant_on[grammar]:
			// after.update(firsts[dep]);
		// todo = set();
		// if before != after:
			// for dep in firsts.dependant_of[grammar]:
				// todo.add(percolate_first_task(dep));
		// return todo;
	
	// explore_lookahead_task::process(grammar, node, end, invocation = None):
		// tuple = ("explore-lookahead", node, invocation);
		// if tuple in done: return set();
		// done.add(tuple);
		// todo = set();
		// if node == end:
			// lookaheads.dependant_on.setdefault(invocation, set()).add(grammar);
			// lookaheads.dependant_of.setdefault(grammar, set()).add(invocation);
		// for t in node->transitions:
			// if invocation:
				// invocation.add(t->value);
			// todo.add(new explore_lookahead_task(t->to, invocation = None));
		// for g in node->grammars:
			// if invocation:
				// invocation.update(firsts[g]);
			// todo.add(new explore_lookahead_task(g->to, invocation = lookaheads[g]));
			// todo.add(new lambda_subgrammars_task(node));
		// for l in node->lambdas:
			// todo.add(new explore_first_task(l, invocation = invocation));
		// return todo;
	
	// percolate_lookahead_task(grammar):
		// tuple = ("percolate-lookahead", node);
		// if tuple in done: return set();
		// before = lookaheads[grammar];
		// after = before.copy();
		// for dep in lookaheads.dependant_on[grammar]:
			// after.update(lookaheads[dep]);
		// todo = set();
		// if before != after:
			// for dep in lookaheads.dependant_of[grammar]:
				// todo.add(percolate_lookahead_task(dep));
		// return todo;
	
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
		// tokenizer_lookup[state], patches = get_tokenizer_id(acceptable_tokens);
		// iterators = set();
		// for n in nodes:
			// if n.transitions:
				// iterators.add(iter(n.transitions));
		// for new_token, source_tokens in patches:
			// maybe add new iterators?
			// or add more transitions to existing iterators?
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
	
	// or maybe run the explorers on the start grammar?
		// which launches sub explorers for the subgrammars?
	
	// for g in grammar:
		// heapush(heap,       explore_first_task(g->start));
		// heapush(heap,     percolate_first_task(g->start));
		// heapush(heap,   explore_lookahead_task(g->start, g->end));
		// heapush(heap, percolate_lookahead_task(g->start));
		// heapush(heap,      add_reductions_task(g->end));
	
	// heapush(heap, nfa_to_dfa_task(add_lambda_transitions(start->start)));
	TODO;
	
	// dfa-simplify
	TODO;
	
	// while todo:
		// runme = heappop(todo);
		// more = runme.process();
		// runme.dotout();
		// for m in more:
			// heappush(todo, more);
	
	avl_free_tree(firsts);
	
	avl_free_tree(lookaheads);
	
	EXIT;
	// return start, machines
}












