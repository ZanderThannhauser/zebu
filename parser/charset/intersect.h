
struct tokenizer;
struct avl_tree_t;
struct scope;
struct memory_arena;

struct charset* read_intersect_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope);
