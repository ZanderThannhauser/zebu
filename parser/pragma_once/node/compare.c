
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_pragma_once_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct pragma_once_node* A = a, *B = b;
	ENTER;
	
	if (A->dev > B->dev)
		cmp = +1;
	else if (A->dev < B->dev)
		cmp = -1;
	else if (A->ino > B->ino)
		cmp = +1;
	else if (A->ino < B->ino)
		cmp = -1;
	
	EXIT;
	return cmp;
}




