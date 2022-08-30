
#include <debug.h>

#include "5.complement.h"
#include "root.h"

struct cbundle read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct cbundle retval = read_complement_charset(tokenizer, scope);
	
	EXIT;
	return retval;
}
