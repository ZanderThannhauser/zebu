
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/foreach.h>

#include <set/gegex/struct.h>
#include <set/gegex/new.h>
#include <set/gegex/foreach.h>
#include <set/gegex/clone.h>
#include <set/gegex/free.h>

#include <heap/new.h>
#include <heap/len.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/free.h>

#include <yacc/structinfo/are_equal.h>

#include <gegex/state/struct.h>
#include <gegex/dotout.h>

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

#ifdef VERBOSE
/*#include <unistd.h>*/
/*#include <signal.h>*/
/*#include <string.h>*/
/*#include <stdlib.h>*/
/*#include <tree/of_gegexes/struct.h>*/
/*#include <macros/N.h>*/
/*#include <macros/max.h>*/
#include <misc/default_sighandler.h>
#endif

#include "mark_as_unequal.h"
#include "dotout.h"
#include "add_dep.h"
#include "clone.h"
#include "build_universe.h"
#include "simplify_dfa.h"

struct gegex* gegex_simplify_dfa(struct gegex* original_start)
{
	ENTER;
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_gegex_dependent_of_nodes, free_gegex_dependent_of_node);
	
	struct gegexset* universe = new_gegexset();
	
	gegex_simplify_dfa_build_universe(universe, original_start);
	
	struct heap* todo = new_heap(compare_gegex_simplify_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n = universe->n * universe->n / 2;
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr),
			"\e[K" "zebu: grammar simplify (build dependencies) %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	gegexset_foreach(universe, ({
		void runme(struct gegex* a) {
			gegexset_foreach(universe, ({
				void runme(struct gegex* b) {
					if (a < b)
					{
						ENTER;
						
						bool unequal = false;
						
						if (a->is_reduction_point != b->is_reduction_point)
						{
							unequal = true;
						}
						
						{
							unsigned a_i = 0, a_n = a->transitions.n;
							unsigned b_i = 0, b_n = b->transitions.n;
							
							while (!unequal && a_i < a_n && b_i < b_n)
							{
								const struct gegex_transition* const at = a->transitions.data[a_i];
								const struct gegex_transition* const bt = b->transitions.data[b_i];
								
								if (at->token != bt->token)
								{
									unequal = true;
								}
								else if (!structinfos_are_equal(at->structinfo, bt->structinfo))
								{
									unequal = true;
								}
								else
								{
									gegex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
									a_i++, b_i++;
								}
							}
							
							if (!unequal && (a_i < a_n || b_i < b_n))
							{
								unequal = true;
							}
						}
						
						{
							unsigned a_i = 0, a_n = a->grammar_transitions.n;
							unsigned b_i = 0, b_n = b->grammar_transitions.n;
							
							while (!unequal && a_i < a_n && b_i < b_n)
							{
								const struct gegex_grammar_transition* const at = a->grammar_transitions.data[a_i];
								const struct gegex_grammar_transition* const bt = b->grammar_transitions.data[b_i];
								
								if (!strings_are_equal(at->grammar, bt->grammar))
								{
									unequal = true;
								}
								else if (!structinfos_are_equal(at->structinfo, bt->structinfo))
								{
									unequal = true;
								}
								else
								{
									gegex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
									a_i++, b_i++;
								}
							}
							
							if (!unequal && (a_i < a_n || b_i < b_n))
							{
								unequal = true;
							}
						}
						
						if (unequal)
						{
							heap_push(todo, new_gegex_simplify_task(a, b, 0));
						}
						
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
		
		size_t len = snprintf(ptr, sizeof(ptr),
			"\e[K" "zebu: grammar simplify (allocating dependency-trees): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	count = 0, n = universe->n;
	
	signal(SIGALRM, handler12);
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_gegex_same_as_nodes, free_gegex_same_as_node);
	
	gegexset_foreach(universe, ({
		void runme(struct gegex* a) {
			ENTER;
			
			struct gegexset* uni = gegexset_clone(universe);
			
			struct gegex_same_as_node* sa = new_gegex_same_as_node(a, uni);
			
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
			"\e[K" "zebu: grammar simplify (percolate): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
/*	#ifdef DOTOUT*/
/*	gegex_simplify_dfa_dotout(universe, connections, 0);*/
/*	#endif*/
	
	while (heap_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct gegex_simplify_task* task = heap_pop(todo);
		
		if (gegex_simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct gegex_dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(void* ptr) {
						const struct gegex_pair* pair = ptr;
						
						heap_push(todo, new_gegex_simplify_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
			
/*			#ifdef DOTOUT*/
/*			gegex_simplify_dfa_dotout(universe, connections, task->hopcount);*/
/*			#endif*/
		}
		
		free_gegex_simplify_task(task);
	}
	
	#ifdef DOTOUT
	gegex_simplify_dfa_dotout(universe, connections, 0);
	#endif
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	struct gegex* new_start = gegex_simplify_dfa_clone(connections, original_start);
	
	#ifdef DOTOUT
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(dependent_of);
	
	free_gegexset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
	return new_start;
}























