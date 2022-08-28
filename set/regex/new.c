
#include <debug.h>

#include "struct.h"
#include "new.h"

static int tree_compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

struct regexset* new_regexset()
{
	ENTER;
	
	struct regexset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(tree_compare, NULL);
	this->n = 0;
	
	EXIT;
	return this;
}

