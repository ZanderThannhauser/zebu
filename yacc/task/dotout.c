
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "dotout.h"

#ifdef DEBUGGING
void task_dotout(struct task* this, struct shared* shared)
{
	ENTER;
	
	assert(this->inheritance->dotout);
	
	(this->inheritance->dotout)(this, shared);
	
	EXIT;
}

#endif
