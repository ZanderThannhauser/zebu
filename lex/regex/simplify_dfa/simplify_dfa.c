
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>

#include <set/regex/new.h>
/*#include <set/regex/free.h>*/
#include <set/regex/clone.h>
#include <set/regex/foreach.h>
#include <set/regex/free.h>

#include <set/unsignedchar/contains.h>
#include <set/unsignedchar/are_equal.h>

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
#include <misc/colors.h>
#endif

#include "../dotout.h"
#include "../state/struct.h"

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
			argv0, "regex simplify (build deps)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
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
						
						unsigned a_i = 0, a_n = a->transitions.n;
						unsigned b_i = 0, b_n = b->transitions.n;
						
						while (!unequal && a_i < a_n && b_i < b_n)
						{
							const struct regex_transition* const at = a->transitions.data[a_i];
							const struct regex_transition* const bt = b->transitions.data[b_i];
							
							if (at->value < bt->value)
							{
								if (b->default_transition.to)
								{
									TODO;
									#if 0
									regex_simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
									a_i++;
									#endif
								}
								else
								{
									unequal = true;
								}
							}
							else if (at->value > bt->value)
							{
								if (a->default_transition.to && !unsignedcharset_contains(a->default_transition.exceptions, bt->value))
								{
									regex_simplify_dfa_add_dep(dependent_of, a, b, a->default_transition.to, bt->to);
									b_i++;
								}
								else
								{
									unequal = true;
								}
							}
							else
							{
								regex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
								
								a_i++, b_i++;
							}
						}
						
						while (!unequal && a_i < a_n && b->default_transition.to)
						{
							const struct regex_transition* const at = a->transitions.data[a_i++];
							
							if (!unsignedcharset_contains(b->default_transition.exceptions, at->value))
							{
								regex_simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition.to);
							}
							else
							{
								unequal = true;
							}
						}
						
						while (!unequal && a->default_transition.to && b_i < b_n)
						{
							const struct regex_transition* const bt = b->transitions.data[b_i++];
							
							TODO;
							#if 0
							regex_simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
							#endif
						}
						
						if (!unequal && ((a_i < a_n) != (b_i < b_n)))
						{
							unequal = true;
						}
						
						if (!unequal && (!a->default_transition.to != !b->default_transition.to))
						{
							unequal = true;
						}
						
						if (!unequal && a->default_transition.to && b->default_transition.to)
						{
							// are exception-sets equal?
							if (unsignedcharset_are_equal(a->default_transition.exceptions, b->default_transition.exceptions))
							{
								regex_simplify_dfa_add_dep(dependent_of, a, b, a->default_transition.to, b->default_transition.to);
							}
							else
							{
								// unequal = true;
								TODO;
							}
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
			argv0, "regex simplify (allocating dep-trees)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
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
			"\e[k" "%s: regex simplify (percolate): %u of %u (%.2f%%)\r", argv0,
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
/*	#ifdef DOTOUT*/
/*	simplify_dfa_dotout(universe, connections, 0);*/
/*	#endif*/
	
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
			
/*			#ifdef DOTOUT*/
/*			simplify_dfa_dotout(universe, connections, task->hopcount);*/
/*			#endif*/
		}
		
		free_regex_simplify_task(task);
	}
	
	#ifdef DOTOUT
	simplify_dfa_dotout(universe, connections, 0);
	#endif
	
	#ifdef VERBOSE
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























