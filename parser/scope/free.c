
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "pop.h"
#include "free.h"

void free_scope(struct scope* this)
{
	ENTER;
	
	while (this->layer)
	{
		scope_pop(this);
	}
	
	free(this->prefix.chars);
	free(this);
	
	EXIT;
}
