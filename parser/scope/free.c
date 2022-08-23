
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "pop.h"
#include "struct.h"
#include "free.h"

void free_scope(struct scope* this)
{
	ENTER;
	
	// pop remaining layers
	while (this->layer)
	{
		scope_pop(this);
	}
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this->prefix.chars);
	free(this);
	#endif
	
	EXIT;
}

