
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct options* new_options()
{
	struct options* this = smalloc(sizeof(*this));
	
	this->start = NULL;
	
	this->skip = NULL;
	
	return this;
}

