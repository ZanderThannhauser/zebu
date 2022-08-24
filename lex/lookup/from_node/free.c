
#ifdef WITHOUT_ARENAS

#include <stdlib.h>

#include <assert.h>
#include <debug.h>

#include "free.h"

void free_dfa_from_id_node(void* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}

#endif
