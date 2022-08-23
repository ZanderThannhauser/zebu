
struct options;
struct lex;
struct scope;
struct tokenizer;
struct memory_arena;

#include "gbundle.h"

struct gbundle read_or_production(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
