
#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include "dfa_to_id/compare.h"
#include "dfa_to_id/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex(bool verbose)
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->dfa_to_id = avl_alloc_tree(compare_dfa_to_id_nodes, free_dfa_to_id_node);
	
	this->next_id = 1; // because token 0 is for EOF
	
	this->verbose = verbose;
	
	EXIT;
	return this;
}

