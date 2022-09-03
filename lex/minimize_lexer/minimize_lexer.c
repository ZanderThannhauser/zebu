
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#if 0

#include <avl/alloc_tree.h>
#include <avl/foreach.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <tree/of_lstates/new.h>
#include <tree/of_lstates/clone.h>
#include <tree/of_lstates/foreach.h>
#include <tree/of_lstates/free.h>

#include <set/of_tokens/compare.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#ifdef VERBOSE
#include <heap/struct.h>
#include <cmdln/verbose.h>
#include <defines/argv0.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <misc/colors.h>
#include <macros/N.h>
#include <misc/default_sighandler.h>
#include <tree/of_lstates/struct.h>
#endif

#include "../struct.h"
#include "../state/struct.h"
#include "../state/free.h"
#include "../build_tokenizer/node/struct.h"

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
#endif

/*#include "build_universe.h"*/
#include "minimize_lexer.h"
/*#include "mark_as_unequal.h"*/
/*#include "traverse_and_clone.h"*/
/*#include "add_dep.h"*/

void lex_minimize_lexer(
	struct lex* this,
	struct yacc_state* ystart)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_lex_dependent_of_nodes, free_lex_dependent_of_node);
	
	struct lstatetree* universe = new_lstatetree();
	
	for (struct avl_node_t* node = this->tokenizer.cache->head; node; node = node->next)
	{
		struct build_tokenizer_node* ele = node->item;
		
		minimize_lexer_build_universe(universe, ele->start);
	}
	
	#ifdef WITH_ARENAS
	struct heap* todo = new_heap(arena, compare_lex_simplify_tasks);
	#else
	struct heap* todo = new_heap(compare_lex_simplify_tasks);
	#endif
	
	#ifdef VERBOSE
	
	dpv(universe->n);
	
	uintmax_t count = 0, n;
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "lexer-simplify (build deps)",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
	{
		n = (universe->n * (universe->n - 1)) / 2;
		
		signal(SIGALRM, handler1);
	}
	#endif
	
	lstatetree_foreach(universe, ({
		void runme(struct lex_state* a) {
			lstatetree_foreach(universe, ({
				void runme(struct lex_state* b) {
					if (a < b)
					{
						ENTER;
						
						bool unequal = false;
						
						if (!a->accepting != !b->accepting)
						{
							unequal = true;
						}
						else if (a->accepting && b->accepting && compare_tokensets(a->accepting, b->accepting))
						{
							unequal = true;
						}
						
						unsigned a_i = 0, a_n = a->transitions.n;
						unsigned b_i = 0, b_n = b->transitions.n;
						
						while (!unequal && a_i < a_n && b_i < b_n)
						{
							const struct ltransition* const at = a->transitions.data[a_i];
							const struct ltransition* const bt = b->transitions.data[b_i];
							
							if (at->value < bt->value)
							{
								if (b->default_transition_to)
								{
									#ifdef WITH_ARENAS
									lex_simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
									#else
									lex_simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
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
									lex_simplify_dfa_add_dep(arena, dependent_of, a, b, a->default_transition_to, bt->to);
									#else
									lex_simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
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
								lex_simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, bt->to);
								#else
								lex_simplify_dfa_add_dep(dependent_of, a, b, at->to, bt->to);
								#endif
								a_i++, b_i++;
							}
						}
						
						while (!unequal && a_i < a_n && b->default_transition_to)
						{
							const struct ltransition* const at = a->transitions.data[a_i++];
							
							#ifdef WITH_ARENAS
							lex_simplify_dfa_add_dep(arena, dependent_of, a, b, at->to, b->default_transition_to);
							#else
							lex_simplify_dfa_add_dep(dependent_of, a, b, at->to, b->default_transition_to);
							#endif
						}
						
						while (!unequal && a->default_transition_to && b_i < b_n)
						{
							const struct ltransition* const bt = b->transitions.data[b_i++];
							
							#ifdef WITH_ARENAS
							lex_simplify_dfa_add_dep(arena, dependent_of, a, b, a->default_transition_to, bt->to);
							#else
							lex_simplify_dfa_add_dep(dependent_of, a, b, a->default_transition_to, bt->to);
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
						
						if (!unequal && a->default_transition_to && b->default_transition_to)
						{
							#ifdef WITH_ARENAS
							lex_simplify_dfa_add_dep(arena, dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#else
							lex_simplify_dfa_add_dep(dependent_of, a, b,
								a->default_transition_to, b->default_transition_to);
							#endif
						}
						
						if (unequal)
						{
							#ifdef WITH_ARENAS
							heap_push(todo, new_lex_simplify_task(arena, a, b, 0));
							#else
							heap_push(todo, new_lex_simplify_task(a, b, 0));
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
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "%s: %s: %4lu of %4lu (%.2f%%)\r",
			argv0, "lexer-simplify (allocating dep-trees)",
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
	struct avl_tree_t* connections = avl_alloc_tree(arena, compare_lex_same_as_nodes, free_lex_same_as_node);
	#else
	struct avl_tree_t* connections = avl_alloc_tree(compare_lex_same_as_nodes, free_lex_same_as_node);
	#endif
	
	lstatetree_foreach(universe, ({
		void runme(struct lex_state* a) {
			ENTER;
			
			#ifdef WITH_ARENAS
			struct lstatetree* uni = lstatetree_clone(arena, universe);
			#else
			struct lstatetree* uni = lstatetree_clone(universe);
			#endif
			
			#ifdef WITH_ARENAS
			struct lex_same_as_node* sa = new_lex_same_as_node(arena, a, uni);
			#else
			struct lex_same_as_node* sa = new_lex_same_as_node(a, uni);
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
				struct lex_simplify_task* task0 = todo->data[0];
				hopcount = task0->hopcount;
			}
			
			while (print_count < 10 && i < n)
			{
				struct lex_simplify_task* task = todo->data[i++];
				
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
	
	while (is_heap_nonempty(todo))
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
					void runme(const void* ptr) {
						const struct lex_pair* pair = ptr;
						
						#ifdef WITH_ARENAS
						heap_push(todo, new_lex_simplify_task(arena, pair->a, pair->b, hopcount));
						#else
						heap_push(todo, new_lex_simplify_task(pair->a, pair->b, hopcount));
						#endif
					}
					runme;
				}));
			}
		}
		
		free_lex_simplify_task(task);
	}
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	
	lex_minimize_traverse_and_clone(connections, ystart);
	
	struct lstatetree* freed = new_lstatetree();
	
	lstatetree_foreach(universe, ({
		void runme(struct lex_state* state) {
			ENTER;
			free_lex_state(freed, state);
			EXIT;
		}
		runme;
	}));
	
	avl_free_tree(dependent_of);
	
	free_lstatetree(freed);
	
	free_lstatetree(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	#endif
	
	EXIT;
}


























