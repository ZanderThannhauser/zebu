
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_gegex_to_tries(const void* a, const void* b)
{
	const struct gegex_to_trie *A = a, *B = b;
	if (A->gegex > B->gegex)
		return +1;
	else if (A->gegex < B->gegex)
		return -1;
	return 0;
}

