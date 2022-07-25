
struct tokenizer;
struct scope;

struct memory_arena;

#include "gbundle.h"

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex);
