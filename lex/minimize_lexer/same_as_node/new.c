
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct lex_same_as_node* new_lex_same_as_node(
	struct lex_state* state, struct lexstateset* set)
{
	ENTER;
	
	struct lex_same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}
