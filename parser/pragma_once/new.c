
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

struct pragma_once* new_pragma_once()
{
	ENTER;
	
	struct pragma_once* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree((void*) strcmp, free);
	
	EXIT;
	return this;
}
