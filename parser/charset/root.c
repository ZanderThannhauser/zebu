
#include <debug.h>

#include "4.complement.h"
#include "root.h"

charset_t read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t retval = read_complement_charset(tokenizer, scope);
	
	EXIT;
	return retval;
}
