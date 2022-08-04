
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_build_trie_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct build_trie_task* A = (void*) a, *B = (void*) b;
	ENTER;
	
	if (A->mirrorme > B->mirrorme)
		cmp = +1;
	else if (A->mirrorme < B->mirrorme)
		cmp = -1;
	
	EXIT;
	return cmp;
}

