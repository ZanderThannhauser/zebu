
#include "gbundle.h"

struct tokenizer;
struct options;
struct scope;
struct lex;

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex);
