
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct options* new_options()
{
	ENTER;
	
	struct options* this = malloc(sizeof(*this));
	
	this->skip = NULL;
	
	EXIT;
	return this;
}
