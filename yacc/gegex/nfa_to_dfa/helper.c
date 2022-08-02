
#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include <set/of_gegexes/foreach.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>

#include "mapping/new.h"

#include "helper.h"

struct gegex* gegex_nfa_to_dfa_helper(
	struct gegexset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	struct avl_node_t* search_result;
	ENTER;
	
	if ((search_result = avl_search(mappings, &states)))
	{
		TODO;
		#if 0
		struct mapping* cached = search_result->item;
		
		EXIT;
		return cached->combined_state;
		#endif
	}
	else
	{
		struct gegex* state = new_gegex(arena);
		
		struct gegex_mapping* mapping = new_gegex_mapping(states, state);
		
		safe_avl_insert(mappings, mapping);
		
		// set this as reduction_point if any states in list are accepting:
		{
			bool reduction_point = false;
			
			gegexset_foreach(states, ({
				void runme(struct gegex* ele) {
					if (ele->reduction_point)
						reduction_point = true;
				}
				runme;
			}));
			
			state->reduction_point = reduction_point;
			
			dpvb(state->reduction_point);
		}
		
		// find minimum (token) transition value
		TODO;
		// make new set of new gegex sets
		TODO;
		// call self, add transition
		TODO;
		
		// find minimum (grammar) transition value
		TODO;
		// make new set of new gegex sets
		TODO;
		// call self, add transition
		TODO;
		
		EXIT;
		return state;
	}
}




















