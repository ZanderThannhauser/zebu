
#include <debug.h>

#include "struct.h"
#include "add_token_field.h"

void structinfo_add_token_field(
	struct structinfo* this,
	struct string* name)
{
	ENTER;
	
	struct structinfo_node* node = smalloc(sizeof(*node));
	
	node->name = inc_string(name);
	
	node->kind = sin_token;
	
	avl_insert(this->tree, node);
	
	EXIT;
}

