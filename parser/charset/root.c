
#include <debug.h>

#include "union.h"

#include "root.h"

struct charset* read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval = read_union_charset(tokenizer, scope);
	
	EXIT;
	return retval;
}

