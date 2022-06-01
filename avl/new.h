
struct avl_tree_t;

int new_avl_tree(
	struct avl_tree_t** out,
	int (*compare)(const void *, const void *),
	void (*freeitem)(void *));
