
#include "charset.h"

struct tokenizer;
struct scope;

charset_t read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope);
