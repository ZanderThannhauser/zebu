
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/compare.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "tokenset_to_id.h"
#include "new.h"

static int compare_tokenset_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct tokenset_to_id_node* A = a, *B = b;
	ENTER;
	
	if (A->is_tokenset > B->is_tokenset)
		cmp = +1;
	else if (A->is_tokenset < B->is_tokenset)
		cmp = -1;
	else if (A->is_tokenset)
		cmp = compare_tokensets(A->tokenset, B->tokenset);
	else
		cmp = strcmp(A->grammar, B->grammar);
	
	EXIT;
	return cmp;
}

static void free_tokenset_to_id_node(void* ptr)
{
	ENTER;
	
	TODO;
	#if 0
	struct tokenset_to_id_node* node = ptr;
	
	free(node);
	#endif
	
	EXIT;
}

struct tokenset_to_id* new_tokenset_to_id(
	struct memory_arena* arena)
{
	ENTER;
	
	struct tokenset_to_id* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_tokenset_to_id_nodes, free_tokenset_to_id_node);
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	this->arena = arena;
	
	{
		this->eof = new_tokenset(arena);
		tokenset_add(this->eof, 0); // 0 indicates EOF
		tokenset_to_id(this, this->eof);
	}
	
	EXIT;
	return this;
}


















