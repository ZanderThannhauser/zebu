
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_stateinfo_nodes(const void* a, const void* b)
{
	const struct stateinfo_node *A = a, *B = b;
	if (A->trie > B->trie)
		return +1;
	if (A->trie < B->trie)
		return -1;
	return 0;
}

