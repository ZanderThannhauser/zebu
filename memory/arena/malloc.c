
#include <debug.h>

#include <valgrind/memcheck.h>

#include "private/remove_from_ll.h"

#include "header.h"
#include "footer.h"
#include "struct.h"
#include "prettyprint.h"
#include "sbrk.h"
#include "malloc.h"

static int private_arena_find_block(
	struct memory_arena* this,
	void** out, size_t* size)
{
	int error = 0;
	void* ptr;
	struct memory_arena_header *i, *block = NULL;
	ENTER;
	
	dpv(*size);
	
	for (i = this->free_list.head; !block && i; i = i->next)
		if (!i->is_alloc && *size <= i->size)
			ptr = block = i;
	
	if (!block)
	{
		// if there's no available free blocks call sbrk
		// to get another one.
		
		error = arena_sbrk(this, *size);
		
		ptr = block = this->free_list.tail;
		
		dpv(block);
	}
	
	if (!error)
	{
		dpv(block);
		
		if (block->size >= *size + sizeof(struct memory_arena_header) + sizeof(struct memory_arena_footer))
		{
			size_t split_size = block->size - *size;
			dpv(split_size);
			
			struct memory_arena_header* newblock = ptr + *size;
			struct memory_arena_footer* footer = ptr + block->size - sizeof(*footer);
			
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
	}
	
	if (!error)
		*out = ptr;
	
	EXIT;
	return error;
}

int arena_malloc(
	struct memory_arena* this,
	void** out, size_t user_size)
{
	int error = 0;
	void* ptr;
	size_t block_size;
	struct memory_arena_header* header;
	struct memory_arena_footer* footer;
	ENTER;
	
	#ifdef DEBUGGING
	arena_prettyprint(this);
	#endif
	
	block_size = 0
		+ sizeof(*header)
		+ user_size
		+ sizeof(*footer);
	
	dpv(block_size);
	
	error = private_arena_find_block(this, &ptr, &block_size);
	
	if (!error)
	{
		dpv(block_size);
		
		dpv(ptr);
		
		header = ptr;
		footer = ptr + block_size - sizeof(*footer);
		
		header->is_alloc = true;
		header->size = block_size;
		
		dpv(footer);
		
		footer->header = header;
		
		dpv(footer->header);
		
		void* payload = ptr + sizeof(*header);
		
		VALGRIND_MAKE_MEM_UNDEFINED(payload,
			block_size - sizeof(*footer) - sizeof(*header));
		
		*out = payload;
	}
	
	#ifdef DEBUGGING
	arena_prettyprint(this);
	#endif
	
	EXIT;
	return error;
}











