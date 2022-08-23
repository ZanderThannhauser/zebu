
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <tree/of_gegexes/struct.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/add_grammar_transition.h"

#include "same_as_node/struct.h"

#include "clone.h"

static struct mapping {
	struct gegex* old; // must be the first
	struct gegex* new;
	
	struct memory_arena* arena;
}* new_mapping(
	struct memory_arena* arena,
	struct gegex* old, struct gegex* new)
{
	ENTER;
	
	struct mapping* this = arena_malloc(arena, sizeof(*this));
	
	this->old = old, this->new = new;
	
	this->arena = arena;
	
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
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

static struct gegex* find(struct avl_tree_t* connections, struct gegex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct gegex_same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

static struct gegex* clone_helper(
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct avl_tree_t* connections,
	struct gegex* old)
{
	struct avl_node_t* node;
	struct mapping* mapping;
	ENTER;
	
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
		
		avl_insert(mappings, new_mapping(arena, old, new));
		
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			gegex_add_transition(
				/* from: */ new,
				/* value: */ ele->token,
				/* to: */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* connections: */ connections,
					/* in: */ find(connections, ele->to)));
		}
		
		for (i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* const ele = old->grammar_transitions.data[i];
			
			gegex_add_grammar_transition(
				/* from: */ new,
				/* value: */ ele->grammar,
				/* to: */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* connections: */ connections,
					/* in: */ find(connections, ele->to)));
		}
		
		EXIT;
		return new;
	}
}

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct gegex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	dpv(original_start);
	
	struct avl_tree_t* mappings = avl_alloc_tree(arena, compare_mappings, free_mapping);
	
	struct gegex* cloneme = find(connections, original_start);
	
	dpv(cloneme);
	
	struct gegex* new_start = clone_helper(
		mappings, arena, connections, cloneme);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















