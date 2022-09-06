
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(
		struct string* name,
		enum structinfo_node_kind kind,
		struct string* grammar))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		runme(ele->name, ele->kind, ele->grammar);
	}
}

