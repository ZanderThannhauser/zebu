
struct avl_tree_t;

struct yacc_shared* new_yacc_shared(
	struct avl_tree_t* grammar,
	unsigned EOF_token_id);
