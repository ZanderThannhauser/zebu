
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "0.highest.h"
#include "1.complement.h"

charset_t read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	charset_t retval;
	ENTER;
	
	if (tokenizer->token == t_emark)
	{
		TODO;
		#if 0
		TODO;
/*		read_token(tokenizer, charset_root_machine);*/
		
		charset_t inner = read_highest_charset(tokenizer, scope);
		
		EXIT;
		return ~inner;
		#endif
	}
	else
	{
		retval = read_highest_charset(tokenizer, scope);
	}
	
	EXIT;
	return retval;
}


















