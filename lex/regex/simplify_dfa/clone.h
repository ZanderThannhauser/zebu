
struct avl_tree_t;
struct regex;
struct memory_arena;

struct regex* simplify_dfa_clone(
	struct regex_ll* unique_nodes,
	struct regex* original_start,
	struct memory_arena* arena);
