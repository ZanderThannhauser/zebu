
struct scope;

/*#include "bundle.h"*/
struct regex;
struct regex_state;
struct tokenizer;
struct memory_arena;

struct rbundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct regex* token_skip);
