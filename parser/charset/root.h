
struct memory_arena;
struct tokenizer;
struct avl_tree_t;
struct scope;

struct charset* read_root_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope);
