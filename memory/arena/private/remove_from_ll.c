
#include <debug.h>

#include "../struct.h"
#include "../header.h"

#include "remove_from_ll.h"

void remove_from_ll(
	struct memory_arena* this,
	struct memory_arena_header* block)
{
	ENTER;
	
	dpv(block);
	
	assert(!block->is_alloc);
	
	if (block->prev)
		block->prev->next = block->next;
	else
		this->free_list.head = block->next;
	
	if (block->next)
		block->next->prev = block->prev;
	else
		this->free_list.tail = block->prev;
	
	EXIT;
}

