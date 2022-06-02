
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/insert.h>

#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include "state/struct.h"
#include "state/new.h"

#include "dotout.h"
#include "nfa_to_dfa.h"

int compare_states(const void* a, const void* b)
{
	TODO;
}

struct stateset
{
	struct avl_tree_t tree;
	size_t n;
};

int new_stateset(struct stateset** out)
{
	int error = 0;
	ENTER;
	
	struct stateset* this;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		avl_init_tree(&this->tree, compare_states, NULL);
		this->n = 0;
		
		*out = this;
	}
	
	EXIT;
	return error;
}

bool stateset_contains(struct stateset* this, struct regex_state* element)
{
	TODO;
}

int stateset_insert(struct stateset* this, struct regex_state* element)
{
	int error = 0;
	ENTER;
	
	if (avl_insert(&this->tree, element))
	{
		this->n++;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return error;
}

void free_stateset(struct stateset* this)
{
	TODO;
}

static int add_lamda_states(struct stateset* stateset)
{
	int error = 0;
	size_t i, n;
	ENTER;
	
#if 0
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
/*				if ()*/
				{
					TODO;
					changed = false;
				}
				
				TODO;
			}
		}
	}
#endif
	
	EXIT;
	return error;
}

struct iterator
{
	struct regex_state* state;
	size_t i, last_used_by;
};

int new_iterator(struct iterator** out, struct regex_state* state)
{
	TODO;
}

void heap_push(struct iterator** data, struct iterator* element)
{
	TODO;
}

struct iterator* heap_pop(struct iterator** data)
{
	TODO;
}

struct mapping
{
	struct stateset* original_states; // must be the first
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
	struct stateset* states)
{
	int error = 0;
	ENTER;
	
	if (avl_search(mappings, &states))
	{
		TODO;
	}
	else
	{
		TODO;
		#if 0
		struct regex_state* new;
		struct mapping* mapping = NULL;
		
		error = 0
			?: new_regex_state(&new, arena)
			?: smalloc((void**) &mapping, sizeof(*mapping));
		
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
		
		struct avl_node_t* node;
		struct regex_state* ele;
		
		// set this as accepting if any states in list are accepting:
		if (!error)
		{
			bool is_accepting = false;
			
			for (node = states->head; !is_accepting && node; node = node->next)
				if ((ele = node->item)->is_accepting)
					is_accepting = true;
			
			new->is_accepting = is_accepting;
			
			dpvb(new->is_accepting);
		}
		
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
	struct stateset* start = NULL;
	struct regex_state* new_start;
	ENTER;
	
	error = 0
		?: new_avl_tree(&mappings, compare_mappings, free_mapping)
		?: new_stateset(&start)
		?: stateset_insert(start, in)
		?: add_lamda_states(start)
		?: nfa_to_dfa(&new_start, arena, mappings, start);
	
	TODO;
	#if 0
	if (!error)
	{
		#ifdef DEBUGGING
		regex_dotout(new_start);
		#endif
		
		CHECK;
		
		*out = new_start;
	}
	
	#endif
	
	CHECK;
	
	avl_free_tree(mappings);
	
	EXIT;
	return error;
}













