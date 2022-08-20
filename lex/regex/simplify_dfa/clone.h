
struct avl_tree_t;
struct regex;
struct memory_arena;

struct regex* regex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct regex* original_start,
	struct memory_arena* arena);
