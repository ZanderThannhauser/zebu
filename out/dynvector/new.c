
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare(const void* a, const void* b)
{
	const struct dynvector_node* A = a, *B = b;
	
	if (A->i > B->i)
		return +1;
	else if (A->i < B->i)
		return -1;
	else
		return 0;
}

struct dynvector* new_dynvector(const char* name)
{
	ENTER;
	
	struct dynvector* this = smalloc(sizeof(*this));
	
	this->list = avl_alloc_tree(compare, free);
	
	this->length = 0;
	
	this->name = name;
	
	EXIT;
	return this;
}



















