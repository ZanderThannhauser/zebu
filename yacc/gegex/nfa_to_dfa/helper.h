
struct gegex_mappings;
struct memory_arena;

struct gegex* gegex_nfa_to_dfa_helper(
	struct gegexset* stateset,
	struct avl_tree_t* mappings,
	struct memory_arena* arena);
