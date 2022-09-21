
struct options;
struct lex;
struct scope;
struct tokenizer;
struct memory_arena;

#include <gegex/gbundle.h>

struct gbundle read_or_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
