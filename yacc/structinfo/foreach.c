
#include <debug.h>

#include <avl/tree_t.h>

#include "node.h"
#include "struct.h"
#include "foreach.h"

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(struct structinfo_node* ele))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		runme(ele);
	}
	
	EXIT;
}

