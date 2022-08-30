
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void unsignedcharset_foreach(
	const struct unsignedcharset* this,
	void (*runme)(unsigned char value))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		unsigned char* element = node->item;
		runme(*element);
	}
}

