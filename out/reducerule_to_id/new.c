
#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct reducerule_to_id_node *A = a, *B = b;
	
	if (A->popcount > B->popcount)
		return +1;
	else if (A->popcount < B->popcount)
		return -1;
	else if (A->reductioninfo > B->reductioninfo)
		return +1;
	else if (A->reductioninfo < B->reductioninfo)
		return -1;
	else
		return +0;
}

static void free_node(void* ptr)
{
	TODO;
}

struct reducerule_to_id* new_reducerule_to_id()
{
	struct reducerule_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->next = 1; // 0 indicates error
	
	return this;
}

