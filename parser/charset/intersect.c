
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_intersect.h"

#include "charset/struct.h"
#include "charset/union.h"
#include "charset/difference.h"
#include "charset/free.h"

#include "range.h"
#include "intersect.h"

struct charset* read_intersect_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	struct charset* inner = read_range_charset(arena, tokenizer, scope);
	
	if (tokenizer->token == t_ampersand)
	{
		#define left (inner)
		
		read_token(tokenizer, charset_inside_intersect_machine);
		
		struct charset* right = read_range_charset(arena, tokenizer, scope);
		
		if (left->is_complement)
		{
			if (right->is_complement)
			{
				retval = charset_union(arena, left, right, true);
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
				retval = charset_difference(arena, left, right, false);
			}
			else
			{
				TODO;
			}
		}
		
		free_charset(left), free_charset(right);
		
		#undef left
	}
	else
	{
		retval = inner;
	}
	
	EXIT;
	return retval;
}







