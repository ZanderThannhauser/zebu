

#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare_ystate_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct ystate_to_id_node* A = a, *B = b;
	
	if (A->ystate > B->ystate)
		cmp = +1;
	else if (A->ystate < B->ystate)
		cmp = -1;
	
	EXIT;
	return cmp;
}

static void free_ystate_to_id_node(void* ptr)
{
	ENTER;
	
	struct ystate_to_id_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct ystate_to_id* new_ystate_to_id()
{
	ENTER;
	
	TODO;
	#if 0
	struct ystate_to_id* this = smalloc(sizeof(*this));
	
	this->tree = new_avl_tree(compare_ystate_to_id_nodes, free_ystate_to_id_node);
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	EXIT;
	return this;
	#endif
}

