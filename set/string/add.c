
#include <debug.h>

#include "struct.h"
#include "add.h"

void stringset_add(
	struct stringset* this,
	char* string)
{
	ENTER;
	
	struct avl_node_t* node = avl_insert(this->tree, string);
	
	if (!node)
	{
		TODO;
		free(string);
	}
	
	EXIT;
}


