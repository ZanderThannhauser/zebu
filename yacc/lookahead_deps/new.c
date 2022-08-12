
#include <debug.h>

#include <avl/new.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct lookahead_deps* new_lookahead_deps()
{
	struct lookahead_deps* this = smalloc(sizeof(*this));
	
	this->dependant_of = new_avl_tree(compare_lookahead_deps_nodes, free_lookahead_deps_node);
	this->dependant_on = new_avl_tree(compare_lookahead_deps_nodes, free_lookahead_deps_node);
	
	return this;
}

