
#include "charset.h"

struct tokenizer;
struct scope;

charset_t read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
