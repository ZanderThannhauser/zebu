
struct avl_tree_t;

struct scope* new_scope(
	struct memory_arena* arena,
	struct memory_arena* grammar_arena,
	struct avl_tree_t* grammar);
