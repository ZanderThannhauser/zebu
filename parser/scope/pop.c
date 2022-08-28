
#if 0
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include <arena/dealloc.h>
#include <arena/free.h>

#include "struct.h"

#include "pop.h"

void scope_pop(struct scope* this)
{
	ENTER;
	
	struct scope_layer* head = this->layer;
	
	#ifdef WITH_ARENAS
	free_memory_arena(head->arena);
	#else
	avl_free_tree(head->charsets);
	avl_free_tree(head->fragments);
	avl_free_tree(head->inline_grammar);
	#endif
	
	this->prefix.n = head->prefix_len;
	
	this->layer = head->prev;
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, head);
	#else
	free(head);
	#endif
	
	EXIT;
}
#endif
