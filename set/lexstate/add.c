
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

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
		this->len++;
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

