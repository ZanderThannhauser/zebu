
#include "search.h"
#include "delete_node.h"
#include "delete.h"

void *avl_delete(avl_tree_t *avltree, const void *item)
{
	return avl_delete_node(avltree, avl_search(avltree, item));
}

