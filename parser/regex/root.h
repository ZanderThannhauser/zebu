
#include <regex/rbundle.h>

struct tokenizer;
struct scope;

struct rbundle read_root_token_expression(
	struct tokenizer* tokenizer,
	struct scope* scope);
