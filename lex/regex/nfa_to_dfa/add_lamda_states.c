
#include <debug.h>

#include "../state/struct.h"

#ifdef DEBUGGING
#include "stateset/struct.h"
#endif

#include "stateset/contains.h"
#include "stateset/insert.h"

#include "add_lamda_states.h"

void add_lamda_states(struct stateset* stateset)
{
	bool changed = true;
	ENTER;
	
	while (changed)
	{
		dpv(stateset->n);
		
		changed = false;
		
		for (struct avl_node_t* node = stateset->tree.head; node; node = node->next)
		{
			struct regex* state = node->item;
			
			for (size_t i = 0, n = state->lambda_transitions.n; i < n; i++)
			{
				struct regex* lambda = state->lambda_transitions.data[i];
				
				if (!stateset_contains(stateset, lambda))
				{
					stateset_insert(stateset, lambda);
					changed = true;
				}
			}
		}
	}
	
	EXIT;
}
















