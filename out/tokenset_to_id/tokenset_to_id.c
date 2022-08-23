

#include <debug.h>

#include <avl/search.h>

#include <arena/malloc.h>

#include <avl/insert.h>

#include "struct.h"
#include "tokenset_to_id.h"

unsigned tokenset_to_id(
	struct tokenset_to_id* this,
	const struct tokenset* tokenset)
{
	unsigned retval;
	ENTER;
	
	dpv(this->arena);
	
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
		struct tokenset_to_id_node* new = arena_malloc(this->arena, sizeof(*new));
		
		new->is_tokenset = true;
		new->tokenset = tokenset;
		new->id = retval = this->next++;
		
		avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}

