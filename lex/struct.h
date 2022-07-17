
#include <stdbool.h>

#include <avl/tree_t.h>

struct lex
{
	bool verbose;
	
	unsigned next_id;
	
	struct avl_tree_t* dfa_to_id; // token -> token id
	
	// # set(token ids) -> machine id
};
