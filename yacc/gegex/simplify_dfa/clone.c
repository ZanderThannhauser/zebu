
#include <assert.h>

#include <debug.h>

#include <stdlib.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <debug.h>

#include <macros/lambda.h>

#include <set/of_gegexes/first.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../dotout.h"
#include "../state/add_transition.h"
#include "../state/add_grammar_transition.h"

#include "are_equal.h"
#include "clone.h"

static struct gegex_mapping {
	struct gegex* old; // must be the first
	struct gegex* new;
}* new_gegex_mapping(struct gegex* old, struct gegex* new)
{
	TODO;
	#if 0
	struct gegex_mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
	return this;
	#endif
}

static int compare_gegex_mappings(const void* a, const void* b)
{
	const struct gegex_mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static bool are_equal(struct gegex* unique, va_list* va)
{
	struct gegex* state = va_arg(*va, struct gegex*);
	struct avl_tree_t* cache = va_arg(*va, struct avl_tree_t*);
	return gegex_are_equal(cache, state, unique);
}

static struct gegex* clone_helper(
	struct avl_tree_t* cache,
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct gegexset* unique,
	struct gegex* old)
{
	struct avl_node_t* node;
	struct gegex_mapping* mapping;
	ENTER;
	
	TODO;
	#if 0
	dpv(old);
	
	if ((node = avl_search(mappings, &old)))
	{
		EXIT;
		return (mapping = node->item)->new;
	}
	else
	{
		struct gegex* new = new_gegex(arena);
		
		new->is_reduction_point = old->is_reduction_point;
		
		safe_avl_insert(mappings, new_gegex_mapping(old, new));
		
		// for each transition:
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			struct gegex* cloneme = gegexset_first(unique, are_equal, ele->to, cache);
			
			dpv(cloneme);
			
			struct gegex* to = clone_helper(cache, mappings, arena, unique, cloneme);
			
			gegex_add_transition(new, arena, ele->token, to);
		}
		
		for (unsigned i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const ele = old->grammar_transitions.data[i];
			
			struct gegex* cloneme = gegexset_first(unique, are_equal, ele->to, cache);
			
			dpv(cloneme);
			
			struct gegex* to = clone_helper(cache, mappings, arena, unique, cloneme);
			
			gegex_add_grammar_transition(new, arena, ele->grammar, to);
		}
		
		assert(!old->lambda_transitions.n);
		
		EXIT;
		return new;
	}
	#endif
}

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* cache,
	struct gegexset* unique,
	struct gegex* start,
	struct memory_arena* arena)
{
	ENTER;
	
	TODO;
	#if 0
	dpv(start);
	
	struct avl_tree_t* mappings = new_avl_tree(compare_gegex_mappings, free);
	
	struct gegex* cloneme = gegexset_first(unique, are_equal, start, cache);
	
	dpv(cloneme);
	
	struct gegex* new_start = clone_helper(
		cache, mappings, arena, unique, cloneme);
	
	avl_free_tree(mappings);
	
	#ifdef DEBUGGING
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return new_start;
	#endif
}


















