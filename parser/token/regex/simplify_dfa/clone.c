
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/safe_insert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"

#include "regex_ll/find.h"

#include "clone.h"

static struct mapping {
	struct regex* old; // must be the first
	struct regex* new;
}* new_mapping(struct regex* old, struct regex* new) {
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
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

struct memory_arena;

static struct regex* clone_helper(
	struct avl_tree_t* mappings,
	struct memory_arena* arena,
	struct regex_ll* unique_nodes,
	struct regex* old)
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
		struct regex* new = new_regex(arena);
		
		new->is_accepting = old->is_accepting;
		
		safe_avl_insert(mappings, new_mapping(old, new));
		
		// calculate default transition first,
		if (old->default_transition_to)
		{
			struct regex* cloneme = regex_ll_find(unique_nodes, old->default_transition_to);
			
			dpv(cloneme);
			
			regex_set_default_transition(
				/* from: */ new,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* unique_nodes: */ unique_nodes,
					/* in: */ cloneme));
		}
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			dpv(ele->value);
			dpv(ele->to);
			
			struct regex* cloneme = regex_ll_find(unique_nodes, ele->to);
			
			dpv(cloneme);
			
			struct regex* to = clone_helper(
				/* mappings: */ mappings,
				/* arena: */ arena,
				/* unique_nodes: */ unique_nodes,
				/* in: */ cloneme);
			
			// don't add the transition if the default already covers it
			if (to != new->default_transition_to)
				regex_add_transition(
					/* from: */ new,
					/* arena */ arena,
					/* value: */ ele->value,
					/* to: */ to);
		}
		
		EXIT;
		return new;
	}
}

struct regex* simplify_dfa_clone(
	struct regex_ll* unique_nodes,
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	dpv(original_start);
	
	struct avl_tree_t* mappings = new_avl_tree(compare_mappings, free);
	
	struct regex* cloneme = regex_ll_find(unique_nodes, original_start);
	
	dpv(cloneme);
	
	struct regex* new_start = clone_helper(
		mappings, arena, unique_nodes, cloneme);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















