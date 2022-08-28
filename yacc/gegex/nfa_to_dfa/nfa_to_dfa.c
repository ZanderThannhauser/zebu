
#if 0
#include <debug.h>

#include <cmdln/verbose.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <tree/of_gegexes/new.h>
#include <tree/of_gegexes/free.h>

#ifdef VERBOSE
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <misc/default_sighandler.h>

#include <defines/argv0.h>
#endif

#include "mapping/compare.h"
#include "mapping/free.h"

#include "../dotout.h"

#include "add_lambda_states.h"
#include "helper.h"
#include "nfa_to_dfa.h"

struct gegex* gegex_nfa_to_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* start
) {
	ENTER;
	
	#ifdef VERBOSE
	unsigned node_count = 0;
	
	if (verbose)
	{
		void handler(int _)
		{
			char ptr[100] = {};
			
			size_t len = snprintf(ptr, 100, "\e[k" "%s: %s (%u)\r", argv0, "gegex_nfa_to_dfa", node_count);
			
			if (write(1, ptr, len) != len)
			{
				abort();
			}
		}
		
		signal(SIGALRM, handler);
	}
	#endif
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_gegex_mappings, free_gegex_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_gegex_mappings, free_gegex_mapping);
	#endif
	
	#ifdef WITH_ARENAS
	struct gegextree* start_set = new_gegextree(arena);
	#else
	struct gegextree* start_set = new_gegextree();
	#endif
	
	gegex_add_lamda_states(start_set, start);
	
	struct gegex* new_start = gegex_nfa_to_dfa_helper(
		#ifdef VERBOSE
		&node_count,
		#endif
		#ifdef WITH_ARENAS
		arena,
		#endif
		start_set, mappings);
	
	free_gegextree(start_set);
	
	avl_free_tree(mappings);
	
	#ifdef DOTOUT
	gegex_dotout(new_start, /* optional_end: */ NULL, __PRETTY_FUNCTION__);
	#endif
	
	#ifdef VERBOSE
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
	}
	#endif
	
	EXIT;
	return new_start;
}










#endif
