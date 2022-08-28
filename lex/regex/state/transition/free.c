
#include <debug.h>

#include "free.h"

void free_regex_transition(void* ptr)
{
	ENTER;
	free(ptr);
	EXIT;
}

