
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>
#include <arena/free.h>

#include "struct.h"

#include "pop.h"

void scope_pop(struct scope* this)
{
	ENTER;
	
	struct scope_layer* head = this->layer;
	
	// avl_free_tree(head->charsets);
	
	// avl_free_tree(head->fragments);
	
	// avl_free_tree(head->inline_grammar);
	
	free_memory_arena(head->arena);
	
	this->prefix.n = head->prefix_len;
	
	this->layer = head->prev;
	
	arena_dealloc(this->arena, head);
	
	EXIT;
}

