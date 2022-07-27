
struct scope;

#include "rbundle.h"

struct regex_state;
struct tokenizer;
struct memory_arena;

struct rbundle read_prefixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope);
