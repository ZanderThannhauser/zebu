
#include <debug.h>

#include <avl/tree_t.h>

#include "node.h"
#include "struct.h"
#include "foreach.h"

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(
		struct string* name,
		enum structinfo_node_type type,
		struct string* grammar))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* const ele = node->item;
		runme(ele->name, ele->type, ele->grammar.name);
	}
	
	EXIT;
}

