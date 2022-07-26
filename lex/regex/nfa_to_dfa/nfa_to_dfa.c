
#include <avl/free_tree.h>
#include <avl/avl.h>
#include <avl/new.h>
/*#include <avl/insert.h>*/

#include <debug.h>

/*#include <memory/smalloc.h>*/
/*#include <memory/srealloc.h>*/

/*#include "state/struct.h"*/	
/*#include "state/new.h"*/

#include <set/of_regexes/new.h>

#include "mapping/compare.h"
#include "mapping/free.h"

#include "add_lamda_states.h"

#include "helper.h"

#include "../dotout.h"

#include "nfa_to_dfa.h"

struct regex* regex_nfa_to_dfa(struct regex* in, struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare_mappings, free_mapping);
	
	struct regexset* start_set = new_regexset();
	
	regex_add_lamda_states(start_set, in);
	
	struct regex* new_start = nfa_to_dfa_helper(start_set, mappings, arena);
	
	#ifdef DEBUGGING
	regex_dotout(new_start);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}













