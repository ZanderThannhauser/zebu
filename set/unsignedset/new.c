
#include <debug.h>

#include <set/unsigned/compare.h>
#include <set/unsigned/free.h>

#include "struct.h"
#include "new.h"

struct unsignedsetset* new_unsignedsetset()
{
	ENTER;
	
	struct unsignedsetset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_unsignedsets, free_unsignedset);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

