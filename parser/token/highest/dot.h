
#include "../rbundle.h"

struct tokenizer;
struct scope;

struct rbundle read_dot_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope
);
