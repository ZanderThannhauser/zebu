
#include <debug.h>

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

struct regextree* new_regextree()
{
	ENTER;
	
	TODO;
	#if 0
	struct regextree* this = smalloc(sizeof(*this));
	
	this->tree = new_avl_tree(compare, NULL);
	this->n = 0;
	
	EXIT;
	return this;
	#endif
}

