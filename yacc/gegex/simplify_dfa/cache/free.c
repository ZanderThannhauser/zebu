
#include <stdlib.h>

#include <debug.h>

#include "free.h"

void free_gegex_cache(void* a)
{
	struct gegex_cache *A = a;
	free(A);
}

