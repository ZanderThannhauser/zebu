
#if 0
#include <debug.h>

#include "free.h"

void free_lex_state_cache(void* a)
{
	struct cache *A = a;
	free(A);
}

#endif
