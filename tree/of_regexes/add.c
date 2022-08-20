
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include "struct.h"
#include "add.h"

bool regextree_add(struct regextree* this, struct regex* ele)
{
	ENTER;
	
	errno = 0;
	
	bool new;
	struct avl_node_t* node = avl_insert(this->tree, ele);
	
	if (node)
	{
		new = true;
		this->n++;
	}
	else switch (errno)
	{
		case EEXIST:
			new = false;
			break;
		
		default:
			TODO;
	}
	
	EXIT;
	return new;
}

