
struct options;

#include "gbundle.h"

struct lex;
struct scope;
struct memory_arena;

struct gbundle read_concat_production(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
