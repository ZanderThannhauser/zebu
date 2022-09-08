
#include <stdlib.h>
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct gegex_dependent_of_node* new_gegex_dependent_of_node(
	struct gegex* a, struct gegex* b)
{
	ENTER;
	
	struct gegex_dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_gegex_pairs, free_gegex_pair);
	
	EXIT;
	return this;
}
