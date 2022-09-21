
struct options;
struct scope;
struct memory_arena;
struct lex;

#include <gegex/gbundle.h>

struct gbundle read_subdefinitions_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);







