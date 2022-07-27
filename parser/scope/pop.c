
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"

#include "pop.h"

void scope_pop(struct scope* this)
{
	ENTER;
	
	struct scope_layer* head = this->layer;
	
	avl_free_tree(head->charsets);
	avl_free_tree(head->tokens);
	avl_free_tree(head->grammar);
	
	this->prefix.n = head->prefix_len;
	
	this->layer = head->prev;
	
	free(head);
	
	EXIT;
}

