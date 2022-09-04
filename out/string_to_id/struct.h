
struct string_to_id_node
{
	struct string* string;
	
	unsigned id;
};

struct string_to_id
{
	struct avl_tree_t* tree;
	
	unsigned next;
};

