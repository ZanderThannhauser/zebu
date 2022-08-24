
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_gbundle(void* ptr)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	
	TODO;
	
	#else
	
	struct named_gbundle* const this = ptr;
	
	free(this->name);
	free(this);
	
	#endif
	
	EXIT;
}

