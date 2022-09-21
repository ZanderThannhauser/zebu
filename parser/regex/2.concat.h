
#include <regex/rbundle.h>

struct tokenizer;
struct scope;

struct rbundle read_concat_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
);
