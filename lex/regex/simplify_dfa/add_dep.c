
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "dependent_of_node/struct.h"
#include "dependent_of_node/new.h"

#include "pair/struct.h"
#include "pair/new.h"

#include "add_dep.h"

void simplify_dfa_add_dep(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* dependent_of,
	struct regex* a_on, struct regex* b_on,
	struct regex* a_of, struct regex* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct regex* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct pair){a_of, b_of});
	
	if (node)
	{
		struct dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct pair){a_on, b_on}))
		{
			#ifdef WITH_ARENAS
			struct pair* dep = new_pair(arena, a_on, b_on);
			#else
			struct pair* dep = new_pair(a_on, b_on);
			#endif
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		#ifdef WITH_ARENAS
		struct dependent_of_node* new = new_dependent_of_node(arena, a_of, b_of);
		#else
		struct dependent_of_node* new = new_dependent_of_node(a_of, b_of);
		#endif
		
		#ifdef WITH_ARENAS
		struct pair* dep = new_pair(arena, a_on, b_on);
		#else
		struct pair* dep = new_pair(a_on, b_on);
		#endif
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}







