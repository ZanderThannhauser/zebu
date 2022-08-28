
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_regex* new_named_regex(char* name, struct regex* regex)
{
	ENTER;
	
	struct named_regex* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->regex = regex;
	
	EXIT;
	return this;
}

