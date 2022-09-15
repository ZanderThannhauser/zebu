
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/root.h"

#include "0.highest.h"
#include "1.complement.h"

charset_t read_complement_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	if (tokenizer->token == t_emark)
	{
		read_token(tokenizer, charset_root_machine);
		
		charset_t inner = read_highest_charset(tokenizer, scope);
		
		EXIT;
		return ~inner;
	}
	else
	{
		charset_t inner = read_highest_charset(tokenizer, scope);
		EXIT;
		return inner;
	}
}


















