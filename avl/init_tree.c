
#include <stddef.h>

#include <debug.h>

#include "init_tree.h"

avl_tree_t *avl_init_tree(
	avl_tree_t *rc,
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	ENTER;
	
	if (rc)
	{
		#ifdef WITH_ARENAS
		rc->arena = arena;
		#endif
		
		rc->head = NULL;
		rc->tail = NULL;
		rc->top = NULL;
		
		rc->cmp = cmp;
		
		rc->freeitem = freeitem;
	}
	
	EXIT;
	return rc;
}

