
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_dfa_from_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct dfa_from_id_node* A = a, *B = b;
	
	if (A->id > B->id)
		cmp = +1;
	else if (A->id < B->id)
		cmp = -1;
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}


