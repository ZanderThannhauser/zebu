
#include <debug.h>

#include <avl/new.h>
#include <avl/free_tree.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/free.h>
#include <set/of_gegexes/len.h>

#include <yacc/phase_counter.h>

#include "cache/compare.h"
#include "cache/free.h"

#include <macros/len.h>

#include "../dotout.h"

#include "survey.h"
#include "clone.h"
#include "simplify_dfa.h"

struct gegex* gegex_simplify_dfa(
	struct gegex* start,
	struct memory_arena* scratchpad)
{
	ENTER;
	
	struct avl_tree_t* cache = new_avl_tree(compare_gegex_caches, free_gegex_cache);
	
	struct gegexset* unique_states = new_gegexset();
	
	yacc_phase_counter++;
	
	gegex_survey(cache, unique_states, start);
	
	struct gegex* new_start = gegex_simplify_dfa_clone(cache, unique_states, start, scratchpad);
	
	#ifdef DEBUGGING
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(cache);
	
	free_gegexset(unique_states);
	
	EXIT;
	return new_start;
}

