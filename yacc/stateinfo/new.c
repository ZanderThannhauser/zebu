
#include <debug.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct stateinfo* new_stateinfo()
{
	ENTER;
	
	struct stateinfo* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_stateinfo_nodes, free_stateinfo_node);
	
	EXIT;
	return this;
}

