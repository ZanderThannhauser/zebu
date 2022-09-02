
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct regex_dependent_of_node* new_regex_dependent_of_node(
	struct regex* a, struct regex* b)
{
	ENTER;
	
	struct regex_dependent_of_node* this = malloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_regex_pairs, free_regex_pair);
	
	EXIT;
	return this;
}

