
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_gegex(void* ptr)
{
	ENTER;
	
	struct named_gegex* this = ptr;
	
	free_string(this->name);
	
	free(this);
	
	EXIT;
}

