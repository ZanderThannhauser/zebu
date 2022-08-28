
#include <stdbool.h>

struct avl_tree_t;

struct lex
{
	struct avl_tree_t* dfa_to_id; // token -> token id
	
	struct avl_tree_t* dfa_from_id; // token id -> token
	
	unsigned next_id;
	
	unsigned EOF_token_id;
	
	struct avl_tree_t* tokenizer_cache; // # set(token ids) -> machine id
	
	struct {
		struct tokenset* literal_ids;
		struct tokenset* regex_ids;
	} disambiguations;
	
};
