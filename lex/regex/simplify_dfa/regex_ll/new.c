
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct regex_ll* new_regex_ll(struct avl_tree_t* cache)
{
	ENTER;
	
	struct regex_ll* this = smalloc(sizeof(*this));
	
	this->head = NULL;
	this->cache = cache;
	
	EXIT;
	return this;
}

