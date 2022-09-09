
#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>

#include <avl/insert.h>

#include <memory/smalloc.h>

#include <set/unsigned/inc.h>

#include "struct.h"
#include "unsignedset_to_id.h"

unsigned unsignedset_to_id(
	struct unsignedset_to_id* this,
	struct unsignedset* unsignedset)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct unsignedset_to_id_node){
		.unsignedset = unsignedset
	});
	
	if (node)
	{
		struct unsignedset_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		struct unsignedset_to_id_node* new = smalloc(sizeof(*new));
		
		new->unsignedset = inc_unsignedset(unsignedset);
		
		new->id = retval = this->next++;
		
		avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}








