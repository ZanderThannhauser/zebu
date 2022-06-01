
#include <debug.h>

#include "node.h"
#include "compare.h"

int compare_node(const void* a, const void* b)
{
	int cmp = 0;
	const struct pragma_once_node* A = a, *B = b;
	ENTER;
	
	cmp = A->dev - B->dev ?: A->ino - B->ino;
	
	EXIT;
	return cmp;
}

