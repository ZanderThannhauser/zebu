
struct yacc_shared;
struct lex;
struct avl_tree_t;
struct memory_arena;

struct yacc_state* yacc(
	struct yacc_shared** out_shared,
	struct lex* lex,
	struct avl_tree_t* grammars,
	struct memory_arena* scratchpad);
