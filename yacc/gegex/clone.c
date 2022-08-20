
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/new.h>
#include <avl/safe_insert.h>
#include <avl/free_tree.h>

#include <memory/arena/strdup.h>

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_grammar_transition.h"
#include "state/add_lambda_transition.h"

#include "clone.h"

struct mapping
{
	struct gegex* old; // must be the first
	struct gegex* new;
};

static int compare(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

struct memory_arena;

static struct gegex* clone_helper(
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct gegex* old)
{
	struct avl_node_t* node;
	ENTER;
	
	if ((node = avl_search(mappings, &old)))
	{
		struct mapping* mapping = node->item;
		
		EXIT;
		return mapping->new;
	}
	else
	{
		struct gegex* new = new_gegex(arena);
		
		new->is_reduction_point = old->is_reduction_point;
		
		struct mapping* mapping = smalloc(sizeof(*mapping));
		
		mapping->old = old;
		mapping->new = new;
		
		safe_avl_insert(mappings, mapping);
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			dpv(ele->token);
			
			gegex_add_transition(
				/* from: */ new,
				/* arena */ arena,
				/* value: */ ele->token,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* in: */ ele->to));
		}
		
		for (i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const ele = old->grammar_transitions.data[i];
			
			char* grammar = arena_strdup(arena, ele->grammar);
			
			gegex_add_grammar_transition(
				/* from: */ new,
				/* arena */ arena,
				/* value: */ grammar,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* in: */ ele->to));
		}
		
		// for each lambda transition:
		for (i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			gegex_add_lambda_transition(
				/* from: */ new,
				/* arena */ arena,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* in: */ old->lambda_transitions.data[i]));
		}
		
		EXIT;
		return new;
	}
}

struct gegex* gegex_clone(
	struct gegex* in,
	struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare, free);
	
	struct gegex* retval = clone_helper(mappings, arena, in);
	
	avl_free_tree(mappings);
	
	EXIT;
	return retval;
}

struct gbundle gegex_clone_nfa(
	struct memory_arena* arena,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare, free);
	
	struct gegex* new_start = clone_helper(mappings, arena, start);
	struct gegex* new_end = clone_helper(mappings, arena, end);
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct gbundle) {new_start, new_end};
}






















