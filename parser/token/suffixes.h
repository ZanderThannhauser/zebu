
#include "rbundle.h"

struct regex_state;
struct tokenizer;
struct memory_arena;
struct scope;

struct rbundle read_suffixes_token_expression(
	struct memory_arena* token_arena,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip);
