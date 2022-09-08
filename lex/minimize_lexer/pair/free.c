
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_lex_pair(void* ptr)
{
	struct lex_pair* this = ptr;
	ENTER;
	
	free(this);
	
	EXIT;
}
