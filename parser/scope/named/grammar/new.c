
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct named_grammar* new_named_grammar(
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	struct named_grammar* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->start = start;
	this->end = end;
	
	dpvs(this->name);
	
	EXIT;
	return this;
}

