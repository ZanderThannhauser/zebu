
#include <debug.h>

#include <avl/tree_t.h>

#include "node/struct.h"
#include "struct.h"
#include "foreach.h"

void yacc_stateinfo_foreach(
	struct yacc_stateinfo* this,
	void (*runme)(struct gegex* state, const char* grammar, struct tokenset*))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct yacc_stateinfo_node* ele = node->item;
		
		runme(ele->state, ele->grammar, ele->lookaheads);
	}
	
	EXIT;
}

