
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parser/charset/charset/free.h>

#include "struct.h"
#include "free.h"

void free_named_charset(void* ptr)
{
	struct named_charset* this = ptr;
	ENTER;
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this->name);
	#endif
	
	free_charset(this->charset);
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	free(this);
	#endif
	
	EXIT;
}

