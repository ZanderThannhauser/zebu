
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_lex(struct lex* this)
{
	ENTER;
	
	avl_free_tree(this->dfa_to_id);
	
	avl_free_tree(this->dfa_from_id);
	
	avl_free_tree(this->tokenizer_cache);
	
	free(this);
	
	EXIT;
}

