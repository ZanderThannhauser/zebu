
struct avl_tree_t;

void avl_tree_foreach(
	struct avl_tree_t* this,
	void (*runme)(void*));
