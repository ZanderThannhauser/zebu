
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct named_grammar* new_named_grammar(
	char* name,
	struct gegex* grammar)
{
	ENTER;
	
	struct named_grammar* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->grammar = grammar;
	
	dpvs(this->name);
	
	EXIT;
	return this;
}

