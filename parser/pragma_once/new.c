
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include "node/compare.h"
#include "node/free.h"
#include "struct.h"
#include "new.h"

struct pragma_once* new_pragma_once()
{
	ENTER;
	
	struct pragma_once* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_pragma_once_nodes, free_pragma_once_node);
	
	EXIT;
	return this;
}
