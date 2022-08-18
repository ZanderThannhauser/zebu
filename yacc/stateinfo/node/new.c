
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct yacc_stateinfo_node* new_yacc_stateinfo_node(
	struct gegex* state,
	const char* grammar,
	struct tokenset* lookaheads)
{
	ENTER;
	
	struct yacc_stateinfo_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	this->grammar = grammar;
	this->lookaheads = lookaheads;
	
	EXIT;
	return this;
}

