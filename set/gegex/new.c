
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	if (a < b)
		return -1;
	return 0;
}

struct gegexset* new_gegexset()
{
	ENTER;
	
	struct gegexset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, NULL);
	this->n = 0;
	
	EXIT;
	return this;
}

