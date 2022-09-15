
#include <stdbool.h>

struct avl_tree_t;

struct lex
{
	struct avl_tree_t* dfa_to_id; // token -> token id
	
	struct avl_tree_t* dfa_from_id; // token id -> token
	
	struct avl_tree_t* tokenizer_cache; // # set of token ids -> lex_state
	
	unsigned next_id;
	
	unsigned whitespace_token_id, EOF_token_id;
};
