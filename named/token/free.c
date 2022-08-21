
#if 0
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_token(void* ptr)
{
	struct named_token* this = ptr;
	ENTER;
	
	free(this->name);
	
	free(this);
	
	EXIT;
}

#endif
