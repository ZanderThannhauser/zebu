
#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include <memory/srealloc.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"

#include "add_lamda_states.h"
#include "helper.h"

#include "heap/struct.h"
#include "heap/new.h"
#include "heap/push.h"
#include "heap/pop.h"
#include "heap/free.h"

#include "iterator/struct.h"
#include "iterator/new.h"
#include "iterator/free.h"

#include "stateset/struct.h"
#include "stateset/insert.h"
#include "stateset/new.h"

#include "mapping/struct.h"
#include "mapping/new.h"

struct regex* nfa_to_dfa_helper(
	struct stateset* states,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	int error = 0;
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
			struct avl_node_t* node;
			
			bool is_accepting = false;
			
			for (node = states->tree.head; !is_accepting && node; node = node->next)
			{
				struct regex* ele = node->item;
				
				if (ele->is_accepting)
				{
					is_accepting = true;
				}
			}
			
			state->is_accepting = is_accepting;
			
			dpvb(state->is_accepting);
		}
		
		// create heap:
		struct heap* heap = new_heap();
		
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
			struct avl_node_t* node;
			
			for (node = states->tree.head; node; node = node->next)
			{
				struct regex* ele = node->item;
				
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
		}
		
		unsigned round = 0;
		
		while (heap->n)
		{
			unsigned min_value = heap->data[0]->moving[0]->value;
			
			dpv(min_value);
			
			struct stateset* substateset = new_stateset();
			
			while (heap->n && heap->data[0]->moving[0]->value == min_value)
			{
				struct iterator* iter = heap_pop(heap);
				
				stateset_insert(substateset, (*iter->moving++)->to);
				
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
			
			// add lambda states
			add_lamda_states(substateset);
			
			// substate = myself(state-set);
			struct regex* substate = nfa_to_dfa_helper(
				/* states: */ substateset,
				/* mappings: */ mappings,
				/* arena: */ arena);
			
			// node.transitions[min] = substate;
			regex_add_transition(state, arena, min_value, substate);
			
			round++;
		}
		
		if (defaults.n)
		{
			// create stateset of all defaults
			struct stateset* substateset = new_stateset();
			
			for (size_t i = 0, n = defaults.n; i < n; i++)
				stateset_insert(substateset, defaults.data[i]->default_to);
			
			// add lambdas
			add_lamda_states(substateset);
			
			// node.default = call myself
			struct regex* substate = nfa_to_dfa_helper(
				/* states: */ substateset,
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
		
		
