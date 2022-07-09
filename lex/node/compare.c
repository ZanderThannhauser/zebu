
#include <debug.h>

#include <parser/token/regex/compare.h>

#include "struct.h"
#include "compare.h"

int compare_nodes(const void* a, const void* b)
{
	int cmp;
	ENTER;
	
	const struct node* A = a, *B = b;
	
	cmp = compare_regexes(A->token, B->token);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}


