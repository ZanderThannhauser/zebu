
#include <stdbool.h>

#include <avl/tree_t.h>

struct lex
{
	
	struct memory_arena* arena;
	
	struct avl_tree_t* dfa_to_id; // token -> token id
	struct avl_tree_t* dfa_from_id; // token id -> token
	
	unsigned next_id;
	
	unsigned EOF_token_id;
	
	struct {
		struct avl_tree_t* cache; // # set(token ids) -> machine id
	} tokenizer;
	
	struct {
		struct tokenset* literal_ids;
		struct tokenset* regex_ids;
	} disambiguations;
	
};
