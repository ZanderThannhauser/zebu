
#include <debug.h>

#include "4.or.h"
#include "root.h"

struct gbundle read_root_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	struct gbundle inner = read_or_production(tokenizer, options, scope, lex);
	
	EXIT;
	return inner;
}
