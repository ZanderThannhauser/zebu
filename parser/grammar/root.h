
struct tokenizer;
struct scope;
struct lex;
struct memory_arena;

#include "gbundle.h"

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
