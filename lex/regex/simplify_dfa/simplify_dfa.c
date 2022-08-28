
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <avl/alloc_tree.h>*/
#include <avl/foreach.h>
/*#include <avl/search.h>*/
/*#include <avl/free_tree.h>*/
/*#include <avl/insert.h>*/

/*#include <cmdln/verbose.h>*/

#include <set/regex/new.h>
#include <set/regex/free.h>
#include <set/regex/clone.h>
#include <set/regex/foreach.h>
#include <set/regex/free.h>

#include <heap/new.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/free.h>

/*#include <lex/regex/state/struct.h>*/
/*#include <lex/regex/dotout.h>*/

#ifdef VERBOSE
/*#include <unistd.h>*/
/*#include <signal.h>*/
/*#include <string.h>*/
/*#include <stdlib.h>*/
#include <set/regex/struct.h>
#include <heap/struct.h>
#include <macros/N.h>
/*#include <macros/max.h>*/
/*#include <defines/argv0.h>*/
#include <misc/default_sighandler.h>
#include <cmdln/verbose.h>
#include <misc/colors.h>
#endif

#include "../dotout.h"
#include "../state/struct.h"
#include "../state/transition/struct.h"

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

#include "mark_as_unequal.h"
#include "dotout.h"
#include "add_dep.h"
#include "clone.h"
#include "build_universe.h"
#include "simplify_dfa.h"

struct regex* regex_simplify_dfa(struct regex* original_start)
{
	ENTER;
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_regex_dependent_of_nodes, free_regex_dependent_of_node);
	
	struct regexset* universe = new_regexset();
	
	regex_simplify_dfa_build_universe(universe, original_start);
	
	struct heap* todo = new_heap(compare_regex_simplify_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n;
	
	void handler1(int _)
	{
		char buffer[1000] = {};
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "regex-simplify (build deps)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		dpv(universe->n);
		
		n = (universe->n * (universe->n - 1)) / 2;
		
		signal(SIGALRM, handler1);
	}
	#endif
	
	regexset_foreach(universe, ({
		void runme(struct regex* a) {
			regexset_foreach(universe, ({
				void runme(struct regex* b) {
					if (a < b)
					{
						ENTER;
					
						bool unequal = false;
						
						if (a->is_accepting != b->is_accepting)
						{
							unequal = true;
						}
						
						struct avl_node_t* a_node = a->transitions->head;
						struct avl_node_t* b_node = b->transitions->head;
						
						while (!unequal && a_node && b_node)
						{
							const struct regex_transition* const at = a_node->item;
							const struct regex_transition* const bt = b_node->item;
							
							if (at->value < bt->value)
							{
								if (b->default_transition_to)
								{
									TODO;
									#if 0
									#ifdef WITH_ARENAS
									simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
									#else
									simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
									#endif
									#endif
									a_node = a_node->next;
								}
								else
								{
									unequal = true;
								}
							}
							else if (at->value > bt->value)
							{
								TODO;
								#if 0
								if (a->default_transition_to)
								{
									#ifdef WITH_ARENAS
									simplify_dfa_add_dep(arena, dependent_of, a, b, a->default_transition_to, bt->to);
									#else
									simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
									#endif
								}
								else
								{
									unequal = true;
								}
								
								b_i++;
								#endif
							}
							else
							{
								regex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
								
								a_node = a_node->next;
								b_node = b_node->next;
							}
						}
						
						while (!unequal && a_node && b->default_transition_to)
						{
							TODO;
							#if 0
							const struct transition* const at = a->transitions.data[a_i++];
							
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
							#endif
							#endif
						}
						
						while (!unequal && a->default_transition_to && b_node)
						{
							TODO;
							#if 0
							const struct transition* const bt = b->transitions.data[b_i++];
							
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b, a->default_transition_to, bt->to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
							#endif
							#endif
						}
						
						if (!unequal && (!a_node != !b_node))
						{
							unequal = true;
						}
						
						if (!unequal && (!a->default_transition_to != !b->default_transition_to))
						{
							unequal = true;
						}
						
						if (!unequal && a->default_transition_to && b->default_transition_to)
						{
							TODO;
							#if 0
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#endif
							#endif
						}
						
						if (unequal)
						{
							heap_push(todo, new_regex_simplify_task(a, b, 0));
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
		char ptr[200] = {};
		
		size_t len = snprintf(ptr, 200,
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "simplify (allocating dep-trees)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		count = 0, n = universe->n;
		signal(SIGALRM, handler12);
	}
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_regex_same_as_nodes, free_regex_same_as_node);
	
	regexset_foreach(universe, ({
		void runme(struct regex* a) {
			ENTER;
			
			struct regexset* uni = regexset_clone(universe);
			
			struct regex_same_as_node* sa = new_regex_same_as_node(a, uni);
			
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
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: regex-simplify (percolate): %u of %u (%.2f)\r", argv0,
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		signal(SIGALRM, handler2);
	}
	#endif
	
	#ifdef DOTOUT
	simplify_dfa_dotout(universe, connections, 0);
	#endif
	
	while (is_heap_nonempty(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct regex_simplify_task* task = heap_pop(todo);
		
		if (regex_simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct regex_dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(const void* ptr) {
						const struct regex_pair* pair = ptr;
						heap_push(todo, new_regex_simplify_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
			
			#ifdef DOTOUT
			simplify_dfa_dotout(universe, connections, task->hopcount);
			#endif
		}
		
		free_regex_simplify_task(task);
	}
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	
	struct regex* new_start = regex_simplify_dfa_clone(connections, original_start);
	
	#ifdef DOTOUT
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(dependent_of);
	
	free_regexset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
	return new_start;
}























