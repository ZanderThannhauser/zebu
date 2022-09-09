
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "add_grammar_scalar_field.h"

void structinfo_add_grammar_scalar_field(
	struct structinfo* this,
	struct string* name,
	struct string* grammar)
{
	ENTER;
	
	assert(grammar);
	
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
		
		node->kind = sin_grammar_scalar;
		
		node->grammar = inc_string(grammar);
		
		node->refcount = 1;
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}

