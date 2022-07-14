
#include <stdbool.h>

#include <avl/tree_t.h>

struct lex
{
	bool verbose;
	
	unsigned next_id;
	
	struct avl_tree_t* tokens; // token -> token id
	
	// what if:
		// # set(token ids) -> machine id
};
