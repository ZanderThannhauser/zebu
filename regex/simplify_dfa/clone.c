
#include <avl/avl.h>
#include <avl/new.h>
#include <avl/safe_insert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <regex/state/struct.h>
#include <regex/state/new.h>
#include <regex/state/add_transition.h>

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
	struct avl_tree_t* unique_nodes,
	struct regex* old)
{
	struct avl_node_t* node;
	struct mapping* mapping;
	ENTER;
	
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
		
		// for each transition:
		size_t i, n;
		for (i = 0, n = old->transitions.n; i < n; i++)
		{
			struct transition* const ele = old->transitions.data[i];
			
			struct regex* cloneme;
			{
				node = avl_search(unique_nodes, ele->to);
				assert(node);
				cloneme = node->item;
			}
			
			regex_add_transition(
				/* from: */ new,
				/* arena */ arena,
				/* value: */ ele->value,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* arena: */ arena,
					/* unique_nodes: */ unique_nodes,
					/* in: */ cloneme));
		}
		
		// for default transition:
		if (old->default_transition_to)
		{
			TODO;
		}
		
		EXIT;
		return new;
	}
}

struct regex* simplify_dfa_clone(
	struct avl_tree_t* unique_nodes,
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* mappings = new_avl_tree(compare_mappings, free);
	
	struct regex* new_start = clone_helper(
		mappings, arena, unique_nodes, original_start);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















