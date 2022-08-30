
#include <debug.h>

#include "struct.h"
#include "add.h"

void unsignedcharset_add(
	struct unsignedcharset* this,
	unsigned char element)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &element);
	
	if (node)
	{
		TODO;
	}
	else
	{
		unsigned char* dup = smalloc(sizeof(*dup));
		
		*dup = element;
		
		avl_insert(this->tree, dup);
		
		this->n++;
	}
	
	EXIT;
}

