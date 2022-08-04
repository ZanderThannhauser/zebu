
struct yacc_shared
{
	struct heap* todo;
	
	struct avl_tree_t* grammar; // named_gegex
	
	struct avl_tree_t* new_grammar; // named_yacc_state
	
	struct avl_tree_t* gegex_to_trie; // gegex -> name (char*)
	
	unsigned next_trie_id, EOF_token_id;
	
	struct {
		struct avl_tree_t *sets; // named_tokensets
		struct avl_tree_t *dependant_of, *dependant_on; // named_strsets
	} firsts, lookaheads;
};
