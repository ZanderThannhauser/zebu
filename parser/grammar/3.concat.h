
struct options;

#include <gegex/gbundle.h>

struct lex;
struct scope;
struct memory_arena;

struct gbundle read_concat_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
