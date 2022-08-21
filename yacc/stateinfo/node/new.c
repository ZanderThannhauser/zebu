
#include <debug.h>

#include "struct.h"
#include "new.h"

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads)
{
	ENTER;
	
	TODO;
	#if 0
	struct yacc_stateinfo_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	this->grammar = grammar;
	this->lookaheads = lookaheads;
	
	EXIT;
	return this;
	#endif
}

