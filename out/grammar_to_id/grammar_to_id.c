
#if 0
#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include "struct.h"
#include "grammar_to_id.h"

unsigned grammar_to_id(
	struct grammar_to_id* this,
	const char* grammar)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &grammar);
	
	if (node)
	{
		struct grammar_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct grammar_to_id_node* new = smalloc(sizeof(*new));
		
		new->grammar = grammar;
		new->id = retval = this->next++;
		
		safe_avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}

#endif
