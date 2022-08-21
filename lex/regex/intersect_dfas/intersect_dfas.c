
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/free_tree.h>

/*#include <memory/smalloc.h>*/

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"

#include "../dotout.h"

#include "intersect_dfas.h"

struct mapping
{
	struct regex* a, *b;
	struct regex* new;
};

static struct mapping* new_mapping(
	struct regex* a,
	struct regex* b,
	struct regex* new)
{
	ENTER;
	
	TODO;
	#if 0
	struct mapping* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	this->new = new;
	
	EXIT;
	return this;
	#endif
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

static void free_mapping(
	void* a)
{
	struct mapping* A = a;
	free(A);
}

static struct regex* helper(
	struct regex* A,
	struct regex* B,
	struct avl_tree_t* mappings,
	struct memory_arena* arena)
{
	struct regex* retval;
	ENTER;
	
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(mappings, &(struct mapping) {A, B});
	
	if (node)
	{
		struct mapping* mapping = node->item;
		
		retval = mapping->new;
	}
	else
	{
		struct regex* state = new_regex(arena);
		
		safe_avl_insert(mappings, new_mapping(A, B, state));
		
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
				dpv(A_trans->value);
				
				if (B->default_transition_to)
				{
					struct regex* substate = helper(A_trans->to, B->default_transition_to, mappings, arena);
					regex_add_transition(state, arena, A_trans->value, substate);
				}
				
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
				dpv(A_trans->value);
				
				struct regex* substate = helper(A_trans->to, B_trans->to, mappings, arena);
				
				regex_add_transition(state, arena, A_trans->value, substate);
				
				a.i++, b.i++;
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
			
			regex_add_transition(state, arena, A_trans->value, substate);
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
	#endif
}

struct regex* regex_intersect_dfas(
	struct regex* A,
	struct regex* B,
	struct memory_arena* arena)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = new_avl_tree(compare_mappings, free_mapping);
	
	struct regex* start = helper(A, B, mappings, arena);
	
	#ifdef DEBUGGING
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return start;
	#endif
}













