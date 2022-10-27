
#include <assert.h>
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <misc/format_flags/inc.h>

#include "struct.h"
#include "node.h"
#include "add_scanf_array_field.h"

void structinfo_add_scanf_array_field(
	struct structinfo* this,
	struct format_flags* fflags,
	struct string* name)
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
		
		node->type = snt_scanf_array;
		
		node->scanf.fflags = inc_format_flags(fflags);
		
		node->refcount = 1;
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}
