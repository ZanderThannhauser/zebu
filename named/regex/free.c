
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_regex(void* ptr)
{
	struct named_regex* this = ptr;
	
	free(this->name);
	
	free(this);
}

