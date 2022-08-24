
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>
/*#include <avl/insert.h>*/

/*#include <memory/smalloc.h>*/
/*#include <memory/srealloc.h>*/

/*#include "state/struct.h"*/	
/*#include "state/new.h"*/

#include <set/of_regexes/new.h>
#include <set/of_regexes/free.h>

#include "mapping/compare.h"
#include "mapping/free.h"

#include "add_lamda_states.h"

#include "helper.h"

#include "../dotout.h"

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <defines/argv0.h>
#include <cmdln/verbose.h>
#include <misc/default_sighandler.h>
#endif

#include "nfa_to_dfa.h"

struct regex* regex_nfa_to_dfa(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* in
) {
	ENTER;
	
	#ifdef VERBOSE
	unsigned count = 0;
	
	if (verbose)
	{
		void handler(int _)
		{
			char ptr[100] = {};
			
			size_t len = snprintf(ptr, 100, "\e[k" "%s: %s (%u)\r", argv0, "regex_nfa_to_dfa", count);
			
			if (write(1, ptr, len) != len)
			{
				abort();
			}
			
			count++;
		}
		
		signal(SIGALRM, handler);
	}
	#endif
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_regex_mappings, free_regex_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_regex_mappings, free_regex_mapping);
	#endif
	
	#ifdef WITH_ARENAS
	struct regexset* start_set = new_regexset(arena);
	#else
	struct regexset* start_set = new_regexset();
	#endif
	
	regex_add_lamda_states(start_set, in);
	
	#ifdef WITH_ARENAS
	struct regex* new_start = regex_nfa_to_dfa_helper(arena, start_set, mappings);
	#else
	struct regex* new_start = regex_nfa_to_dfa_helper(start_set, mappings);
	#endif
	
	#ifdef DOTOUT
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	
	free_regexset(start_set);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}













