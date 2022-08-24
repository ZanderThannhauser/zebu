
struct gegex;
struct memory_arena;

struct named_grammar* new_named_grammar(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct gegex* grammar);
