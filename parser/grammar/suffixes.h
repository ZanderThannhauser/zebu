
#include "gbundle.h"

struct gbundle read_suffixes_production(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
