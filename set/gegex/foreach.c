
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void gegexset_foreach(
	const struct gegexset* this,
	void (*runme)(struct gegex* this))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		runme(node->item);
	}
}

