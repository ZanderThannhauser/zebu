
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct fragment* new_fragment(char* name, struct regex* regex)
{
	ENTER;
	
	struct fragment* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->regex = regex;
	
	EXIT;
	return this;
}

