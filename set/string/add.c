
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <string/inc.h>

#include "struct.h"
#include "add.h"

void stringset_add(
	struct stringset* this,
	struct string* string)
{
	ENTER;
	
	struct avl_node_t* node = avl_insert(this->tree, string);
	
	if (node)
	{
		inc_string(string);
		this->n++;
	}
	else
	{
		TODO;
	}
	
	EXIT;
}


