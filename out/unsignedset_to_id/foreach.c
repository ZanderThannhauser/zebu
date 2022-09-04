
#if 0
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void tokenset_to_id_foreach(
	struct tokenset_to_id* this,
	void (*per_tokenset)(const struct tokenset*, unsigned id))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct tokenset_to_id_node* const ele = node->item;
		
		if (ele->is_tokenset)
			per_tokenset(ele->tokenset, ele->id);
	}
	
	EXIT;
}

#endif
