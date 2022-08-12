
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include "free.h"

void free_dfa_to_id_node(void* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}

