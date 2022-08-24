
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "free.h"

void free_gegex_to_trie(void* ptr)
{
	struct gegex_to_trie* this = ptr;
	ENTER;
	
	free(this);
	
	EXIT;
}

