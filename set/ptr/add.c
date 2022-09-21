
#include <debug.h>

#include "struct.h"
#include "add.h"

bool ptrset_add(
	struct ptrset* set,
	void* element)
{
	ENTER;
	
	bool new;
	struct avl_node_t* node = avl_insert(set->tree, element);
	
	if (node)
	{
		new = true;
	}
	else if (errno == EEXIST)
	{
		new = false;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return new;
}

