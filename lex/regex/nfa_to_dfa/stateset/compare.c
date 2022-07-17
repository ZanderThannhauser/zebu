
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_statesets(struct stateset* A, struct stateset* B)
{
	struct avl_node_t* node_a = A->tree.head;
	struct avl_node_t* node_b = B->tree.head;
	
	while (node_a && node_b)
	{
		struct state* state_a = node_a->item;
		struct state* state_b = node_b->item;
		
		if (state_a > state_b)
			return 1;
		else if (state_a < state_b)
			return -1;
		
		node_a = node_a->next;
		node_b = node_b->next;
	}
	
	if (node_a)
		return 1;
	else if (node_b)
		return -1;
	else
		return 0;
}












