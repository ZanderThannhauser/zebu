
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <string/inc.h>

#include "node.h"
#include "struct.h"
#include "add_user_defined_field.h"

void structinfo_add_user_defined_field(
	struct structinfo* this,
	struct string* type,
	struct string* name,
	struct string* destructor)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		// check that it's not already in there, or that it's not the wrong type
		TODO;
	}
	else
	{
		struct structinfo_node* node = smalloc(sizeof(*node));
		
		node->name = inc_string(name);
		
		node->type = snt_user_defined;
		
		node->user_defined.type = inc_string(type);
		
		node->user_defined.destructor = inc_string(destructor);
		
		node->refcount = 1;
		
		avl_insert(this->tree, node);
	}
	
	
	EXIT;
}
