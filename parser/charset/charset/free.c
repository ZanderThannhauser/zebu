
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_charset(struct charset* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		free(this->chars);
		free(this);
	}
	
	EXIT;
}

