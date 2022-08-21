
#include <debug.h>

#include <string.h>

#include <stdlib.h>

#include <macros/strequals.h>

#include <avl/search.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/foreach.h>
#include <set/of_gegexes/enumerate.h>
#include <set/of_gegexes/clear.h>
#include <set/of_gegexes/add.h>
#include <set/of_gegexes/len.h>
#include <set/of_gegexes/free.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>
#include <yacc/gegex/state/add_transition.h>
#include <yacc/gegex/state/add_grammar_transition.h>

#include "macros/len.h"

#include "mapping/struct.h"
#include "mapping/new.h"

#include "add_lambda_states.h"
#include "helper.h"

struct gegex* gegex_nfa_to_dfa_helper(
	struct gegexset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	struct avl_node_t* search_result;
	ENTER;
	
	TODO;
	#if 0
	if ((search_result = avl_search(mappings, &states)))
	{
		struct gegex_mapping* cached = search_result->item;
		
		EXIT;
		return cached->combined_state;
	}
	else
	{
		struct gegex* state = new_gegex(arena);
		
		struct gegex_mapping* mapping = new_gegex_mapping(states, state);
		
		safe_avl_insert(mappings, mapping);
		
		// set this as reduction_point if any states in list are accepting:
		{
			bool is_reduction_point = false;
			
			gegexset_foreach(states, ({
				void runme(struct gegex* ele) {
					if (ele->is_reduction_point) {
						is_reduction_point = true;
					}
				}
				runme;
			}));
			
			state->is_reduction_point = is_reduction_point;
			
			dpvb(state->is_reduction_point);
		}
		
		unsigned (*indexes)[len(states)] = smalloc(sizeof(*indexes));
		
		memset(*indexes, 0, sizeof(*indexes));
		
		struct gegexset* subset = new_gegexset();
		bool assigned;
		unsigned token;
		
		while (({
			assigned = false;
			gegexset_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n) {
						struct gegex* const to = state->transitions.data[index]->to;
						unsigned ele_token = state->transitions.data[index]->token;
						if (!assigned || ele_token < token) {
							gegexset_clear(subset);
							gegex_add_lamda_states(subset, to);
							token = ele_token;
							assigned = true;
						} else if (token == ele_token) {
							gegex_add_lamda_states(subset, to);
						}
					}
				}
				runme;
			}));
			assigned;
		})) {
			dpv(token);
			dpv(len(subset));
			
			struct gegex* to = gegex_nfa_to_dfa_helper(subset, mappings, arena);
			
			gegex_add_transition(state, arena, token, to);
			
			// move forward all indexes that whose ele_token == token
			gegexset_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n && token == state->transitions.data[index]->token)
						(*indexes)[i]++;
				}
				runme;
			}));
		}
		
		memset(*indexes, 0, sizeof(*indexes));
		
		char* grammar;
		while (({
			assigned = false;
			gegexset_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n) {
						struct gegex* const to = state->grammar_transitions.data[index]->to;
						char* ele_grammar = state->grammar_transitions.data[index]->grammar;
						int cmp;
						if (!assigned || (cmp = strcmp(ele_grammar, grammar)) < 0) {
							gegexset_clear(subset);
							gegex_add_lamda_states(subset, to);
							grammar = ele_grammar;
							assigned = true;
						} else if (!cmp) {
							gegex_add_lamda_states(subset, to);
						}
					}
				}
				runme;
			}));
			assigned;
		})) {
			dpvs(grammar);
			dpv(len(subset));
			
			struct gegex* to = gegex_nfa_to_dfa_helper(subset, mappings, arena);
			
			gegex_add_grammar_transition(state, arena, grammar, to);
			
			// move forward all indexes that whose ele_token == token
			gegexset_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n && strequals(grammar, state->grammar_transitions.data[index]->grammar))
						(*indexes)[i]++;
				}
				runme;
			}));
		}
		
		free_gegexset(subset);
		
		free(indexes);
		
		EXIT;
		return state;
	}
	#endif
}




















