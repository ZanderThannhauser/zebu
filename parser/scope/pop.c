
#include <debug.h>

#include "struct.h"

#include "pop.h"

void scope_pop(struct scope* this)
{
	ENTER;
	
	struct scope_layer* head = this->layer;
	
	avl_free_nodes(&head->charsets);
	avl_free_nodes(&head->tokens);
	avl_free_nodes(&head->grammar);
	
	this->prefix.n = head->prefix_len;
	
	this->layer = head->prev;
	
	free(head);
	
	EXIT;
}

