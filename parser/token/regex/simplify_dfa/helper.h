
struct avl_tree_t;
struct regex;

void simplify_dfa_helper(
	struct avl_tree_t* unique_nodes,
	struct regex* node);
