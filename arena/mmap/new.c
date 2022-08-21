
#include <debug.h>

#include "../struct.h"

#include "../stdlib/realloc.h"

#include "malloc.h"
#include "resize.h"
#include "free.h"

#include "new.h"

struct memory_arena* new_mmap_arena()
{
	ENTER;
	
	struct memory_arena* this = malloc(sizeof(*this));
	
	this->free_list.head = NULL;
	this->free_list.tail = NULL;
	
	this->mmaps.data = NULL;
	this->mmaps.cap = 0;
	this->mmaps.n = 0;
	
	this->malloc = mmap_malloc;
	this->realloc = stdlib_realloc;
	this->resize = mmap_resize;
	this->free = mmap_free;
	
	EXIT;
	return this;
}











