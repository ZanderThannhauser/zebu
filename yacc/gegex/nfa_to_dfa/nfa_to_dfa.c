
#include <debug.h>

#include <avl/new.h>
#include <avl/free_tree.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/free.h>

#include "mapping/compare.h"
#include "mapping/free.h"

#include "../dotout.h"

#include "add_lambda_states.h"
#include "helper.h"
#include "nfa_to_dfa.h"

struct gegex* gegex_nfa_to_dfa(
	struct gegex* start,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare_gegex_mappings, free_gegex_mapping);
	
	struct gegexset* start_set = new_gegexset();
	
	gegex_add_lamda_states(start_set, start);
	
	struct gegex* new_start = gegex_nfa_to_dfa_helper(start_set, mappings, scratchpad);
	
	free_gegexset(start_set);
	
	avl_free_tree(mappings);
	
	#ifdef DEBUGGING
	gegex_dotout(new_start, /* optional_end: */ NULL, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return new_start;
}

