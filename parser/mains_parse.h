
struct options;

struct lex;

void mains_parse(
	struct options* options,
	struct scope* scope,
	struct memory_arena* scratchpad,
	struct lex* lex,
	const char* path);
