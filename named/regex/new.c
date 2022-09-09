
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_regex* new_named_regex(
	struct string* name,
	struct regex* regex)
{
	ENTER;
	
	struct named_regex* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	this->regex = regex;
	
	EXIT;
	return this;
}

