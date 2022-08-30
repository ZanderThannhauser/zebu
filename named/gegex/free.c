
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_gegex(void* ptr)
{
	struct named_gegex* this = ptr;
	
	free(this->name);
	
	free(this);
}

