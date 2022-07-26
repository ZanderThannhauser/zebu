
#include <debug.h>

#include <avl/new.h>

#include <memory/smalloc.h>

#include "../cache/compare.h"
#include "../cache/free.h"

#include "struct.h"
#include "new.h"

struct regex_ll* new_regex_ll()
{
	ENTER;
	
	struct regex_ll* this = smalloc(sizeof(*this));
	
	this->head = NULL;
	this->cache = new_avl_tree(compare_regex_caches, free_regex_cache);
	
	EXIT;
	return this;
}

