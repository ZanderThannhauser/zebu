
#include "tree_t.h"
#include "foreach.h"

void avl_tree_foreach(
	struct avl_tree_t* this,
	void (*runme)(void*))
{
	for (struct avl_node_t* node = this->head; node; node = node->next)
		runme(node->item);
}

