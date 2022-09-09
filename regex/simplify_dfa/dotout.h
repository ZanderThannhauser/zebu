
struct regexset;
struct avl_tree_t;

void simplify_dfa_dotout(
	struct regexset* universe,
	struct avl_tree_t* connections,
	unsigned hopcount);
