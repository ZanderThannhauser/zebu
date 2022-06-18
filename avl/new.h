
struct avl_tree_t* new_avl_tree(
	int (*compare)(const void *, const void *),
	void (*freeitem)(void *));
