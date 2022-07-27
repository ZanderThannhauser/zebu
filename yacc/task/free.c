
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "free.h"

void free_task(void* ptr)
{
	struct task* this = ptr;
	ENTER;
	
	if (this && !--this->refcount)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
	
	EXIT;
}

