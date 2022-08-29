
#include "../rbundle.h"

struct rbundle read_dot_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip
);
