
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_named_charset(void* ptr)
{
	struct named_charset* this = ptr;
	ENTER;
	
	free_string(this->name);
	
	free(this);
	
	EXIT;
}
