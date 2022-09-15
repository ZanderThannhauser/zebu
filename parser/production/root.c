
#include <debug.h>

#include "4.or.h"
#include "root.h"

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle inner = read_or_production(tokenizer, scope, lex);
	
	EXIT;
	return inner;
}
