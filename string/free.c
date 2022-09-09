
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_string(void* ptr)
{
	struct string* const this = ptr;
	ENTER;
	
	if (this && !--this->refcount)
	{
		free(this->chars);
		free(this);
	}
	
	EXIT;
}

