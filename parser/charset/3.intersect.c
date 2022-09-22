
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"

#include "2.range.h"
#include "3.intersect.h"

charset_t read_intersect_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_range_charset(tokenizer, scope);
	
	while (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer);
		
		charset_t right = read_range_charset(tokenizer, scope);
		
		left &= right;
	}
	
	EXIT;
	return left;
}






