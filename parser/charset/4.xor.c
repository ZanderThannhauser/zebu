
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "3.intersect.h"
#include "4.xor.h"

charset_t read_xor_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_intersect_charset(tokenizer, scope);
	
	while (tokenizer->token == t_caret)
	{
		TODO;
		#if 0
		read_token(tokenizer, charset_inside_xor_machine);
		
		charset_t right = read_intersect_charset(tokenizer, scope);
		
		left ^= right;
		#endif
	}
	
	EXIT;
	return left;
}






