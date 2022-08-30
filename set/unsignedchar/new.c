
#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	const char *A = a, *B = b;
	
	if (*A > *B)
		return +1;
	else if (*A < *B)
		return -1;
	else
		return +0;
}

struct unsignedcharset* new_unsignedcharset()
{
	ENTER;
	
	struct unsignedcharset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, free);
	
	this->n = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

