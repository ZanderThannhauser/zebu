
#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return 0;
}

struct lexstateset* new_lexstateset()
{
	ENTER;
	
	struct lexstateset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, NULL);
	
	this->len = 0;
	
	EXIT;
	return this;
}

