
#include <gegex/gbundle.h>

struct tokenizer;
struct options;
struct scope;
struct lex;

struct gbundle read_identifier_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex);
