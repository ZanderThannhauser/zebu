
#include <debug.h>

#include <string/inc.h>

#include <memory/smalloc.h>

#include <avl/insert.h>
#include <avl/search.h>

#include "struct.h"
#include "string_to_id.h"

unsigned string_to_id(
	struct string_to_id* this,
	struct string* string)
{
	struct avl_node_t* node = avl_search(this->tree, &string);
	
	if (node)
	{
		struct string_to_id_node* old = node->item;
		return old->id;
	}
	else
	{
		struct string_to_id_node* new = smalloc(sizeof(*new));
		
		new->string = inc_string(string);
		new->id = this->next++;
		
		avl_insert(this->tree, new);
		
		return new->id;
	}
}

