
#if 0
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
	
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	struct dynvector_node* node = ptr;
	free(node);
	#endif
	
	EXIT;
}

struct dynvector* new_dynvector(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct dynvector* this = arena_malloc(arena, sizeof(*this));
	#else
	struct dynvector* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->list = avl_alloc_tree(arena, compare_dynvector_nodes, free_dynvector_node);
	#else
	this->list = avl_alloc_tree(compare_dynvector_nodes, free_dynvector_node);
	#endif
	
	this->length = 0;
	this->name = name;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}



















#endif
