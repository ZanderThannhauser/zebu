
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include <string/compare.h>
#include <string/free.h>

#include <yacc/reductioninfo/free.h>
#include <yacc/structinfo/free.h>

#include "struct.h"
#include "new.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct reducerule_to_id_node *A = a, *B = b;
	
	int cmp = compare_strings(A->reduce_as, B->reduce_as);
	
	if (cmp)
		return cmp;
	else if (A->reductioninfo > B->reductioninfo)
		return +1;
	else if (A->reductioninfo < B->reductioninfo)
		return -1;
	else
		return +0;
}

static void free_node(void* ptr)
{
	struct reducerule_to_id_node* node = ptr;
	free_string(node->reduce_as);
	free_string(node->grammar);
	free_reductioninfo(node->reductioninfo);
	free_structinfo(node->structinfo);
	free(node);
}

struct reducerule_to_id* new_reducerule_to_id()
{
	struct reducerule_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->next = 1; // 0 indicates error
	
	return this;
}

