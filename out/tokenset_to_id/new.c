
#include <memory/smalloc.h>

#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <avl/new.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/compare.h>

#include "struct.h"
#include "tokenset_to_id.h"
#include "new.h"

static int compare_tokenset_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	
	const struct tokenset_to_id_node* A = a, *B = b;
	
	if (A->is_tokenset > B->is_tokenset)
		cmp = +1;
	else if (A->is_tokenset < B->is_tokenset)
		cmp = -1;
	else if (A->is_tokenset)
		cmp = compare_tokensets(A->tokenset, B->tokenset);
	else
		cmp = strcmp(A->grammar, B->grammar);
	
	return cmp;
}

static void free_tokenset_to_id_node(void* ptr)
{
	ENTER;
	
	struct tokenset_to_id_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct tokenset_to_id* new_tokenset_to_id()
{
	ENTER;
	
	struct tokenset_to_id* this = smalloc(sizeof(*this));
	
	this->tree = new_avl_tree(compare_tokenset_to_id_nodes, free_tokenset_to_id_node);
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	{
		this->eof = new_tokenset();
		tokenset_add(this->eof, 0); // 0 indicates EOF
		tokenset_to_id(this, this->eof);
	}
	
	EXIT;
	return this;
}


















