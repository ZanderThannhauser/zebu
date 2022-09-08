
struct avl_tree_t;
struct yacc_state;

void lex_minimize_traverse_and_clone(
	struct avl_tree_t* connections,
	struct yacc_state* start);
