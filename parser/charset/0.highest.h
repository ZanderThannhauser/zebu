
struct tokenizer;
struct scope;

#include "charset.h"

charset_t read_highest_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
