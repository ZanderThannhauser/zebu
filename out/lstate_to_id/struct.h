
struct lstate_to_id_node
{
	struct lex_state* lstate;
	
	unsigned id;
};

struct lstate_to_id
{
	struct avl_tree_t* tree;
	
	unsigned next;
};
