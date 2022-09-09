
struct stateinfo;
struct avl_tree_t;

void expand_stateinfo(
	struct stateinfo* stateinfo,
	struct avl_tree_t* named_tries,
	struct avl_tree_t* named_firsts);
