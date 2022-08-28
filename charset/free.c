
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_charset(struct charset* this)
{
	ENTER;
	
	if (this)
	{
		#ifdef WITH_ARENAS
		
		arena_dealloc(this->arena, this->chars);
		arena_dealloc(this->arena, this);
		
		#else
		
		free(this->chars);
		free(this);
		
		#endif
	}
	
	EXIT;
}

