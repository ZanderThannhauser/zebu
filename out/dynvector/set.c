
#include <memory/smalloc.h>

#include <debug.h>

#include <avl/safe_insert.h>

#include "struct.h"
#include "set.h"

void dynvector_set(
	struct dynvector* this,
	unsigned index,
	unsigned value)
{
	ENTER;
	
	if (index > this->length)
	{
		this->length = index;
	}
	
	dpv(index);
	dpv(value);
	
	struct dynvector_node* node = smalloc(sizeof(*node));
	
	node->i = index;
	node->v = value;
	
	safe_avl_insert(this->list, node);
	
	EXIT;
}

