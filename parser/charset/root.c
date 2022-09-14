
#include <debug.h>

#include "5.union.h"
#include "root.h"

charset_t read_root_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t retval = read_union_charset(tokenizer, scope);
	
	EXIT;
	return retval;
}
