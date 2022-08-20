
#include <debug.h>

#include "free.h"

void free_scope(struct scope* this)
{
	ENTER;
	
	// pop remaining layers
	TODO;
	
	// free fragment tree (and regexes)
	TODO;
	
	// free inline_grammar tree (and gegexes)
	TODO;
	
	free(this);
	
	EXIT;
}

