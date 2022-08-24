
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include <heap/free.h>

#include "struct.h"
#include "free.h"

void free_yacc_shared(struct yacc_shared* this)
{
	ENTER;
	
	free_heap(this->todo);
	
	avl_free_tree(this->new_grammar);
	
	avl_free_tree(this->firsts.sets);
	
	avl_free_tree(this->firsts.dependant_of);
	
	avl_free_tree(this->firsts.dependant_on);
	
	avl_free_tree(this->gegex_to_trie);
	
	avl_free_tree(this->stateinfo_to_state);
	
	free(this);
	
	EXIT;
}

