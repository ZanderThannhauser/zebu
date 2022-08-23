
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include "struct.h"
#include "add.h"

bool gegextree_add(struct gegextree* this, struct gegex* ele)
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

