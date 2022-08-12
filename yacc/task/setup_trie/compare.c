
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_setup_trie_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	const struct setup_trie_task* A = (void*) a, *B = (void*) b;
	
	assert(a->kind == tk_setup_trie);
	assert(b->kind == tk_setup_trie);
	
	if (!!A->name > !!B->name)
		cmp = -1;
	else if (!!A->name < !!B->name)
		cmp = +1;
	else if (A->node > B->node)
		cmp = +1;
	else if (A->node < B->node)
		cmp = -1;
	
	return cmp;
}

