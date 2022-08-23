
struct avl_tree_t;

struct scope* new_scope(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	struct memory_arena* grammar_arena,
	#endif
	struct avl_tree_t* grammar);
