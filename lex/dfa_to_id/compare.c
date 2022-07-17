
#include <debug.h>

#include <lex/regex/compare.h>

#include "struct.h"
#include "compare.h"

int compare_dfa_to_id_nodes(const void* a, const void* b)
{
	int cmp;
	ENTER;
	
	const struct dfa_to_id_node* A = a, *B = b;
	
	cmp = compare_regexes(A->token, B->token);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}


