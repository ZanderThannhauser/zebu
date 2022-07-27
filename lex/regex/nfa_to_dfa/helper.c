
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include <memory/srealloc.h>

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

#include "iterator/struct.h"
#include "iterator/new.h"
#include "iterator/compare.h"
#include "iterator/free.h"

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"

#include "add_lamda_states.h"
#include "helper.h"

/*#include "regexset/struct.h"*/
/*#include "regexset/insert.h"*/
/*#include "regexset/new.h"*/

#include "mapping/struct.h"
#include "mapping/new.h"

struct regex* nfa_to_dfa_helper(
	struct regexset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	struct avl_node_t* search_result;
	ENTER;
	
	if ((search_result = avl_search(mappings, &states)))
	{
		struct mapping* cached = search_result->item;
		
		EXIT;
		return cached->combined_state;
	}
	else
	{
		struct regex* state = new_regex(arena);
		
		struct mapping* mapping = new_mapping(states, state);
		
		safe_avl_insert(mappings, mapping);
		
		// set this as accepting if any states in list are accepting:
		{
			// struct avl_node_t* node;
			
			bool is_accepting = false;
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					if (ele->is_accepting)
						is_accepting = true;
				}
				runme;
			}));
			
			state->is_accepting = is_accepting;
			
			dpvb(state->is_accepting);
		}
		
		// create heap:
		struct heap* heap = new_heap(compare_iterators);
		
		// create default iterator list:
		struct {
			struct iterator** data;
			size_t n, cap;
		} defaults = {
			.data = NULL,
			.n = 0, .cap = 0,
		};
		
		// create iterators for each state:
		{
			// struct avl_node_t* node;
			
			regexset_foreach(states, ({
				void runme(struct regex* ele) {
					struct iterator* iter = new_iterator(ele);
					
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
							defaults.data = srealloc(defaults.data,
								sizeof(*defaults.data) * defaults.cap);
						}
						
						defaults.data[defaults.n++] = iter;
						needed = true;
					}
					
					if (!needed)
					{
						free_iterator(iter);
					}
				}
				runme;
			}));
			
		}
		
		unsigned round = 0;
		
		while (is_heap_nonempty(heap))
		{
			unsigned min_value = heap->datai[0]->moving[0]->value;
			
			dpv(min_value);
			
			struct regexset* subregexset = new_regexset();
			
			while (heap->n && heap->datai[0]->moving[0]->value == min_value)
			{
				struct iterator* iter = heap_pop(heap);
				
				regex_add_lamda_states(subregexset, (*iter->moving++)->to);
				
				iter->last_used = round;
				
				if (iter->moving < iter->end)
					heap_push(heap, iter);
				else if (!iter->default_to)
					free_iterator(iter);
			}
			
			// for each iterator with defaults:
			for (size_t i = 0, n = defaults.n; i < n; i++)
			{
				if (defaults.data[i]->last_used != round)
				{
					// state-set.add(iter.default);
					TODO;
				}
			}
			
			// substate = myself(state-set);
			struct regex* substate = nfa_to_dfa_helper(
				/* states: */ subregexset,
				/* mappings: */ mappings,
				/* arena: */ arena);
			
			// node.transitions[min] = substate;
			regex_add_transition(state, arena, min_value, substate);
			
			round++;
		}
		
		if (defaults.n)
		{
			// create regexset of all defaults
			struct regexset* subregexset = new_regexset();
			
			for (size_t i = 0, n = defaults.n; i < n; i++)
				regex_add_lamda_states(subregexset, defaults.data[i]->default_to);
			
			// node.default = call myself
			struct regex* substate = nfa_to_dfa_helper(
				/* states: */ subregexset,
				/* mappings: */ mappings,
				/* arena: */ arena);
			
			// node.transitions[min] = substate;
			regex_set_default_transition(state, substate);
		}
		
		// free default iterator list and it's elements
		for (size_t i = 0, n = defaults.n; i < n; i++)
			free_iterator(defaults.data[i]);
		
		free_heap(heap);
		
		EXIT;
		return state;
	}
	
}



		#if 0
		// create transition iterators for each:
		struct {
			struct transition ** moving, **end;
			struct regex_state* default_to;
		} *iterators = NULL , *iterator;
		
		size_t n = 0, cap = 0, m = 0;
		
		for (node = states->head; !error && node; node = node->next)
		{
			ele = node->item;
			
			if (ele->transitions.n)
			{
				if (n + 1 >= cap)
				{
					cap = cap << 1 ?: 1;
					
					error = srealloc((void**) &iterators, cap * sizeof(*iterators));
				}
				
				if (!error)
				{
					iterators[n++] = (typeof(*iterators)) {
						.moving = ele->transitions.data,
						.end = ele->transitions.data + ele->transitions.n,
						.default_to = ele->default_transition_to,
					};
				}
			}
		}
		
		size_t i, m;
		unsigned lowest;
		struct regex_state* state;
		struct transition* transition;
		struct avl_tree_t* transition_statelist;
		
		// until there are no more transitions:
		for (m = n; !error && m > 0; )
		{
			// get lowest transition value
			for (lowest = -1, i = 0; i < n; i++)
			{
				iterator = &iterators[i];
				
				if (iterator->moving < iterator->end)
				{
					transition = *iterator->moving;
					
					dpv(transition->value);
					
					if (transition->value < lowest)
						lowest = transition->value;
				}
			}
			
			// make a list of new locations:
			transition_statelist = NULL;
			
			error = new_avl_tree(&transition_statelist, compare_states, NULL);
			
			// make a list of all the new places we would be:
			for (i = 0; !error && i < n; i++)
			{
				iterator = &iterators[i];
				
				if (iterator->moving < iterator->end && iterator->moving[0]->value == lowest)
				{
					TODO;
					#if 0
					error = statelist_insert(transition_statelist, iterator->moving[0]->to);
					
					if (++iterator->moving == iterator->end)
						N--;
					#endif
				}
				else if ((state = iterator->default_to))
				{
					TODO;
					#if 0
					error = statelist_insert(transition_statelist, state);
					#endif
				}
			}
			
			CHECK;
			
			// add lambda transitions to list
			TODO;
			
			// call yourself on list
			TODO;
			
			// create transition bewteen this state and substate
			TODO;
		}
		
		// call convert on the list of all default-transitions, set result to
		// new state's default transition
		TODO;
		
		free(iterators);
		
		free_mapping(mapping);
		#endif
		
		
