
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include "struct.h"
#include "free.h"

void free_named_regex(void* ptr)
{
	ENTER;
	
	struct named_regex* this = ptr;
	
	free_string(this->name);
	
	free(this);
	
	EXIT;
}
