
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct yacc_state* new_yacc_state()
{
	ENTER;
	
	struct yacc_state* this = smalloc(sizeof(*this));
	
	this->tokenizer_start = NULL;
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.n = 0;
	this->grammar_transitions.cap = 0;
	
	this->reduce_transitions.data = NULL;
	this->reduce_transitions.n = 0;
	this->reduce_transitions.cap = 0;
	
	EXIT;
	return this;
}

