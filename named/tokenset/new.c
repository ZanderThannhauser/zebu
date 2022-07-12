
#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_tokenset* new_named_tokenset(const char* name, struct tokenset* tokenset)
{
	ENTER;
	
	struct named_tokenset* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->tokenset = tokenset;
	
	EXIT;
	return this;
}

