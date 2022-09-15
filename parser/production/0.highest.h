
struct options;
struct lex;
struct scope;
struct memory_arena;

#include "gbundle.h"

struct gbundle read_highest_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);




