
#if 0
#include <stdlib.h>


#include <debug.h>

#include <avl/insert.h>

#include <arena/malloc.h>

#include "struct.h"
#include "set.h"

void dyntable_set(
	struct dyntable* this,
	unsigned x, unsigned y,
	unsigned value)
{
	ENTER;
	
	if (x > this->width)
	{
		this->width = x;
		dpv(this->width);
	}
	
	if (y > this->height)
	{
		this->height = y;
		dpv(this->height);
	}
	
	#ifdef WITH_ARENAS
	struct dyntable_node* node = arena_malloc(this->arena, sizeof(*node));
	#else
	struct dyntable_node* node = malloc(sizeof(*node));
	#endif
	
	node->x = x;
	node->y = y;
	node->v = value;
	
	ddprintf("%s[%u][%u] = %u\n", this->name, x, y, value);
	
	avl_insert(this->tree, node);
	
	EXIT;
}















#endif
