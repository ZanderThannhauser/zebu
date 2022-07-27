
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct tokenset* new_tokenset()
{
	ENTER;
	
	struct tokenset* this = smalloc(sizeof(*this));
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

