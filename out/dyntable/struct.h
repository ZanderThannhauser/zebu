
struct dyntable_node
{
	unsigned x, y, v;
};

struct dyntable
{
	struct avl_tree_t* tree;
	
	const char* name;
	
	unsigned width, height;
};

