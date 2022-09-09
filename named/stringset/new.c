
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct named_stringset* new_named_stringset(
	struct string* name,
	struct stringset* stringset)
{
	ENTER;
	
	struct named_stringset* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->stringset = stringset;
	
	EXIT;
	return this;
}

