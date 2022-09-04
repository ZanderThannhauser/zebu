
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include "../pair/compare.h"
#include "../pair/free.h"

#include "struct.h"
#include "new.h"

struct lex_dependent_of_node* new_lex_dependent_of_node(
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct lex_dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_lex_pairs, free_lex_pair);
	
	EXIT;
	return this;
}
