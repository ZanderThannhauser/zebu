
struct reducerule_to_id_node
{
	struct string* reduce_as;
	
	unsigned popcount;
	
	struct reductioninfo* reductioninfo;
	
	unsigned id;
};

struct reducerule_to_id
{
	struct avl_tree_t* tree;
	unsigned next;
};

