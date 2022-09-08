
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_lex_simplify_task(struct lex_simplify_task* this)
{
	ENTER;
	
	free(this);
	
	EXIT;
}
