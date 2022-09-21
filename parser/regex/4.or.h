
#include <regex/rbundle.h>

struct tokenizer;
struct scope;

struct rbundle read_or_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
);
