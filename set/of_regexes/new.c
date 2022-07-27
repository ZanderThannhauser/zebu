
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct regexset* new_regexset()
{
	ENTER;
	struct regexset* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	EXIT;
	return this;
}

