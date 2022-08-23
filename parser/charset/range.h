
struct scope;
struct tokenizer;
struct avl_tree_t;

struct charset* read_range_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope);
