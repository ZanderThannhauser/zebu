
#if 0
#include <debug.h>

#include "struct.h"
#include "add.h"

void lex_state_ll_add(
	struct lex_state_ll* this,
	struct lex_state* state)
{
	ENTER;
	
	struct lex_state_link* new = smalloc(sizeof(*new));
	
	new->element = state;
	new->next = this->head;
	
	this->head = new;
	
	EXIT;
}

#endif
