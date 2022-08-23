
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "node.h"
#include "struct.h"
#include "new.h"

static int compare_node(const void* a, const void* b)
{
	int cmp = 0;
	const struct pragma_once_node* A = a, *B = b;
	ENTER;
	
	cmp = A->dev - B->dev ?: A->ino - B->ino;
	
	EXIT;
	return cmp;
}

static void free_node(void* ptr)
{
	struct pragma_once_node* node = ptr;
	ENTER;
	free(node);
	EXIT;
}

struct pragma_once* new_pragma_once(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct pragma_once* this = arena_malloc(arena, sizeof(*this));
	#else
	struct pragma_once* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->tree = avl_alloc_tree(arena, compare_node, free_node);
	#else
	this->tree = avl_alloc_tree(compare_node, free_node);
	#endif
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

