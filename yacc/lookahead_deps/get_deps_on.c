
#include <stddef.h>
#include <debug.h>

#include <avl/search.h>

#include "node/struct.h"

#include "struct.h"
#include "get_deps_on.h"

struct gegexset* lookahead_get_deps_on(
	struct lookahead_deps* this,
	struct gegex* state)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->dependant_on, &state);
	
	if (node)
	{
		struct lookahead_deps_node* ldnode = node->item;
		EXIT;
		return ldnode->b;
	}
	else
	{
		EXIT;
		return NULL;
	}
}

