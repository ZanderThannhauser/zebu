
#include <avl/alloc_tree.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "node/compare.h"
#include "node/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex(bool verbose)
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->tokens = avl_alloc_tree(compare_nodes, free_node);
	
	this->next_id = 1;
	
	this->verbose = verbose;
	
	EXIT;
	return this;
}

