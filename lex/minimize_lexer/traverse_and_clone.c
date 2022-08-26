
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <tree/of_lstates/struct.h>

#include <misc/phase_counters.h>

#include <yacc/state/struct.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"

#include "same_as_node/struct.h"
#include "traverse_and_clone.h"

static struct mapping {
	struct lex_state* old; // must be the first
	struct lex_state* new;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
}* new_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* old, struct lex_state* new)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct mapping* this = arena_malloc(arena, sizeof(*this));
	#else
	struct mapping* this = malloc(sizeof(*this));
	#endif
	
	this->old = old, this->new = new;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static void free_mapping(void* ptr)
{
	struct mapping* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

static struct lex_state* find(struct avl_tree_t* connections, struct lex_state* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct lex_same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

static struct lex_state* clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* mappings,
	struct avl_tree_t* connections,
	struct lex_state* cloneme)
{
	struct avl_node_t* node;
	struct mapping* mapping;
	ENTER;
	
	dpv(cloneme);
	
	if ((node = avl_search(mappings, &cloneme)))
	{
		EXIT;
		return (mapping = node->item)->new;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct lex_state* new = new_lex_state(arena);
		#else
		struct lex_state* new = new_lex_state();
		#endif
		
		new->accepting = cloneme->accepting;
		
		#ifdef WITH_ARENAS
		avl_insert(mappings, new_mapping(arena, cloneme, new));
		#else
		avl_insert(mappings, new_mapping(cloneme, new));
		#endif
		
		// calculate default transition first,
		if (cloneme->default_transition_to)
		{
			struct lex_state* subcloneme = find(connections, cloneme->default_transition_to);
			
			dpv(subcloneme);
			
			lex_state_set_default_transition(
				/* from: */ new,
				/* to */ clone(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ subcloneme));
		}
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = cloneme->transitions.n; i < n; i++)
		{
			struct ltransition* const ele = cloneme->transitions.data[i];
			
			struct lex_state* cloneme = find(connections, ele->to);
			
			struct lex_state* to = clone(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* mappings: */ mappings,
				/* connections: */ connections,
				/* in: */ cloneme);
			
			// don't add the transition if the default already covers it
			if (to != new->default_transition_to)
			{
				lex_state_add_transition(
					/* from: */ new,
					/* value: */ ele->value,
					/* to: */ to);
			}
		}
		
		// EOF transitions?
		if (cloneme->EOF_transition_to)
		{
			struct lex_state* subcloneme = find(connections, cloneme->EOF_transition_to);
			
			dpv(cloneme);
			
			lex_state_set_EOF_transition(
				/* from: */ new,
				/* to */ clone(
					#ifdef WITH_ARENAS
					/* arena: */ arena,
					#endif
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ subcloneme));
		}
		
		EXIT;
		return new;
	}
}

static void traverse(
	struct avl_tree_t* mappings,
	struct avl_tree_t* connections,
	struct yacc_state* state)
{
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		state->phase = yacc_phase_counter;
		
		state->tokenizer_start = clone(mappings, connections, find(connections, state->tokenizer_start));
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			traverse(mappings, connections, state->transitions.data[i]->to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			traverse(mappings, connections, state->grammar_transitions.data[i]->to);
		}
	}
	
	EXIT;
}

void lex_minimize_traverse_and_clone(
	struct avl_tree_t* connections,
	struct yacc_state* start)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	#endif
	
	yacc_phase_counter++;
	
	traverse(mappings, connections, start);
	
	avl_free_tree(mappings);
	
	EXIT;
}












































