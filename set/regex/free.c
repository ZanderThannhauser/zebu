
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_regexset(struct regexset* this)
{
	ENTER;
	
	if (this)
	{
		avl_free_tree(this->tree);
		
		free(this);
	}
	
	EXIT;
}

