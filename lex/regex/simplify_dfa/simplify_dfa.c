
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/insert.h>

#include <cmdln/verbose.h>

#include <tree/of_regexes/new.h>
#include <tree/of_regexes/free.h>
#include <tree/of_regexes/clone.h>
#include <tree/of_regexes/foreach.h>
#include <tree/of_regexes/free.h>

#include <heap/new.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/free.h>

#include <lex/regex/state/struct.h>
#include <lex/regex/dotout.h>

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

#ifdef RELEASE
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <tree/of_regexes/struct.h>
#include <heap/struct.h>
#include <macros/N.h>
#include <macros/max.h>
#include <defines/argv0.h>
#include <misc/default_sighandler.h>
#endif

#include "mark_as_unequal.h"
#include "dotout.h"
#include "add_dep.h"
#include "clone.h"
#include "build_universe.h"
#include "simplify_dfa.h"

#ifdef RELEASE
static const char* colors[] = {
	"\e[38;2;200;0;0m",
	"\e[38;2;100;100;0m",
	"\e[38;2;0;200;0m",
	"\e[38;2;0;100;100m",
	"\e[38;2;0;0;200m",
	"\e[38;2;100;0;100m",
};
#endif

struct regex* regex_simplify_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* original_start)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* dependent_of = avl_alloc_tree(arena, compare_dependent_of_nodes, free_dependent_of_node);
	#else
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_dependent_of_nodes, free_dependent_of_node);
	#endif
	
	#ifdef WITH_ARENAS
	struct regextree* universe = new_regextree(arena);
	#else
	struct regextree* universe = new_regextree();
	#endif
	
	simplify_dfa_build_universe(universe, original_start);
	
	#ifdef WITH_ARENAS
	struct heap* todo = new_heap(arena, compare_simplify_tasks);
	#else
	struct heap* todo = new_heap(compare_simplify_tasks);
	#endif
	
	#ifdef RELEASE
	unsigned count = 0, n;
	
	void handler1(int _)
	{
		char ptr[100] = {};
		
		size_t len = snprintf(ptr, 100,
			"\e[K" "%s: %s: %4u of %4u (%.2f%%)\r",
			argv0, "simplify (build deps)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		n = universe->n * universe->n / 2;
		
		signal(SIGALRM, handler1);
	}
	#endif
	
	regextree_foreach(universe, ({
		void runme(struct regex* a) {
			regextree_foreach(universe, ({
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
						
						while (a_i < a_n && b_i < b_n)
						{
							const struct transition* const at = a->transitions.data[a_i];
							const struct transition* const bt = b->transitions.data[b_i];
							
							if (at->value < bt->value)
							{
								if (b->default_transition_to)
								{
									#ifdef WITH_ARENAS
									simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
									#else
									simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
									#endif
								}
								else
								{
									unequal = true;
								}
								
								a_i++;
							}
							else if (at->value > bt->value)
							{
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
							}
							else
							{
								#ifdef WITH_ARENAS
								simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, bt->to);
								#else
								simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
								#endif
								a_i++, b_i++;
							}
						}
						
						while (a_i < a_n && b->default_transition_to)
						{
							const struct transition* const at = a->transitions.data[a_i++];
							
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
							#endif
						}
						
						while (a->default_transition_to && b_i < b_n)
						{
							const struct transition* const bt = b->transitions.data[b_i++];
							
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b, a->default_transition_to, bt->to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
							#endif
						}
						
						if (!unequal && (a_i < a_n || b_i < b_n))
						{
							unequal = true;
						}
						
						if (!unequal && (!a->default_transition_to != !b->default_transition_to))
						{
							unequal = true;
						}
						
						if (a->default_transition_to && b->default_transition_to)
						{
							#ifdef WITH_ARENAS
							simplify_dfa_add_dep(arena, dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#else
							simplify_dfa_add_dep(dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#endif
						}
						
						if (unequal)
						{
							#ifdef WITH_ARENAS
							heap_push(todo, new_simplify_task(arena, a, b, 0));
							#else
							heap_push(todo, new_simplify_task(a, b, 0));
							#endif
						}
						
						#ifdef RELEASE
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
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* connections = avl_alloc_tree(arena, compare_same_as_nodes, free_same_as_node);
	#else
	struct avl_tree_t* connections = avl_alloc_tree(compare_same_as_nodes, free_same_as_node);
	#endif
	
	regextree_foreach(universe, ({
		void runme(struct regex* a) {
			ENTER;
			
			#ifdef WITH_ARENAS
			struct regextree* uni = regextree_clone(arena, universe);
			#else
			struct regextree* uni = regextree_clone(universe);
			#endif
			
			#ifdef WITH_ARENAS
			struct same_as_node* sa = new_same_as_node(arena, a, uni);
			#else
			struct same_as_node* sa = new_same_as_node(a, uni);
			#endif
			
			avl_insert(connections, sa);
			
			EXIT;
		}
		runme;
	}));
	
	#ifdef RELEASE
	
/*	count = 0;*/
	
	void handler2(int _)
	{
		char ptr[300] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr), "\e[K" "%s: %s:", argv0, "simplify (percolate)");
		
		unsigned i = 0, n = todo->n, print_count = 0;
		unsigned hopcount, task_count = 0;
		
		if (n)
		{
			{
				struct simplify_task* task0 = todo->data[0];
				hopcount = task0->hopcount;
			}
			
			while (print_count < 10 && i < n)
			{
				struct simplify_task* task = todo->data[i++];
				
				if (task->hopcount == hopcount)
				{
					task_count++;
				}
				else
				{
					len += snprintf(ptr + len, sizeof(ptr) - len, " %s%u%s", colors[hopcount % N(colors)], task_count, "\e[0m");
					hopcount = task->hopcount;
					task_count = 1;
					print_count++;
				}
			}
			
			if (print_count < 8)
			{
				len += snprintf(ptr + len, sizeof(ptr) - len, " %s%u%s", colors[hopcount % N(colors)], task_count, "\e[0m");
			}
		}
		
		
		if (len < sizeof(ptr))
		{
/*			len += snprintf(ptr + len, sizeof(ptr) - len, " (%u)\r", count);*/
			ptr[len++] = '\r';
		}
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		signal(SIGALRM, handler2);
	}
	#endif
	
	#ifdef DEBUGGING
	#ifdef WITH_ARENAS
	simplify_dfa_dotout(arena, universe, connections, 0);
	#else
	simplify_dfa_dotout(universe, connections, 0);
	#endif
	#endif
	
	while (is_heap_nonempty(todo))
	{
		struct simplify_task* task = heap_pop(todo);
		
		if (simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(const void* ptr) {
						const struct pair* pair = ptr;
						
						#ifdef WITH_ARENAS
						heap_push(todo, new_simplify_task(arena, pair->a, pair->b, hopcount));
						#else
						heap_push(todo, new_simplify_task(pair->a, pair->b, hopcount));
						#endif
					}
					runme;
				}));
			}
			
			#ifdef DEBUGGING
			#ifdef WITH_ARENAS
			simplify_dfa_dotout(arena, universe, connections, task->hopcount);
			#else
			simplify_dfa_dotout(universe, connections, task->hopcount);
			#endif
			#endif
		}
		
		free_simplify_task(task);
	}
	
	#ifdef RELEASE
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
	}
	#endif
	
	#ifdef WITH_ARENAS
	struct regex* new_start = regex_simplify_dfa_clone(arena, connections, original_start);
	#else
	struct regex* new_start = regex_simplify_dfa_clone(connections, original_start);
	#endif
	
	#ifdef DEBUGGING
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(dependent_of);
	
	free_regextree(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
	return new_start;
}
























