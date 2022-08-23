
struct options;
struct scope;
struct memory_arena;
struct lex;

#include "gbundle.h"

struct gbundle read_subdefinitions_production(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
