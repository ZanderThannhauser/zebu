
struct options;
struct tokenizer;
struct scope;
struct lex;
struct memory_arena;

#include "gbundle.h"

struct gbundle read_root_production(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
