
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	const struct dyntable_node* A = a, *B = b;
	if (A->x > B->x)
		return +1;
	else if (A->x < B->x)
		return -1;
	else if (A->y > B->y)
		return +1;
	else if (A->y < B->y)
		return -1;
	else
		return +0;
}

struct dyntable* new_dyntable(const char* name)
{
	ENTER;
	
	struct dyntable* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare, free);
	
	this->name = name;
	
	this->width = 0;
	this->height = 0;
	
	EXIT;
	return this;
}
















