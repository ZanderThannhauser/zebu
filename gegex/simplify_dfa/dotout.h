
struct gegexset;
struct avl_tree_t;

void gegex_simplify_dfa_dotout(
	struct gegexset* universe,
	struct avl_tree_t* connections,
	unsigned hopcount);
