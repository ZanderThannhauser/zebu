
struct options;
struct lex;
struct scope;
struct memory_arena;

#include "gbundle.h"

struct gbundle read_highest_production(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
