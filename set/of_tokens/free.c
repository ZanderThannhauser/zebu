
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_tokenset(struct tokenset* this)
{
	ENTER;
	
	if (this)
	{
		free(this->data);
		free(this);
	}
	
	EXIT;
}

