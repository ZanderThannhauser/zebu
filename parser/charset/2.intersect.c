
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_intersect.h"

#include "1.range.h"
#include "2.intersect.h"

charset_t read_intersect_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_range_charset(tokenizer, scope);
	
	if (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, charset_inside_intersect_machine);
		
		charset_t right = read_range_charset(tokenizer, scope);
		
		EXIT;
		return left & right;
	}
	else
	{
		EXIT;
		return left;
	}
}






