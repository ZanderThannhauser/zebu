
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_strset(struct strset* this)
{
	ENTER;
	
	free(this->data);
	free(this);
	
	EXIT;
}

