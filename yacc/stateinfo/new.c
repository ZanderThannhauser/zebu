
#include <debug.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct yacc_stateinfo* new_yacc_stateinfo()
{
	TODO;
	#if 0
	struct yacc_stateinfo* this = smalloc(sizeof(*this));
	
	this->tree = new_avl_tree(compare_yacc_stateinfo_nodes, free_yacc_stateinfo_node);
	
	return this;
	#endif
}

