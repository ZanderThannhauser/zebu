
struct memory_arena;

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* cache,
	struct gegexset* unique_nodes,
	struct gegex* original_start,
	struct memory_arena* arena);
