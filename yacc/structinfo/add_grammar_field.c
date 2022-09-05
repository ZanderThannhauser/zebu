
#include <debug.h>

#include "struct.h"
#include "add_grammar_field.h"

void structinfo_add_grammar_field(
	struct structinfo* this,
	struct string* name,
	struct string* grammar)
{
	ENTER;
	
	struct structinfo_node* node = smalloc(sizeof(*node));
	
	node->name = inc_string(name);
	
	node->kind = sin_grammar;
	
	node->grammar.name = inc_string(grammar);
	
	avl_insert(this->tree, node);
	
	EXIT;
}

