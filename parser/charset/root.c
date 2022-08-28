
#include <debug.h>

#include "5.complement.h"
#include "root.h"

struct charset* read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval = read_complement_charset(tokenizer, scope);
	
	EXIT;
	return retval;
}
