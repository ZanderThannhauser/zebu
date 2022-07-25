
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/free_tree.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/phase_counter.h>

#include "../dotout.h"

#include "../state/struct.h"

#include "cache/compare.h"
#include "cache/free.h"

#include "regex_ll/new.h"
#include "regex_ll/free.h"

#include "survey.h"
#include "clone.h"
#include "simplify_dfa.h"

struct regex* regex_simplify_dfa(
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* cache = new_avl_tree(compare_caches, free_cache);
	
	struct regex_ll* unique_nodes = new_regex_ll(cache);
	
	phase_counter++;
	
	simplify_dfa_survey(unique_nodes, original_start);
	
	struct regex* new_start = simplify_dfa_clone(
		unique_nodes, original_start, arena);
	
	free_regex_ll(unique_nodes);
	
	avl_free_tree(cache);
	
	#ifdef DEBUGGING
	regex_dotout(new_start);
	#endif
	
	EXIT;
	return new_start;
}
























