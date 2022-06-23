
#include <debug.h>

#include <valgrind/memcheck.h>

#include "private/remove_from_ll.h"

#include "header.h"
#include "footer.h"
#include "struct.h"
#include "prettyprint.h"
#include "sbrk.h"
#include "malloc.h"

static void* private_arena_find_block(struct memory_arena* this, size_t* size)
{
	ENTER;
	
	dpv(*size);
	
	struct memory_arena_header *i, *block = NULL;
	
	for (i = this->free_list.head; !block && i; i = i->next)
	{
		assert(!i->is_alloc);
		
		if (*size <= i->size)
			block = i;
	}
	
	HERE;
	
	if (!block)
		block = arena_sbrk(this, *size);
	
	dpv(block);
	
	if (block->size >= *size
		+ sizeof(struct memory_arena_header)
		+ sizeof(struct memory_arena_footer))
	{
		size_t split_size = block->size - *size;
		
		dpv(split_size);
		
		struct memory_arena_header* newblock = (void*) block + *size;
		struct memory_arena_footer* footer = (void*) block + block->size - sizeof(*footer);
		
		assert((void*) footer - (void*) newblock + sizeof(*footer) == split_size);
		
		dpv(newblock);
		
		// do split, adjust linked-list:
		newblock->is_alloc = false;
		newblock->size = split_size;
		
		newblock->prev = block->prev;
		newblock->next = block->next;
		
		dpv(newblock->prev);
		dpv(newblock->next);
		
		footer->header = newblock;
		
		dpv(footer->header);
		
		if (block->prev)
			block->prev->next = newblock;
		else
			this->free_list.head = newblock;
		
		if (block->next)
			block->next->prev = newblock;
		else
			this->free_list.tail = newblock;
	}
	else
	{
		// don't do split, remove from linked-list
		remove_from_ll(this, block);
		
		*size = block->size;
	}
	
	EXIT;
	return block;
}

void* arena_malloc(struct memory_arena* this, size_t user_size)
{
	int error = 0;
	struct memory_arena_header* header;
	struct memory_arena_footer* footer;
	ENTER;
	
	size_t block_size = sizeof(*header) + user_size + sizeof(*footer);
	
	dpv(block_size);
	
	void* ptr = private_arena_find_block(this, &block_size);
	
	dpv(block_size);
	
	dpv(ptr);
	
	header = ptr, footer = ptr + block_size - sizeof(*footer);
	
	header->is_alloc = true;
	header->size = block_size;
	
	footer->header = header;
	
	void* payload = ptr + sizeof(*header);
	
	VALGRIND_MAKE_MEM_UNDEFINED(payload,
		block_size - sizeof(*footer) - sizeof(*header));
	
	#ifdef DEBUGGING
	arena_prettyprint(this);
	#endif
	
	EXIT;
	return payload;
}











