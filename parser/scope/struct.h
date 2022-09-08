
#include <stddef.h>

#include <avl/tree_t.h>

struct scope
{
	// prefix-appended, not owned by scope:
	struct avl_tree_t* grammar; // struct named_grammar*
	
	struct {
		char* chars;
		size_t n, cap;
	} prefix;
	
	struct scope_layer {
		// all local names, all locally owned:
		struct avl_tree_t* charsets;       // struct named_charset*
		struct avl_tree_t* fragments;      // struct named_token*
		struct avl_tree_t* inline_grammar; // struct named_gbundle*
		
		size_t prefix_len;
		
		unsigned sublayer_counter;
		
		struct scope_layer* prev;
	}* layer;
};

