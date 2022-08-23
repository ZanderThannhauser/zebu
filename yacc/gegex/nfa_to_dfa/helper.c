
#include <debug.h>

#include <string.h>

#include <stdlib.h>

#include <macros/strequals.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <tree/of_gegexes/new.h>
#include <tree/of_gegexes/foreach.h>
#include <tree/of_gegexes/enumerate.h>
#include <tree/of_gegexes/clear.h>
#include <tree/of_gegexes/add.h>
#include <tree/of_gegexes/len.h>
#include <tree/of_gegexes/free.h>

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
	#ifdef RELEASE
	unsigned *node_count,
	#endif
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegextree* states,
	struct avl_tree_t* mappings
) {
	struct avl_node_t* search_result;
	ENTER;
	
	if ((search_result = avl_search(mappings, &states)))
	{
		struct gegex_mapping* cached = search_result->item;
		
		EXIT;
		return cached->combined_state;
	}
	else
	{
		#ifdef RELEASE
		(*node_count)++;
		#endif
		
		#ifdef WITH_ARENAS
		struct gegex* state = new_gegex(arena);
		#else
		struct gegex* state = new_gegex();
		#endif
		
		#ifdef WITH_ARENAS
		struct gegex_mapping* mapping = new_gegex_mapping(arena, states, state);
		#else
		struct gegex_mapping* mapping = new_gegex_mapping(states, state);
		#endif
		
		avl_insert(mappings, mapping);
		
		// set this as reduction_point if any states in list are accepting:
		{
			bool is_reduction_point = false;
			
			gegextree_foreach(states, ({
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
		
		#ifdef WITH_ARENAS
		unsigned (*indexes)[len(states)] = arena_malloc(arena, sizeof(*indexes));
		#else
		unsigned (*indexes)[len(states)] = malloc(sizeof(*indexes));
		#endif
		
		memset(*indexes, 0, sizeof(*indexes));
		
		#ifdef WTIH_ARENAS
		struct gegextree* subset = new_gegextree(arena);
		#else
		struct gegextree* subset = new_gegextree();
		#endif
		
		bool assigned;
		unsigned token;
		
		while (({
			assigned = false;
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n) {
						struct gegex* const to = state->transitions.data[index]->to;
						unsigned ele_token = state->transitions.data[index]->token;
						if (!assigned || ele_token < token) {
							gegextree_clear(subset);
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
			
			struct gegex* to = gegex_nfa_to_dfa_helper(
				#ifdef RELEASE
				node_count,
				#endif
				#ifdef WITH_ARENAS
				arena,
				#endif
				subset, mappings);
			
			gegex_add_transition(state, token, to);
			
			// move forward all indexes that whose ele_token == token
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n && token == state->transitions.data[index]->token) {
						(*indexes)[i]++;
					}
				}
				runme;
			}));
		}
		
		memset(*indexes, 0, sizeof(*indexes));
		
		char* grammar;
		while (({
			assigned = false;
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n) {
						struct gegex* const to = state->grammar_transitions.data[index]->to;
						char* ele_grammar = state->grammar_transitions.data[index]->grammar;
						int cmp;
						if (!assigned || (cmp = strcmp(ele_grammar, grammar)) < 0) {
							gegextree_clear(subset);
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
			
			struct gegex* to = gegex_nfa_to_dfa_helper(
				#ifdef RELEASE
				node_count,
				#endif
				#ifdef WITH_ARENAS
				arena,
				#endif
				subset, mappings);
			
			#ifdef WITH_ARENAS
			char* dup = arena_strdup(arena, grammar);
			#else
			char* dup = strdup(grammar);
			#endif
			
			gegex_add_grammar_transition(state, dup, to);
			
			// move forward all indexes that whose ele_token == token
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n && strequals(grammar, state->grammar_transitions.data[index]->grammar))
						(*indexes)[i]++;
				}
				runme;
			}));
		}
		
		free_gegextree(subset);
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, indexes);
		#else
		free(indexes);
		#endif
		
		EXIT;
		return state;
	}
}




















