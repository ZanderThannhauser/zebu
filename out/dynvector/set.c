
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/insert.h>

#include "struct.h"
#include "set.h"

void dynvector_set(
	struct dynvector* this,
	unsigned index,
	unsigned value)
{
	ENTER;
	
	if (index > this->length)
	{
		this->length = index;
	}
	
	dpv(index);
	dpv(value);
	
	#ifdef WITH_ARENAS
	struct dynvector_node* node = arena_malloc(this->arena, sizeof(*node));
	#else
	struct dynvector_node* node = malloc(sizeof(*node));
	#endif
	
	node->i = index;
	node->v = value;
	
	avl_insert(this->list, node);
	
	EXIT;
}
#endif
