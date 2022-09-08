
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <heap/new.h>
#include <heap/push.h>
#include <heap/len.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <set/lexstate/new.h>
#include <set/lexstate/foreach.h>
#include <set/lexstate/clone.h>
#include <set/lexstate/free.h>

#include <set/unsigned/compare.h>

/*#include "../struct.h"*/
#include "../state/struct.h"
#include "../state/free.h"

/*#include "../build_tokenizer/node/struct.h"*/

#include "dependent_of_node/struct.h"
#include "dependent_of_node/compare.h"
#include "dependent_of_node/free.h"

#include "same_as_node/new.h"
#include "same_as_node/compare.h"
#include "same_as_node/free.h"

#include "task/struct.h"
#include "task/new.h"
#include "task/compare.h"
#include "task/free.h"

#include "build_universe.h"
#include "minimize_lexer.h"
#include "mark_as_unequal.h"
#include "traverse_and_clone.h"
#include "add_dep.h"

void lex_minimize_lexer(
	struct lex* this,
	struct yacc_state* ystart)
{
	ENTER;
	
	struct lexstateset* universe = minimize_lexer_build_universe(this);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_lex_dependent_of_nodes, free_lex_dependent_of_node);
	
	struct heap* todo = new_heap(compare_lex_simplify_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n = lexstateset_len(universe);
	
	dpv(n);
	
	n = (n * (n - 1)) / 2;
	
	dpv(n);
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "zebu: minimize lexer (build dependencies): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* a) {
			lexstateset_foreach(universe, ({
				void runme(struct lex_state* b) {
					if (a < b)
					{
						ENTER;
						
						bool unequal = false;
						
						if (!a->accepts != !b->accepts)
							unequal = true;
						else if (a->accepts && b->accepts && compare_unsignedsets(a->accepts, b->accepts))
							unequal = true;
						else if (!a->EOF_transition_to != !b->EOF_transition_to)
							unequal = true;
						else if (a->EOF_transition_to && b->EOF_transition_to)
							lex_simplify_dfa_add_dep(dependent_of, a, b, a->EOF_transition_to, b->EOF_transition_to);
							
						for (unsigned i = 0, n = 256; !unequal && i < n; i++)
						{
							struct lex_state* at = a->transitions[i];
							struct lex_state* bt = b->transitions[i];
							
							if (!at != !bt)
								unequal = true;
							else if (at && bt)
								lex_simplify_dfa_add_dep(dependent_of, a, b, at, bt);
						}
						
						if (unequal)
							heap_push(todo, new_lex_simplify_task(a, b, 0));
						
						#ifdef VERBOSE
						count++;
						#endif
						
						EXIT;
					}
				}
				runme;
			}));
		}
		runme;
	}));
	
	#ifdef VERBOSE
	void handler12(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "zebu: minimize tokenizer (allocating dependency-trees): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	count = 0, n = lexstateset_len(universe);
	
	signal(SIGALRM, handler12);
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_lex_same_as_nodes, free_lex_same_as_node);
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* a) {
			ENTER;
			
			struct lexstateset* uni = lexstateset_clone(universe);
			
			struct lex_same_as_node* sa = new_lex_same_as_node(a, uni);
			
			avl_insert(connections, sa);
			
			#ifdef VERBOSE
			count++;
			#endif
			
			EXIT;
		}
		runme;
	}));
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + heap_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: minimize tokenizer (percolate): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (heap_len(todo))
	{
		struct lex_simplify_task* task = heap_pop(todo);
		
		if (lex_simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct lex_dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(void* ptr) {
						const struct lex_pair* pair = ptr;
						
						heap_push(todo, new_lex_simplify_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
		}
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		free_lex_simplify_task(task);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	lex_minimize_traverse_and_clone(connections, ystart);
	
	struct lexstateset* freed = new_lexstateset();
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* state) {
			free_lex_state(freed, state);
		}
		runme;
	}));
	
	free_lexstateset(freed);
	
	avl_free_tree(dependent_of);
	
	free_lexstateset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
}


























