
#include <debug.h>

#include <memory/smalloc.h>

#include "named/name/compare.h"
#include "named/name/free.h"

#include "private/append_prefix.h"

#include "struct.h"
#include "push.h"

void scope_push(struct scope* this, const char* layer_name)
{
	ENTER;
	
	struct scope_layer* new = smalloc(sizeof(*new));
	
	avl_init_tree(&new->charsets, compare_named_names, free_named_name);
	avl_init_tree(&new->tokens,   compare_named_names, free_named_name);
	avl_init_tree(&new->grammar,  compare_named_names, free_named_name);
	
	new->prefix_len = this->prefix.n;
	
	new->prev = this->layer;
	
	this->layer = new;
	
	dpv(this->layer);
	
	private_scope_append_prefix(this, layer_name);
	
	EXIT;
}










