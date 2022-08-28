
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <set/regex/struct.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
/*#include "../state/set_accepting.h"*/
/*#include "../state/get_accepting.h"*/
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"
#include "../state/foreach_transition.h"

#include "same_as_node/struct.h"

#include "clone.h"

static struct mapping {
	struct regex* old; // must be the first
	struct regex* new;
}* new_mapping(struct regex* old, struct regex* new)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->old = old, this->new = new;
	
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
	free(this);
	EXIT;
}

static struct regex* find(struct avl_tree_t* connections, struct regex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct regex_same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

static struct regex* clone_helper(
	struct avl_tree_t* mappings,
	struct avl_tree_t* connections,
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
		struct regex* new = new_regex();
		
		new->is_accepting = old->is_accepting;
		
		avl_insert(mappings, new_mapping(old, new));
		
		// calculate default transition first,
		if (old->default_transition_to)
		{
			struct regex* cloneme = find(connections, old->default_transition_to);
			
			dpv(cloneme);
			
			regex_set_default_transition(
				/* from: */ new,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ cloneme));
		}
		
		
		// for each transition:
		regex_foreach_transition(old, ({
			void runme(unsigned char value, struct regex* to)
			{
				struct regex* cloneme = find(connections, to);
				
				struct regex* cloned_to = clone_helper(
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ cloneme);
				
				// don't add the transition if the default already covers it
				if (cloned_to != new->default_transition_to)
				{
					regex_add_transition(
						/* from: */ new,
						/* value: */ value,
						/* to: */ cloned_to);
				}
			}
			runme;
		}));
		
		// EOF transitions?
		if (old->EOF_transition_to)
		{
			TODO;
			#if 0
			struct regex* cloneme = find(connections, to);
			
			dpv(cloneme);
			
			regex_set_EOF_transition(
				/* from: */ new,
				/* to */ clone_helper(
					/* mappings: */ mappings,
					/* connections: */ connections,
					/* in: */ cloneme));
			#endif
		}
		
		EXIT;
		return new;
	}
}

struct regex* regex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct regex* original_start)
{
	ENTER;
	
	dpv(original_start);
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct regex* cloneme = find(connections, original_start);
	
	dpv(cloneme);
	
	struct regex* new_start = clone_helper(mappings, connections, cloneme);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















