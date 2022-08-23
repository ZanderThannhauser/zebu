
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/alloc_tree.h>
#include <avl/insert.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"

#include "../dotout.h"

#include "intersect_dfas.h"

struct mapping
{
	struct regex* a, *b;
	struct regex* new;
	
	struct memory_arena* arena;
};

static struct mapping* new_mapping(
	struct memory_arena* arena,
	struct regex* a,
	struct regex* b,
	struct regex* new)
{
	ENTER;
	
	struct mapping* this = arena_malloc(arena, sizeof(*this));
	
	this->a = a;
	this->b = b;
	this->new = new;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

static int compare_mappings(
	const void* a,
	const void* b)
{
	const struct mapping *A = a, *B = b;
	
	if (A->a > B->a)
		return +1;
	if (A->a < B->a)
		return +1;
	if (A->b > B->b)
		return +1;
	if (A->b < B->b)
		return +1;
	
	return 0;
}

static void free_mapping(void* a)
{
	struct mapping* A = a;
	arena_dealloc(A->arena, A);
}

static struct regex* helper(
	struct regex* A,
	struct regex* B,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	struct regex* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(mappings, &(struct mapping) {A, B});
	
	if (node)
	{
		struct mapping* mapping = node->item;
		
		retval = mapping->new;
	}
	else
	{
		struct regex* state = new_regex(arena);
		
		avl_insert(mappings, new_mapping(arena, A, B, state));
		
		state->is_accepting = A->is_accepting && B->is_accepting;
		
		dpvb(state->is_accepting);
		
		struct {
			size_t i, n;
		} a = {0, A->transitions.n},
		  b = {0, B->transitions.n};
		
		dpv(a.n);
		dpv(b.n);
		
		while (a.i < a.n && b.i < b.n)
		{
			const struct transition* const A_trans = A->transitions.data[a.i];
			const struct transition* const B_trans = B->transitions.data[b.i];
			
			if (A_trans->value < B_trans->value)
			{
				TODO;
				#if 0
				dpv(A_trans->value);
				
				if (B->default_transition_to)
				{
					struct regex* substate = helper(A_trans->to, B->default_transition_to, mappings, arena);
					regex_add_transition(state, arena, A_trans->value, substate);
				}
				#endif
				
				a.i++;
			}
			else if (A_trans->value > B_trans->value)
			{
				dpv(B_trans->value);
				
				if (A->default_transition_to)
				{
					TODO;
				}
				
				b.i++;
			}
			else
			{
				TODO;
				#if 0
				dpv(A_trans->value);
				
				struct regex* substate = helper(A_trans->to, B_trans->to, mappings, arena);
				
				regex_add_transition(state, arena, A_trans->value, substate);
				
				a.i++, b.i++;
				#endif
			}
		}
		
		while (a.i < a.n && B->default_transition_to)
		{
			const struct transition* const A_trans = A->transitions.data[a.i++];
			
			struct regex* substate = helper(
				/* A: */ A_trans->to,
				/* B: */ B->default_transition_to,
				/* mappings: */ mappings,
				/* arena: */ arena);
			
			regex_add_transition(state, A_trans->value, substate);
		}
		
		while (A->default_transition_to && b.i < b.n)
		{
			// const struct transition* const B_trans = B->transitions.data[b.i++];
			TODO;
		}
		
		if (A->default_transition_to && B->default_transition_to)
		{
			TODO;
		}
		
		retval = state;
	}
	
	EXIT;
	return retval;
}

struct regex* regex_intersect_dfas(
	struct regex* A,
	struct regex* B,
	struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	
	struct regex* start = helper(A, B, mappings, arena);
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return start;
}













