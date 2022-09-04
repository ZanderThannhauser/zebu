
#include <debug.h>

#include "dependent_of_node/struct.h"
#include "dependent_of_node/new.h"

#include "pair/struct.h"
#include "pair/new.h"

#include "add_dep.h"

void lex_simplify_dfa_add_dep(
	struct avl_tree_t* dependent_of,
	struct lex_state* a_on, struct lex_state* b_on,
	struct lex_state* a_of, struct lex_state* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct lex_state* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct lex_pair){a_of, b_of});
	
	if (node)
	{
		struct lex_dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct lex_pair){a_on, b_on}))
		{
			struct lex_pair* dep = new_lex_pair(a_on, b_on);
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		struct lex_dependent_of_node* new = new_lex_dependent_of_node(a_of, b_of);
		
		struct lex_pair* dep = new_lex_pair(a_on, b_on);
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}






