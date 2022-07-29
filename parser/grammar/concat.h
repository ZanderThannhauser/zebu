
struct options;

#include "gbundle.h"

struct lex;
struct scope;
struct memory_arena;

struct gbundle read_concat_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
