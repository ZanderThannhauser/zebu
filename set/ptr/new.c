
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

struct ptrset* new_ptrset()
{
	ENTER;
	
	struct ptrset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, NULL);
	
	this->refcount = 1;
	
	#ifdef VERBOSE
	this->n = 0;
	#endif
	
	EXIT;
	return this;
}

