
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_tokenset(struct tokenset* this)
{
	ENTER;
	
	if (this)
	{
		TODO;
		free(this->data);
		free(this);
	}
	
	EXIT;
}

