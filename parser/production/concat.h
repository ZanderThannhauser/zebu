
#include "gbundle.h"

struct memory_arena;

struct gbundle read_concat_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex);
