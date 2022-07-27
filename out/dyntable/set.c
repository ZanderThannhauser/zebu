
#include <memory/smalloc.h>

#include <debug.h>

#include <avl/safe_insert.h>

#include "struct.h"
#include "set.h"

void dyntable_set(
	struct dyntable* this,
	unsigned x, unsigned y,
	unsigned value)
{
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
	
	struct dyntable_node* node = smalloc(sizeof(*node));
	
	node->x = x;
	node->y = y;
	node->v = value;
	
	ddprintf("%s[%u][%u] = %u\n", this->name, x, y, value);
	
	safe_avl_insert(this->tree, node);
	
	
}
















