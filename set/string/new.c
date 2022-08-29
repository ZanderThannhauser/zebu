
#include <debug.h>

#include "struct.h"
#include "new.h"

struct stringset* new_stringset()
{
	ENTER;
	
	struct stringset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree((void*) strcmp, free);
	
	EXIT;
	return this;
}

