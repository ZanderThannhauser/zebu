
#include <debug.h>

#include "struct.h"
#include "add.h"

bool yaccstateset_add(
	struct yaccstateset* this,
	struct yacc_state* ele)
{
	errno = 0;
	
	struct avl_node_t* node = avl_insert(this->tree, ele);
	
	if (node)
		return true;
	else if (errno == EEXIST)
		return false;
	else
	{
		TODO;
	}
}

