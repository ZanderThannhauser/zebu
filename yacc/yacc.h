
struct lex;
struct avl_tree_t;

struct yacc_state* yacc(
	struct avl_tree_t* named_gegexes,
	struct avl_tree_t* extra_fields,
	struct lex* lex);
