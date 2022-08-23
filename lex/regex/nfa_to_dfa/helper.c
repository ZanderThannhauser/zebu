
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <arena/realloc.h>

/*#include <heap/struct.h>*/
#include <heap/new.h>
#include <heap/struct.h>
#include <heap/is_nonempty.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/free.h>

#include <set/of_regexes/new.h>
#include <set/of_regexes/add.h>
#include <set/of_regexes/foreach.h>
#include <set/of_regexes/is_nonempty.h>
#include <set/of_regexes/free.h>

#include "iterator/struct.h"
#include "iterator/new.h"
#include "iterator/compare.h"
#include "iterator/free.h"

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"

#include "add_lamda_states.h"
#include "helper.h"

/*#include "regexset/struct.h"*/
/*#include "regexset/insert.h"*/
/*#include "regexset/new.h"*/

#include "mapping/struct.h"
#include "mapping/new.h"

struct regex* regex_nfa_to_dfa_helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regexset* states, // not yours to keep
	struct avl_tree_t* mappings)
{
	struct avl_node_t* search_result;
	ENTER;
	
	if ((search_result = avl_search(mappings, &states)))
	{
		struct regex_mapping* cached = search_result->item;
		
		EXIT;
		return cached->combined_state;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct regex* state = new_regex(arena);
		#else
		struct regex* state = new_regex();
		#endif
		
		#ifdef WITH_ARENAS
		struct regex_mapping* mapping = new_regex_mapping(arena, states, state);
		#else
		struct regex_mapping* mapping = new_regex_mapping(states, state);
		#endif
		
		avl_insert(mappings, mapping);
		
		// set this as accepting if any states in list are accepting:
		{
			// struct avl_node_t* node;
			
			bool is_accepting = false;
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->is_accepting) {
						is_accepting = true;
					}
				}
				runme;
			}));
			
			state->is_accepting = is_accepting;
			
			dpvb(state->is_accepting);
		}
		
		// create heap:
		#ifdef WITH_ARENAS
		struct heap* heap = new_heap(arena, compare_iterators);
		#else
		struct heap* heap = new_heap(compare_iterators);
		#endif
		
		// create default iterator list:
		struct {
			struct iterator** data;
			size_t n, cap;
		} defaults = {
			.data = NULL,
			.n = 0, .cap = 0,
		};
		
		// create iterators for each state:
		regexset_foreach(states, ({
			void runme(struct regex* ele) {
				#ifdef WITH_ARENAS
				struct iterator* iter = new_iterator(arena, ele);
				#else
				struct iterator* iter = new_iterator(ele);
				#endif
				
				bool needed = false;
				
				if (iter->moving < iter->end)
				{
					heap_push(heap, iter);
					needed = true;
				}
				
				if (iter->default_to)
				{
					if (defaults.n + 1 > defaults.cap)
					{
						defaults.cap = defaults.cap << 1 ?: 1;
						
						dpv(defaults.cap);
						
						#ifdef WITH_ARENAS
						defaults.data = arena_realloc(arena, defaults.data,
							sizeof(*defaults.data) * defaults.cap);
						#else
						defaults.data = realloc(defaults.data,
							sizeof(*defaults.data) * defaults.cap);
						#endif
					}
					
					defaults.data[defaults.n++] = iter;
					needed = true;
				}
				
				if (!needed)
				{
					#ifdef WITH_ARENAS
					free_iterator(arena, iter);
					#else
					free_iterator(iter);
					#endif
				}
			}
			runme;
		}));
		
		unsigned round = 0;
		
		while (is_heap_nonempty(heap))
		{
			unsigned min_value = heap->datai[0]->moving[0]->value;
			
			dpv(min_value);
			
			#ifdef WITH_ARENAS
			struct regexset* subregexset = new_regexset(arena);
			#else
			struct regexset* subregexset = new_regexset();
			#endif
			
			while (heap->n && heap->datai[0]->moving[0]->value == min_value)
			{
				struct iterator* iter = heap_pop(heap);
				
				regex_add_lamda_states(subregexset, (*iter->moving++)->to);
				
				iter->last_used = round;
				
				if (iter->moving < iter->end)
					heap_push(heap, iter);
				else if (!iter->default_to)
				{
					#ifdef WITH_ARENAS
					free_iterator(arena, iter);
					#else
					free_iterator(iter);
					#endif
				}
			}
			
			// for each iterator with defaults:
			for (size_t i = 0, n = defaults.n; i < n; i++)
				if (defaults.data[i]->last_used != round)
					regexset_add(subregexset, defaults.data[i]->default_to);
			
			// substate = myself(state-set);
			struct regex* substate = regex_nfa_to_dfa_helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* states: */ subregexset,
				/* mappings: */ mappings);
			
			// node.transitions[min] = substate;
			regex_add_transition(state, min_value, substate);
			
			free_regexset(subregexset);
			
			round++;
		}
		
		if (defaults.n)
		{
			// create regexset of all defaults
			#ifdef WITH_ARENAS
			struct regexset* subregexset = new_regexset(arena);
			#else
			struct regexset* subregexset = new_regexset();
			#endif
			
			for (size_t i = 0, n = defaults.n; i < n; i++)
				regex_add_lamda_states(subregexset, defaults.data[i]->default_to);
			
			// node.default = call myself
			struct regex* substate = regex_nfa_to_dfa_helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* states: */ subregexset,
				/* mappings: */ mappings);
			
			regex_set_default_transition(state, substate);
			
			free_regexset(subregexset);
		}
		
		// EOF transitions?
		{
			#ifdef WITH_ARENAS
			struct regexset* subregexset = new_regexset(arena);
			#else
			struct regexset* subregexset = new_regexset();
			#endif
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->EOF_transition_to) {
						regexset_add(subregexset, ele->EOF_transition_to);
					}
				}
				runme;
			}));
			
			if (regexset_is_nonempty(subregexset))
			{
				struct regex* substate = regex_nfa_to_dfa_helper(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* states: */ subregexset,
					/* mappings: */ mappings);
				
				regex_set_EOF_transition(state, substate);
			}
			
			free_regexset(subregexset);
		}
		
		// free default iterator list and it's elements
		for (size_t i = 0, n = defaults.n; i < n; i++)
		{
			#ifdef WITH_ARENAS
			free_iterator(arena, defaults.data[i]);
			#else
			free_iterator(defaults.data[i]);
			#endif
		}
		
		free_heap(heap);
		
		EXIT;
		return state;
	}
}













