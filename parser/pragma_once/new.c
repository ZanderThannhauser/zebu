
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "compare.h"
#include "new.h"

int new_pragma_once(struct pragma_once** new)
{
	int error = 0;
	ENTER;
	
	struct pragma_once* this = NULL;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		avl_init_tree(&this->tree, compare_node, free);
		
		*new = this;
	}
	
	EXIT;
	return error;
}

