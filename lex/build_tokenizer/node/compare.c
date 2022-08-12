
#include <debug.h>

#include <set/of_tokens/compare.h>

#include "struct.h"
#include "compare.h"

int compare_build_tokenizer_nodes(const void* a, const void* b)
{
	const struct build_tokenizer_node* A = a, *B = b;
	
	int cmp = compare_tokensets(A->given, B->given);
	
	return cmp;
}

