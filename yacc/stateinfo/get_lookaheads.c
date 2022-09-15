
#include <assert.h>
#include <debug.h>

#include <avl/search.h>

#include "node/struct.h"

#include "struct.h"
#include "get_lookaheads.h"

struct stateinfo_node* stateinfo_get_lookaheads(
	struct stateinfo* this,
	struct trie* trie)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &trie);
	
	assert(node);
	
	struct stateinfo_node* ele = node->item;
	
	EXIT;
	return ele;
}

