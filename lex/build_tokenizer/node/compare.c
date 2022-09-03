
#include <debug.h>

#include <set/unsigned/compare.h>

#include "struct.h"
#include "compare.h"

int compare_build_tokenizer_nodes(const void* a, const void* b)
{
	const struct build_tokenizer_node* A = a, *B = b;
	
	return compare_unsignedsets(A->given, B->given);
}

