
struct yacc_shared;
struct lex;
struct avl_tree_t;
struct memory_arena;

struct yacc_state* yacc(
	struct lex* lex,
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad);
