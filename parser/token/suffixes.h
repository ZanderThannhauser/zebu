
#include "rbundle.h"

struct regex_state;
struct tokenizer;
struct memory_arena;
struct scope;

struct rbundle read_suffixes_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope);
