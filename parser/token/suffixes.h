
#include "rbundle.h"

struct regex_state;
struct tokenizer;
struct memory_arena;
struct scope;

struct rbundle read_suffixes_token_expression(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip);
