

#include <debug.h>

#include "struct.h"
#include "set.h"

void dynvector_set(
	struct dynvector* this,
	unsigned index,
	unsigned value)
{
	ENTER;
	
	TODO;
	#if 0
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
	#endif
}

