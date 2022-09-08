
struct avl_tree_t;
struct gegex;

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct gegex* original_start
);
