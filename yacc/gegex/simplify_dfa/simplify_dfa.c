
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

#include <debug.h>

#include <cmdln/verbose.h>

#include <defines/argv0.h>

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/insert.h>

/*#include <cmdln/verbose.h>*/

#include <tree/of_gegexes/new.h>
#include <tree/of_gegexes/clone.h>
#include <tree/of_gegexes/foreach.h>
#include <tree/of_gegexes/free.h>

#include <heap/new.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/is_nonempty.h>
#include <heap/free.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/dotout.h>

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
#include <signal.h>
#include <string.h>
/*#include <stdlib.h>*/
#include <tree/of_gegexes/struct.h>
#include <heap/struct.h>
#include <macros/N.h>
/*#include <macros/max.h>*/
/*#include <defines/argv0.h>*/
#include <misc/default_sighandler.h>
#endif

#include "mark_as_unequal.h"
#include "dotout.h"
#include "add_dep.h"
#include "clone.h"
#include "build_universe.h"
#include "simplify_dfa.h"

#ifdef VERBOSE
static const char* colors[] = {
	"\e[38;2;255;000;000m",
	"\e[38;2;255;165;000m",
	"\e[38;2;255;255;000m",
	"\e[38;2;000;128;100m",
	"\e[38;2;000;000;255m",
	"\e[38;2;075;000;130m",
	"\e[38;2;238;120;238m",
};
#endif

struct gegex* gegex_simplify_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* original_start
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* dependent_of = avl_alloc_tree(arena,
		compare_gegex_dependent_of_nodes, free_gegex_dependent_of_node);
	#else
	struct avl_tree_t* dependent_of = avl_alloc_tree(
		compare_gegex_dependent_of_nodes, free_gegex_dependent_of_node);
	#endif
	
	#ifdef WITH_ARENAS
	struct gegextree* universe = new_gegextree(arena);
	#else
	struct gegextree* universe = new_gegextree();
	#endif
	
	gegex_simplify_dfa_build_universe(universe, original_start);
	
	#ifdef WITH_ARENAS
	struct heap* todo = new_heap(arena, compare_gegex_simplify_tasks);
	#else
	struct heap* todo = new_heap(compare_gegex_simplify_tasks);
	#endif
	
	#ifdef VERBOSE
	uintmax_t count = 0, n;
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr),
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "grammar-simplify (build deps)",
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
	
	gegextree_foreach(universe, ({
		void runme(struct gegex* a) {
			gegextree_foreach(universe, ({
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
							
/*							printf("%u, %u\n", a_n, b_n);*/
							
							while (!unequal && a_i < a_n && b_i < b_n)
							{
								const struct transition* const at = a->transitions.data[a_i];
								const struct transition* const bt = b->transitions.data[b_i];
								
								if (at->token < bt->token)
								{
									unequal = true, a_i++;
								}
								else if (at->token > bt->token)
								{
									unequal = true, b_i++;
								}
								else
								{
									#ifdef WITH_ARENAS
									gegex_simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, bt->to);
									#else
									gegex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
									#endif
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
							
/*							printf("%u, %u\n", a_n, b_n);*/
							
							while (!unequal && a_i < a_n && b_i < b_n)
							{
								const struct gtransition* const at = a->grammar_transitions.data[a_i];
								const struct gtransition* const bt = b->grammar_transitions.data[b_i];
								
								int cmp = strcmp(at->grammar, bt->grammar);
								
								if (cmp < 0)
								{
									unequal = true, a_i++;
								}
								else if (cmp > 0)
								{
									unequal = true, b_i++;
								}
								else
								{
									#ifdef WITH_ARENAS
									gegex_simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, bt->to);
									#else
									gegex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
									#endif
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
							#ifdef WITH_ARENAS
							heap_push(todo, new_gegex_simplify_task(arena, a, b, 0));
							#else
							heap_push(todo, new_gegex_simplify_task(a, b, 0));
							#endif
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
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "grammar-simplify (allocating dep-trees)",
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
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* connections = avl_alloc_tree(arena, compare_gegex_same_as_nodes, free_gegex_same_as_node);
	#else
	struct avl_tree_t* connections = avl_alloc_tree(compare_gegex_same_as_nodes, free_gegex_same_as_node);
	#endif
	
	gegextree_foreach(universe, ({
		void runme(struct gegex* a) {
			ENTER;
			
			#ifdef WITH_ARENAS
			struct gegextree* uni = gegextree_clone(arena, universe);
			#else
			struct gegextree* uni = gegextree_clone(universe);
			#endif
			
			#ifdef WITH_ARENAS
			struct gegex_same_as_node* sa = new_gegex_same_as_node(arena, a, uni);
			#else
			struct gegex_same_as_node* sa = new_gegex_same_as_node(a, uni);
			#endif
			
			avl_insert(connections, sa);
			
			#ifdef VERBOSE
			count++;
			#endif
			
			EXIT;
		}
		runme;
	}));
	
	#ifdef VERBOSE
	
	void handler2(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr), "\e[K" "%s: %s:", argv0, "simplify (percolate)");
		
		unsigned i = 0, n = todo->n, print_count = 0;
		unsigned hopcount, task_count = 0;
		
		if (n)
		{
			{
				struct gegex_simplify_task* task0 = todo->data[0];
				hopcount = task0->hopcount;
			}
			
			while (print_count < 10 && i < n)
			{
				struct gegex_simplify_task* task = todo->data[i++];
				
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
	
	#ifdef DOTOUT
	#ifdef WITH_ARENAS
	gegex_simplify_dfa_dotout(arena, universe, connections, 0);
	#else
	gegex_simplify_dfa_dotout(universe, connections, 0);
	#endif
	#endif
	
	while (is_heap_nonempty(todo))
	{
		struct gegex_simplify_task* task = heap_pop(todo);
		
		if (gegex_simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct gegex_dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(const void* ptr) {
						const struct gegex_pair* pair = ptr;
						
						#ifdef WITH_ARENAS
						heap_push(todo, new_gegex_simplify_task(arena, pair->a, pair->b, hopcount));
						#else
						heap_push(todo, new_gegex_simplify_task(pair->a, pair->b, hopcount));
						#endif
					}
					runme;
				}));
			}
			
			#ifdef DOTOUT
			#ifdef WITH_ARENAS
			gegex_simplify_dfa_dotout(arena, universe, connections, task->hopcount);
			#else
			gegex_simplify_dfa_dotout(universe, connections, task->hopcount);
			#endif
			#endif
		}
		
		free_gegex_simplify_task(task);
	}
	
	#ifdef VERBOSE
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
	}
	#endif
	
	#ifdef WITH_ARENAS
	struct gegex* new_start = gegex_simplify_dfa_clone(arena, connections, original_start);
	#else
	struct gegex* new_start = gegex_simplify_dfa_clone(connections, original_start);
	#endif
	
	#ifdef DOTOUT
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(dependent_of);
	
	free_gegextree(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	EXIT;
	return new_start;
}
























