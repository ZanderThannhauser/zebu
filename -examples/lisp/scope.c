
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "argv0.h"
#include "avl.h"
#include "scope.h"
#include "value.h"
#include "builtins.h"

struct scope
{
	struct scope_layer {
		struct avl_tree_t* tree;
		struct scope_layer* prev;
	}* head;
};

struct scope_node
{
	char* name; // owned;
	struct value* value;
};

static int compare_nodes(const void* a, const void* b)
{
	const struct scope_node *A = a, *B = b;
	return strcmp(A->name, B->name);
}

static void free_node(void* c)
{
	struct scope_node* node = c;
	free(node->name);
	free_value(node->value);
	free(node);
}

struct scope* new_scope(struct scope* prev)
{
	struct scope* this = malloc(sizeof(*this));
	
	this->head = NULL;
	
	scope_push(this);
	
	return this;
}

void scope_push(struct scope* this)
{
	struct scope_layer* layer = malloc(sizeof(*layer));
	layer->tree = avl_alloc_tree(compare_nodes, free_node);
	layer->prev = this->head;
	this->head = layer;
}

void scope_pop(struct scope* this)
{
	struct scope_layer* head = this->head;
	avl_free_tree(head->tree);
	this->head = head->prev;
	free(head);
}

struct value* scope_lookup(struct scope* this, const char* value)
{
	for (struct scope_layer* layer = this->head; layer; layer = layer->prev)
	{
		struct avl_node_t* node = avl_search(layer->tree, &value);
		
		if (node)
		{
			struct scope_node* ele = node->item;
			return inc_value(ele->value);
		}
	}
	
	fprintf(stderr, "%s: value '%s' not defined!\n", argv0, value);
	exit(1);
}

void scope_define(struct scope* this, const char* name, struct value* value)
{
	char* dup = strdup(name);
	struct scope_node* node = malloc(sizeof(*node));
	node->name = dup;
	node->value = value, value->refcount++;
	struct avl_node_t* out = avl_insert(this->head->tree, node);
	assert(out);
}

void scope_define_builtins(struct scope* this)
{
	#define X(string, func) \
	{ \
		struct value* builtin = new_builtin_value(func); \
		scope_define(this, string, builtin); \
		free_value(builtin); \
	}
	
	// boolean operations:
	X("&", and_builtin);
	X("|", or_builtin);
	X("bool", bool_builtin);
	
	// math operations:
	X("+", sum_builtin);
	X("-", subtract_builtin);
	X("*", product_builtin);
	X("%", mod_builtin);
	X("/", divide_builtin);
	X("^", expo_builtin);
	
	// comparison operations:
	X("<", less_builtin);
	X(">", greater_builtin);
	X("=", equals_builtin);
	
	// string operations:
	X("strconcat", strconcat_builtin);
	
	// list operations:
	X("concat", concat_builtin);
	X("prepend", prepend_builtin);
	X("append", append_builtin);
	X("map", map_builtin);
	X("list", list_builtin);
	X("range", range_builtin);
	X("filter", filter_builtin);
	X("reduce", reduce_builtin);
	X("first", first_builtin);
	X("len", len_builtin);
	
	// misc operations:
	X("lambda", lambda_builtin);
	X("define", define_builtin);
	X("if", if_builtin);
}

void free_scope(struct scope* this)
{
	while (this->head)
		scope_pop(this);
	free(this);
}


























