
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "get_head.h"

void* ptrset_get_head(const struct ptrset* this)
{
	assert(this->tree->head);
	
	return this->tree->head->item;
}

