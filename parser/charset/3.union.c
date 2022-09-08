
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_union.h"

#include "2.intersect.h"
#include "3.union.h"

charset_t read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	charset_t left = read_intersect_charset(tokenizer, scope);
	
	while (false
		|| tokenizer->token == t_oparen
		|| tokenizer->token == t_character_literal
		|| tokenizer->token == t_vertical_bar
		|| tokenizer->token == t_comma)
	{
		if (false
			|| tokenizer->token == t_vertical_bar
			|| tokenizer->token == t_comma)
		{
			read_token(tokenizer, charset_inside_union_machine);
		}
		
		charset_t right = read_intersect_charset(tokenizer, scope);
		
		left |= right;
	}
	
	EXIT;
	return left;
}

















