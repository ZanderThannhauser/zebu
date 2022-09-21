
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void ptrset_foreach(
	const struct ptrset* this,
	void (*runme)(void* ptr))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		runme(node->item);
	}
	
	EXIT;
}

