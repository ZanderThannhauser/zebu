
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_heap(struct heap* this)
{
	ENTER;
	
	free(this->data);
	free(this);
	
	EXIT;
}

