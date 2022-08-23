
struct avl_tree_t;
struct gegex;
struct memory_arena;

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct gegex* original_start,
	struct memory_arena* arena);
