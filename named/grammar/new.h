
struct memory_arena;
struct gegex;

struct named_grammar* new_named_grammar(
	struct memory_arena* arena,
	char* name,
	struct gegex* grammar);
