
struct avl_tree_t;
struct gegex;

void gegex_simplify_dfa_add_dep(
	struct avl_tree_t* dependent_of,
	struct gegex* a_on, struct gegex* b_on,
	struct gegex* a_of, struct gegex* b_of);
