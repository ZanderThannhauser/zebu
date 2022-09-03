
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool stateinfo_contains(
	struct stateinfo* this,
	struct trie* trie)
{
	return !!avl_search(this->tree, &trie);
}

