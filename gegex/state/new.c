
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct gegex* new_gegex()
{
	ENTER;
	
	struct gegex* this = smalloc(sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.cap = 0;
	this->transitions.n = 0;
	
	this->grammar_transitions.data = NULL;
	this->grammar_transitions.cap = 0;
	this->grammar_transitions.n = 0;
	
	this->lambda_transitions.data = NULL;
	this->lambda_transitions.cap = 0;
	this->lambda_transitions.n = 0;
	
	this->is_reduction_point = false;
	
	dpv(this);
	
	EXIT;
	return this;
}
