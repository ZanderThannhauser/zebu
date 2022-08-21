
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct dependent_of_node* new_dependent_of_node(struct regex* a, struct regex* b)
{
	ENTER;
	
	TODO;
	#if 0
	struct dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = new_avl_tree(compare_pairs, free_pair);
	
	EXIT;
	return this;
	#endif
}

