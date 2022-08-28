
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void regexset_foreach(
	struct regexset* this,
	void (*runme)(struct regex* state))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct regex* to = node->item;
		runme(to);
	}
	
	EXIT;
}

