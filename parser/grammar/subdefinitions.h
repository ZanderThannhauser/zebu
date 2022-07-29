
struct scope;
struct memory_arena;
struct lex;

#include "gbundle.h"

struct gbundle read_subdefinitions_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
