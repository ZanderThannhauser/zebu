
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_unsignedset* new_named_unsignedset(
	struct string* name,
	struct unsignedset* unsignedset)
{
	ENTER;
	
	struct named_unsignedset* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->unsignedset = unsignedset;
	
	EXIT;
	return this;
}

