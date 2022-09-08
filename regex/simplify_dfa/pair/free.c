
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_regex_pair(void* ptr)
{
	struct regex_pair* this = ptr;
	ENTER;
	
	free(this);
	
	EXIT;
}
