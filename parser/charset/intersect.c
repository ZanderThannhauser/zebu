
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_intersect.h"

#include "charset/struct.h"
#include "charset/inc.h"
#include "charset/union.h"
#include "charset/difference.h"
#include "charset/free.h"

#include "range.h"
#include "intersect.h"

struct charset* read_intersect_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct charset* retval;
	ENTER;
	
	struct charset* left = read_range_charset(tokenizer, scope);
	struct charset* right = NULL;
	
	if (tokenizer->token == t_ampersand)
	{
		read_token(tokenizer, charset_inside_intersect_machine);
		
		right = read_range_charset(tokenizer, scope);
		
		if (left->is_complement)
		{
			if (right->is_complement)
				retval = charset_union(left, right, true);
			else
			{
				TODO;
			}
		}
		else
		{
			if (right->is_complement)
				retval = charset_difference(left, right, false);
			else
			{
				TODO;
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















