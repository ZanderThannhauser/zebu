
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct named_name* new_named_name(
	char* name,
	char* value)
{
	ENTER;
	
	struct named_name* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->value = value;
	
	dpvs(this->name);
	dpvs(this->value);
	
	EXIT;
	return this;
}

