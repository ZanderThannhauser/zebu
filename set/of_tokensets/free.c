
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_tokensetset(struct tokensetset* this)
{
	ENTER;
	
	// TODO; // should the elements be freed?
	
	free(this->data);
	
	free(this);
	
	EXIT;
}

