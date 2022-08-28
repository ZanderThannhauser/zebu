
#if 0
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
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

static struct mapping* new_mapping(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* a,
	struct regex* b,
	struct regex* new)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct mapping* this = arena_malloc(arena, sizeof(*this));
	#else
	struct mapping* this = malloc(sizeof(*this));
	#endif
	
	this->a = a;
	this->b = b;
	this->new = new;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
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
	ENTER;
	
	#ifdef WITH_ARENAS
	struct mapping* const A = a;
	arena_dealloc(A->arena, A);
	#else
	free(a);
	#endif
	
	EXIT;
}

static struct regex* helper(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* mappings,
	struct regex* A,
	struct regex* B)
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
		#ifdef WITH_ARENAS
		struct regex* state = new_regex(arena);
		#else
		struct regex* state = new_regex();
		#endif
		
		#ifdef WITH_ARENAS
		avl_insert(mappings, new_mapping(arena, A, B, state));
		#else
		avl_insert(mappings, new_mapping(A, B, state));
		#endif
		
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
					#ifdef WITH_ARENAS
					struct regex* substate = helper(arena, mappings, A_trans->to, B->default_transition_to);
					#else
					struct regex* substate = helper(mappings, A_trans->to, B->default_transition_to);
					#endif
					
					regex_add_transition(state, A_trans->value, substate);
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
				
				#ifdef WITH_ARENAS
				struct regex* substate = helper(arena, mappings, A_trans->to, B_trans->to);
				#else
				struct regex* substate = helper(mappings, A_trans->to, B_trans->to);
				#endif
				
				regex_add_transition(state, A_trans->value, substate);
				
				a.i++, b.i++;
			}
		}
		
		while (a.i < a.n && B->default_transition_to)
		{
			const struct transition* const A_trans = A->transitions.data[a.i++];
			
			struct regex* substate = helper(
				#ifdef WITH_ARENAS
				/* arena: */ arena,
				#endif
				/* mappings: */ mappings,
				/* A: */ A_trans->to,
				/* B: */ B->default_transition_to);
			
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
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct regex* A,
	struct regex* B)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	#else
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	#endif
	
	#ifdef WITH_ARENAS
	struct regex* start = helper(arena,  mappings, A, B);
	#else
	struct regex* start = helper(mappings, A, B);
	#endif
	
	#ifdef DOTOUT
	regex_dotout(start, __PRETTY_FUNCTION__);
	#endif
	
	avl_free_tree(mappings);
	
	EXIT;
	return start;
}












#endif
