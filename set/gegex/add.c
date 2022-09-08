
#include <debug.h>

#include "struct.h"
#include "add.h"

bool gegexset_add(struct gegexset* this, struct gegex* element)
{
	bool new;
	ENTER;
	
	errno = 0;
	
	struct avl_node_t* node = avl_insert(this->tree, element);
	
	if (node)
	{
		new = true;
		this->n++;
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

