
#ifdef WITH_ARENAS

#include <assert.h>

#include <debug.h>

#include "private/remove_from_ll.h"

#include "header.h"
#include "footer.h"
#include "struct.h"
/*#include "prettyprint.h"*/
#include "dealloc.h"

void arena_dealloc(struct memory_arena* this, void* ptr)
{
	ENTER;
	
	if (!ptr)
	{
		EXIT;
		return;
	}
	
	struct memory_arena_header* header;
	struct memory_arena_footer* footer;
	
	header = ptr - sizeof(*header);
	footer = ((void*) header) + header->size - sizeof(*footer);
	
	assert(header->is_alloc);
	
	size_t i, n;
	struct mentry* mentry;
	
	for (i = 0, n = this->mmaps.n; i < n; i++)
	{
		mentry = &this->mmaps.data[i];
		
		if (mentry->start <= ptr && ptr < mentry->start + mentry->size)
		{
			break;
		}
	}
	
	assert(i < n);
	
	struct memory_arena_header* preheader;
	struct memory_arena_footer* prefooter;
	
	if (mentry->start < (void*) header &&
		!(preheader =
			(prefooter = (void*) header - sizeof(*prefooter))->header)->is_alloc)
	{
		remove_from_ll(this, preheader);
		
		header = preheader;
	}
	
	struct memory_arena_header* postheader;
	
	if ((void*) (footer + 1) < mentry->start + mentry->size &&
		!(postheader = (void*) footer + sizeof(*footer))->is_alloc)
	{
		// remove from linked list
		remove_from_ll(this, postheader);
		
		footer = (void*) postheader + postheader->size - sizeof(*footer);
	}
	
	header->is_alloc = false;
	header->size = (void*) footer - (void*) header + sizeof(*footer);
	
	header->prev = NULL;
	header->next = this->free_list.head;
	
	footer->header = header;
	
	if (this->free_list.head)
		this->free_list.head->prev = header;
	else
		this->free_list.tail = header;
	
	this->free_list.head = header;
	
	EXIT;
}














#endif
