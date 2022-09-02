
#include <debug.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct structinfo* new_structinfo(struct string* name)
{
	ENTER;
	
	dpvs(name);
	
	struct structinfo* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->tree = avl_alloc_tree(compare_structinfo_nodes, free_structinfo_node);
	
	EXIT;
	return this;
}

