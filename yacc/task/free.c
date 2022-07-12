
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_task(void* ptr)
{
	struct task* this = ptr;
	ENTER;
	
	if (this && !--this->refcount)
	{
		TODO;
	}
	
	EXIT;
}

