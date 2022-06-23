
#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_union.h"

#include "charset/struct.h"
#include "charset/inc.h"
#include "charset/union.h"
#include "charset/free.h"

#include "symdiff.h"
#include "union.h"

struct charset* read_union_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	struct charset* left = read_symdiff_charset(tokenizer, scope);
	struct charset* right = NULL;
	
	if (false
		|| tokenizer->token == t_vertical_bar
		|| tokenizer->token == t_comma)
	{
		read_token(tokenizer, charset_inside_union_machine);
		
		right = read_symdiff_charset(tokenizer, scope);
		
		if (left->is_complement)
		{
			if (right->is_complement)
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
			if (right->is_complement)
			{
				TODO;
			}
			else
			{
				retval = charset_union(left, right, false);
			}
		}
	}
	else
	{
		retval = inc_charset(left);
	}
	
	free_charset(left), free_charset(right);
	
	EXIT;
	return retval;
}










