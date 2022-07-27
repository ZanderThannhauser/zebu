
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_gegexset(struct gegexset* this)
{
	ENTER;
	
	free(this->data);
	free(this);
	
	EXIT;
}

