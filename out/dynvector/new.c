
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

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
	
	TODO;
	#if 0
	struct dynvector_node* node = ptr;
	
	free(node);
	#endif
	
	EXIT;
}

struct dynvector* new_dynvector(
	struct memory_arena* arena,
	const char* name)
{
	ENTER;
	
	struct dynvector* this = arena_malloc(arena, sizeof(*this));
	
	this->list = avl_alloc_tree(arena, compare_dynvector_nodes, free_dynvector_node);
	this->length = 0;
	this->name = name;
	
	this->arena = arena;
	
	EXIT;
	return this;
}




















