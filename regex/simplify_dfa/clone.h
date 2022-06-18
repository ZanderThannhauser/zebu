
struct avl_tree_t;
struct regex;
struct memory_arena;

struct regex* simplify_dfa_clone(
	struct avl_tree_t* unique_nodes,
	struct regex* original_start,
	struct memory_arena* arena);
