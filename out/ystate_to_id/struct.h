
struct ystate_to_id_node
{
	struct yacc_state* ystate;
	
	unsigned id;
};

struct ystate_to_id
{
	struct avl_tree_t* tree;
	
	unsigned next;
};
