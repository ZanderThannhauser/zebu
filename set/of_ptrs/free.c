
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_ptrset(struct ptrset* this)
{
	ENTER;
	
	free(this->data);
	free(this);
	
	EXIT;
}

