
#if 0
#include <debug.h>

#include <avl/new.h>

#include <set/of_tokens/compare.h>

#include "struct.h"
#include "new.h"

static int compare_grammar_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct grammar_to_id_node* A = a, *B = b;
	
	cmp = strcmp(A->grammar, B->grammar);
	
	EXIT;
	return cmp;
}

static void free_grammar_to_id_node(void* ptr)
{
	ENTER;
	
	struct grammar_to_id_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct grammar_to_id* new_grammar_to_id()
{
	ENTER;
	
	struct grammar_to_id* this = smalloc(sizeof(*this));
	
	this->tree = new_avl_tree(compare_grammar_to_id_nodes, free_grammar_to_id_node);
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	EXIT;
	return this;
}


















#endif
