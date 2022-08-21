
#include <debug.h>

#include "../struct.h"

#include "malloc.h"
#include "realloc.h"
#include "resize.h"
#include "free.h"

#include "new.h"

struct memory_arena* new_child_arena(
	struct memory_arena* parent)
{
	ENTER;
	
	struct memory_arena* this = malloc(sizeof(*this));
	
	this->free_list.head = NULL;
	this->free_list.tail = NULL;
	
	this->mmaps.data = NULL;
	this->mmaps.cap = 0;
	this->mmaps.n = 0;
	
	this->malloc = child_malloc;
	this->realloc = child_realloc;
	this->resize = child_resize;
	this->free = child_free;
	
	this->child.parent = parent;
	
	EXIT;
	return this;
}
