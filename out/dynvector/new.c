
#include <memory/smalloc.h>

#include <stdlib.h>

#include <avl/new.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare_dynvector_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	const struct dynvector_node* A = a, *B = b;
	
	if (A->i > B->i)
		cmp = +1;
	else if (A->i < B->i)
		cmp = -1;
	
	EXIT;
	return cmp;
}

static void free_dynvector_node(void* ptr)
{
	ENTER;
	
	struct dynvector_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct dynvector* new_dynvector(const char* name)
{
	ENTER;
	
	struct dynvector* this = smalloc(sizeof(*this));
	
	this->list = new_avl_tree(compare_dynvector_nodes, free_dynvector_node);
	this->length = 0;
	this->name = name;
	
	EXIT;
	return this;
}




















