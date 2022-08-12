
#include <debug.h>

#include <avl/search.h>

#include "node/struct.h"
#include "struct.h"
#include "get.h"

struct tokenset* yacc_stateinfo_get(
	struct yacc_stateinfo* this,
	struct gegex* state)
{
	struct avl_node_t* node = avl_search(this->tree, &state);
	assert(node);
	struct yacc_stateinfo_node* ytnode = node->item;
	return ytnode->lookaheads;
}

