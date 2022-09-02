
#include <debug.h>

#include "struct.h"
#include "new.h"

struct stringset* new_stringset()
{
	ENTER;
	
	struct stringset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_strings, free_string);
	
	this->n = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

