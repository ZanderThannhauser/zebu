
#include <stdbool.h>

#include <avl/tree_t.h>

struct lex
{
	bool verbose;
	
	unsigned next_id;
	
	struct avl_tree_t* dfa_to_id; // token -> token id
	struct avl_tree_t* dfa_from_id; // token id -> token
	
	struct {
		struct avl_tree_t* cache; // # set(token ids) -> machine id
	} tokenizer;
};
