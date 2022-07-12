
#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "dotout.h"

void task_dotout(struct task* this, struct shared* shared)
{
	ENTER;
	
	assert(this->inheritance->dotout);
	
	(this->inheritance->dotout)(this, shared);
	
	EXIT;
}

