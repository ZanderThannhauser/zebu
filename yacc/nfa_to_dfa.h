
struct lex;
struct avl_tree_t;
struct memory_arena;

struct yacc_state* yacc_nfa_to_dfa(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad);
