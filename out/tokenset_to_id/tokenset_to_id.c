
#include <memory/smalloc.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include "struct.h"
#include "tokenset_to_id.h"

unsigned tokenset_to_id(
	struct tokenset_to_id* this,
	const struct tokenset* tokenset)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct tokenset_to_id_node){
		.is_tokenset = true,
		.tokenset = tokenset
	});
	
	if (node)
	{
		struct tokenset_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct tokenset_to_id_node* new = smalloc(sizeof(*new));
		
		new->is_tokenset = true;
		new->tokenset = tokenset;
		new->id = retval = this->next++;
		
		safe_avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}

