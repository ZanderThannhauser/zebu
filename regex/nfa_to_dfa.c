
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/insert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "state/struct.h"
#include "state/new.h"

#include "dotout.h"
#include "nfa_to_dfa.h"

int compare_states(const void* a, const void* b)
{
	TODO;
}

static int add_lamda_states(struct avl_tree_t* stateset)
{
	int error = 0;
	size_t i, n;
	ENTER;
	
	bool changed = true;
	struct avl_node_t* node;
	struct regex_state* state;
	
	while (!error && changed)
	{
		changed = false;
		
		for (node = stateset->head; !error && node; node = node->next)
		{
			state = node->item;
			
			for (i = 0, n = state->lambda_transitions.n; !error && i < n; i++)
			{
				TODO;
			}
		}
	}
	
	EXIT;
	return error;
}

struct mapping
{
	struct avl_tree_t* original_states; // must be the first
	struct regex_state* combined_state;
};

static int compare_mappings(const void* a, const void* b)
{
	TODO;
}

static void free_mapping(void* a)
{
	TODO;
}

static int nfa_to_dfa(
	struct regex_state** out,
	struct memory_arena* arena,
	struct avl_tree_t* mappings,
	struct avl_tree_t* states)
{
	int error = 0;
	ENTER;
	
	if (avl_search(mappings, &states))
	{
		TODO;
	}
	else
	{
		struct regex_state* new;
		
		error = new_regex_state(&new, arena);
		
		// create mapping:
		struct mapping* mapping;
		
		error = smalloc((void**) &mapping, sizeof(*mapping));
		
		if (!error)
		{
			mapping->original_states = states;
			mapping->combined_state = new;
		}
		
		// insert mapping:
		if (!error && !avl_insert(mappings, mapping))
		{
			fprintf(stderr, "%s: malloc(): %m\n", argv0),
			error = e_out_of_memory;
		}
		
		// set this as accepting if any states in list are accepting:
		TODO;
		
		// create transition iterators for each:
		TODO;
		
		// until there are no more transitions:
			// get lowest transition value
			TODO;
			// make a list of new locations
			TODO;
			// add lambda transitions to list
			TODO;
			// call yourself on list
			TODO;
			// create transition bewteen this state and substate
			TODO;
		
		// call convert on the list of all default-transitions, set result to
		// new state's default transition
		TODO;
	}
	
	TODO;
	
	EXIT;
	return error;
}

int regex_nfa_to_dfa(
	struct regex_state** out,
	struct memory_arena* arena,
	struct regex_state*  in)
{
	int error = 0;
	struct avl_tree_t* mappings = NULL;
	struct avl_tree_t* start_stateset = NULL;
	struct regex_state* new_start;
	ENTER;
	
	error = 0
		?: new_avl_tree(&mappings, compare_mappings, free_mapping)
		?: new_avl_tree(&start_stateset, compare_states, NULL)
		?: avl_tree_insert(start_stateset, in)
		?: add_lamda_states(start_stateset)
		?: nfa_to_dfa(&new_start, arena, mappings, start_stateset);
	
	if (!error)
	{
		#ifdef DEBUGGING
		regex_dotout(new_start);
		#endif
		
		CHECK;
		
		*out = new_start;
	}
	
	CHECK;
	
	avl_free_tree(mappings);
	
	EXIT;
	return error;
}













