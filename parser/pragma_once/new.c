
#include <stdlib.h>

#include <debug.h>

#include <avl/init_tree.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "compare.h"
#include "new.h"

struct pragma_once* new_pragma_once()
{
	struct pragma_once* this = smalloc(sizeof(*this));
	
	avl_init_tree(&this->tree, compare_node, free);
	
	return this;
}

