
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
	ENTER;
	
	dpv(start);
	dpv(size);
	
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
	
	EXIT;
}

int arena_sbrk(
	struct memory_arena* this,
	size_t requested_size)
{
	int error = 0;
	bool done = false;
	ENTER;
	
	dpv(requested_size);
	assert(requested_size);
	
	if (this->mmaps.n > 0)
	{
		typeof(*this->mmaps.data)* mentry = &this->mmaps.data[this->mmaps.n - 1];
		
		size_t old_size = mentry->size;
		size_t new_size = old_size * 2;
		dpv(new_size);
		
		if (mremap(mentry->start, old_size, new_size, 0) != MAP_FAILED)
		{
			// setup free block
			dpv(old_size);
			dpv(new_size);
			
			setup_free_block(this,
				mentry->start + old_size,
				new_size - old_size);
			
			mentry->size = new_size;
			done = true;
		}
	}
	
	if (!error && !done)
	{
		// create a new mmap, twice as big as the previous:
		
		void* start = NULL;
		size_t size = this->mmaps.n
			? this->mmaps.data[this->mmaps.n - 1].size * 2
			: INITIAL_MMAP_LENGTH;
		
		if (requested_size > size)
			size = requested_size;
		
		dpv(size);
		
		if ((start = mmap(
			/* addr:   */  NULL,
			/* length: */  size,
			/* prot:   */  PROT_READ | PROT_WRITE,
			/* flags:  */  MAP_ANONYMOUS | MAP_PRIVATE,
			/* fd:     */ -1,
			/* offset: */  0)) == MAP_FAILED)
		{
			fprintf(stderr, "%s: mmap(): %m\n", argv0);
			error = e_syscall_failed;
		}
		
		#ifdef DEBUGGING
		if (!error)
		{
			VALGRIND_MAKE_MEM_UNDEFINED(start, size);
		}
		#endif
		
		setup_free_block(this, start, size);
		
		if (!error && this->mmaps.n + 1 >= this->mmaps.cap)
		{
			this->mmaps.cap = this->mmaps.cap * 2 ?: 1;
			error = srealloc((void**) &this->mmaps.data, sizeof(*this->mmaps.data) * this->mmaps.cap);
		}
		
		dpv(this->mmaps.data);
		
		this->mmaps.data[this->mmaps.n].start = start;
		this->mmaps.data[this->mmaps.n].size = size;
		this->mmaps.n++;
		
		if (error && start && munmap(start, size) < 0)
			fprintf(stderr, "%s: munmap(): %m\n", argv0),
			error = e_syscall_failed;
	}
	
	EXIT;
	return error;
}














