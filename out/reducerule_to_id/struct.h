
struct reducerule_to_id_node
{
	struct string* reduce_as;
	
	struct string* grammar;
	
	struct reductioninfo* reductioninfo;
	
	struct structinfo* structinfo;
	
	unsigned id;
};

struct reducerule_to_id
{
	struct avl_tree_t* tree;
	unsigned next;
};

