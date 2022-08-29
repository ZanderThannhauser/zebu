
#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	const unsigned *A = a, *B = b;
	if (*A > *B)
		return +1;
	else if (*A < *B)
		return -1;
	else
		return +0;
}

struct unsignedset* new_unsignedset()
{
	ENTER;
	
	struct unsignedset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, free);
	
	EXIT;
	return this;
}

