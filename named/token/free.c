
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_token(void* ptr)
{
	struct named_token* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this->name);
	free(this);
	#endif
	
	EXIT;
}

