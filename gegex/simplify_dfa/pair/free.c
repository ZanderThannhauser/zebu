
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_gegex_pair(void* ptr)
{
	struct gegex_pair* this = ptr;
	ENTER;
	
	free(this);
	
	EXIT;
}
