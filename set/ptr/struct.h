
struct ptrset
{
	struct avl_tree_t* tree;
	unsigned refcount;
	
	#ifdef VERBOSE
	unsigned n;
	#endif
};

