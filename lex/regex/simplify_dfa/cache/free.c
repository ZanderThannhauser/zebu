
#include <stdlib.h>

#include <debug.h>

#include "free.h"

void free_regex_cache(void* a)
{
	struct regex_cache *A = a;
	free(A);
}

