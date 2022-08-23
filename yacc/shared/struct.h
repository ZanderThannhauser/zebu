
struct yacc_shared
{
	struct heap* todo;
	
	struct lex* lex;
	
	struct memory_arena* arena;
	
	struct memory_arena* tokenizer_arena;
	
	struct memory_arena* parser_arena;
	
	struct avl_tree_t* grammar; // named_gegex
	
	struct avl_tree_t* new_grammar; // named_lex_state
	
	struct avl_tree_t* gegex_to_trie; // gegex -> name (char*)
	
	unsigned next_trie_id, EOF_token_id;
	
	struct {
		struct avl_tree_t *sets; // named_tokensets
		struct avl_tree_t *dependant_of, *dependant_on; // named_strsets
	} firsts;
	
	struct avl_tree_t* stateinfo_to_state; // yacc_tree* -> yacc_state*
	
	struct yacc_state* yacc_start;
};
