
#include "bundle.h"

struct regex_state;
struct tokenizer;
struct memory_arena;

struct bundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope);