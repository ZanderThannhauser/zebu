
#include <debug.h>

#include <avl/tree_t.h>

#include <string/inc.h>
#include <string/free.h>

#include "node.h"
#include "struct.h"
#include "resolve_grammar_names.h"

void structinfo_resolve_grammar_names(
	struct structinfo* this,
	struct string* grammar)
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct structinfo_node* ele = node->item;
		
		switch (ele->type)
		{
			case snt_grammar_scalar:
			case snt_grammar_array:
			{
				free_string(ele->grammar.name);
				
				ele->grammar.name = inc_string(grammar);
				
				break;
			}
			
			default: break;
		}
	}
	
	EXIT;
}


