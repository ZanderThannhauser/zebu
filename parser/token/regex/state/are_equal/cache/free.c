
#include <debug.h>

#include "free.h"

void free_cache(void* a)
{
	struct cache *A = a;
	free(A);
}

