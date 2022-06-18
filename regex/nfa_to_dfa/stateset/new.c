
#include <avl/avl.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "state/compare.h"

#include "struct.h"
#include "new.h"

struct stateset* new_stateset()
{
	ENTER;
	
	struct stateset* this = smalloc(sizeof(*this));
	
	avl_init_tree(&this->tree, compare_states, NULL);
	
	this->n = 0;
	
	EXIT;
	return this;
}

