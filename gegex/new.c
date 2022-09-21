
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct gegex* new_gegex()
{
	ENTER;
	
	struct gegex* this = smalloc(sizeof(*this));
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->lambdas.data = NULL;
	this->lambdas.n = 0;
	this->lambdas.cap = 0;
	
	this->grammars.data = NULL;
	this->grammars.n = 0;
	this->grammars.cap = 0;
	
	this->accepts = false;
	
	EXIT;
	return this;
}

