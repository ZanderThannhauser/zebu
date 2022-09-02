
struct stringset
{
	struct avl_tree_t* tree;
	unsigned n, refcount;
};

