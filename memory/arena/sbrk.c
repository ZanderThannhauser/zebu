
#include <stdio.h>

#include <sys/mman.h>

#include <valgrind/memcheck.h>

#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <memory/srealloc.h>

#include "defines/INITIAL_MMAP_LENGTH.h"

#include "struct.h"
#include "header.h"
#include "footer.h"
#include "sbrk.h"

static void setup_free_block(
	struct memory_arena* this,
	void* start,
	size_t size)
{
	#ifdef DEBUGGING
	VALGRIND_MAKE_MEM_UNDEFINED(start, size);
	#endif
	
	struct memory_arena_header* header = start;
	struct memory_arena_footer* footer = start + size - sizeof(*footer);
	
	header->is_alloc = false;
	header->size = size;
	
	footer->header = header;
	
	header->prev = this->free_list.tail;
	header->next = NULL;
	
	if (this->free_list.tail)
		this->free_list.tail->next = header;
	else
		this->free_list.head = header;
	
	this->free_list.tail = header;
}

void* arena_sbrk(
	struct memory_arena* this,
	size_t requested_size)
{
	if (this->mmaps.n > 0)
	{
		struct mentry* mentry = &this->mmaps.data[this->mmaps.n - 1];
		
		size_t old_size = mentry->size;
		size_t new_size = old_size * 2;
		
		if (requested_size > new_size)
			new_size = requested_size;
		
		if (mremap(mentry->start, old_size, new_size, 0) != MAP_FAILED)
		{
			// setup free block
			setup_free_block(this,
				mentry->start + old_size,
				new_size - old_size);
			
			mentry->size = new_size;
			
			return mentry->start + old_size;
		}
	}
	
	size_t size = this->mmaps.n
		? this->mmaps.data[this->mmaps.n - 1].size * 2
		: INITIAL_MMAP_LENGTH;
	
	if (requested_size > size)
		size = requested_size;
	
	void* start = NULL;
	
	if ((start = mmap(
		/* addr:   */  NULL,
		/* length: */  size,
		/* prot:   */  PROT_READ | PROT_WRITE,
		/* flags:  */  MAP_ANONYMOUS | MAP_PRIVATE,
		/* fd:     */ -1,
		/* offset: */  0)) == MAP_FAILED)
	{
		fprintf(stderr, "%s: mmap(): %m\n", argv0);
		exit(e_syscall_failed);
	}
	
	setup_free_block(this, start, size);
	
	if (this->mmaps.n + 1 >= this->mmaps.cap)
	{
		this->mmaps.cap = this->mmaps.cap * 2 ?: 1;
		this->mmaps.data = srealloc(this->mmaps.data, sizeof(struct mentry) * this->mmaps.cap);
	}
	
	this->mmaps.data[this->mmaps.n++] = (struct mentry) {
		.start = start,
		.size = size
	};
	
	return start;
}














