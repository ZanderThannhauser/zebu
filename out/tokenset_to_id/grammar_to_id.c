

#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "grammar_to_id.h"

unsigned grammar_to_id(
	struct tokenset_to_id* this,
	const char* grammar)
{
	unsigned retval;
	ENTER;
	
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(this->tree, &(struct tokenset_to_id_node){
		.is_tokenset = false,
		.grammar = grammar,
	});
	
	if (node)
	{
		struct tokenset_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct tokenset_to_id_node* new = smalloc(sizeof(*new));
		
		new->is_tokenset = false;
		new->grammar = grammar;
		new->id = retval = this->next++;
		
		safe_avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
	#endif
}
