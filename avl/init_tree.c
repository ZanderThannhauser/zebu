
#include <stddef.h>

#include "init_tree.h"

avl_tree_t *avl_init_tree(
	avl_tree_t *rc,
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	if (rc)
	{
		rc->head = NULL;
		rc->tail = NULL;
		rc->top = NULL;
		
		rc->cmp = cmp;
		
		rc->freeitem = freeitem;
	}
	return rc;
}

