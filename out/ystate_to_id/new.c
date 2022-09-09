
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	const struct ystate_to_id_node* A = a, *B = b;
	
	if (A->ystate > B->ystate)
		return +1;
	else if (A->ystate < B->ystate)
		return -1;
	else
		return 0;
}

struct ystate_to_id* new_ystate_to_id()
{
	ENTER;
	
	struct ystate_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, free);
	
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	EXIT;
	return this;
}
















