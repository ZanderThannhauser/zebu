
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_options(struct options* this)
{
	ENTER;
	
	free(this->start);
	
	free(this);
	
	EXIT;
}

