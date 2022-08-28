
#if 0
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "dependent_of_node/struct.h"
#include "dependent_of_node/new.h"

#include "pair/struct.h"
#include "pair/new.h"

#include "add_dep.h"

void gegex_simplify_dfa_add_dep(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct avl_tree_t* dependent_of,
	struct gegex* a_on, struct gegex* b_on,
	struct gegex* a_of, struct gegex* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct gegex* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct gegex_pair){a_of, b_of});
	
	if (node)
	{
		struct gegex_dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct gegex_pair){a_on, b_on}))
		{
			#ifdef WITH_ARENAS
			struct gegex_pair* dep = new_gegex_pair(arena, a_on, b_on);
			#else
			struct gegex_pair* dep = new_gegex_pair(a_on, b_on);
			#endif
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		#ifdef WITH_ARENAS
		struct gegex_dependent_of_node* new = new_gegex_dependent_of_node(arena, a_of, b_of);
		#else
		struct gegex_dependent_of_node* new = new_gegex_dependent_of_node(a_of, b_of);
		#endif
		
		#ifdef WITH_ARENAS
		struct gegex_pair* dep = new_gegex_pair(arena, a_on, b_on);
		#else
		struct gegex_pair* dep = new_gegex_pair(a_on, b_on);
		#endif
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}






#endif
