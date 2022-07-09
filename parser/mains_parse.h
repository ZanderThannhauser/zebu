
struct options;
struct memory_arena;
struct lex;
struct scope;

void mains_parse(
	struct options* options,
	struct scope* scope,
	struct memory_arena* scratchpad,
	struct lex* lex,
	const char* path);
