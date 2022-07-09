
#include <debug.h>

#include "struct.h"
#include "header.h"
#include "footer.h"
#include "prettyprint.h"

void arena_prettyprint(
	struct memory_arena* this)
{
	size_t i, n;
	void *start, *end;
	typeof(*this->mmaps.data)* mentry;
	struct memory_arena_header* header;
	struct memory_arena_footer* footer;
	
	ENTER;
	
	dpv(this->free_list.head);
	dpv(this->free_list.tail);
	
	dpv(this->mmaps.n);
	
	struct memory_arena_header* free_head = NULL;
	struct memory_arena_header* free_tail = NULL;
	
	for (i = 0, n = this->mmaps.n; i < n; i++)
	{
		mentry = &this->mmaps.data[i];
		start = mentry->start, end = mentry->start + mentry->size;
		
		for (; start < end; start += header->size)
		{
			header = start;
			
			ddprintf(
				"@%p (%p): is_alloc = %5s, size = %4lu\n",
				header,
				(void*) header + sizeof(*header),
				header->is_alloc ? "true" : "false",
				header->size);
			
			if (!header->is_alloc)
			{
				ddprintf(
					"\t" "prev = %p, next = %p\n",
					header->prev,
					header->next);
				
				if (header->prev)
				{
					assert(!header->prev->is_alloc);
					assert(header->prev->next == header);
				}
				else
				{
					assert(!free_head);
					
					free_head = header;
				}
				
				if (header->next)
				{
					assert(!header->next->is_alloc);
					assert(header->next->prev == header);
				}
				else
				{
					assert(!free_tail);
					
					free_tail = header;
				}
			}
			
			footer = start + header->size - sizeof(*footer);
			
			assert(footer->header == header);
		}
	}
	
	assert(this->free_list.head == free_head);
	assert(this->free_list.tail == free_tail);
	
	EXIT;
}





















