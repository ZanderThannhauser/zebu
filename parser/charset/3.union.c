
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/union.h>
#include <set/unsignedchar/free.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_union.h"

#include "2.intersect.h"
#include "3.union.h"

struct cbundle read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct cbundle retval = read_intersect_charset(tokenizer, scope);
	
	while (false
		|| tokenizer->token == t_oparen
		|| tokenizer->token == t_character_literal
		|| tokenizer->token == t_vertical_bar
		|| tokenizer->token == t_comma)
	{
		struct cbundle left = retval;
		
		if (false
			|| tokenizer->token == t_vertical_bar
			|| tokenizer->token == t_comma)
		{
			read_token(tokenizer, charset_inside_union_machine);
		}
		
		struct cbundle right = read_intersect_charset(tokenizer, scope);
		
		if (left.is_complement)
		{
			if (right.is_complement)
			{
				TODO;
			}
			else
			{
				TODO;
			}
		}
		else
		{
			if (right.is_complement)
			{
				TODO;
			}
			else
			{
				retval = (struct cbundle) {
					.is_complement = false,
					.charset = unsignedcharset_union(left.charset, right.charset),
				};
			}
		}
		
		free_unsignedcharset(left.charset);
		free_unsignedcharset(right.charset);
	}
	
	EXIT;
	return retval;
}

















