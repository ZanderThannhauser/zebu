
#include <stddef.h>

#include <avl/tree_t.h>

struct scope
{
	struct avl_tree_t* charsets; // struct named_charset*
	struct avl_tree_t* tokens;   // struct named_token*
	struct avl_tree_t* grammar;  // struct named_grammar*
	
	struct {
		char* chars;
		size_t n, cap;
	} prefix;
	
	struct scope_layer {
		struct avl_tree_t* charsets; // struct named_name*
		struct avl_tree_t* tokens;   // struct named_name*
		struct avl_tree_t* grammar;  // struct named_name*
		
		size_t prefix_len;
		
		unsigned sublayer_counter;
		
		struct scope_layer* prev;
	}* layer;
};

