
struct scope;
struct memory_arena;

#include "bundle.h"

struct bundle read_subdefinitions_production(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope,
	struct lex* lex);