
#include <debug.h>

#include "struct.h"
#include "add.h"

bool lexstateset_add(
	struct lexstateset* this,
	struct lex_state* ele)
{
	errno = 0;
	
	struct avl_node_t* node = avl_insert(this->tree, ele);
	
	if (node)
	{
		return true;
	}
	else if (errno == EEXIST)
	{
		return false;
	}
	else
	{
		TODO;
	}
}

