
#include "charset.h"

struct tokenizer;
struct scope;

charset_t read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
