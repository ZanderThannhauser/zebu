
#include "gbundle.h"

struct tokenizer;
struct options;
struct scope;
struct lex;

struct gbundle read_suffixes_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
