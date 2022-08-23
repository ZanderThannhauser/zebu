
#include <assert.h>

#include <debug.h>

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_union.h"

#include "charset/struct.h"
#include "charset/union.h"
#include "charset/free.h"

#include "symdiff.h"
#include "union.h"

struct charset* read_union_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval = read_symdiff_charset(arena, tokenizer, scope);
	
	while (false
		|| tokenizer->token == t_oparen
		|| tokenizer->token == t_character_literal
		|| tokenizer->token == t_vertical_bar
		|| tokenizer->token == t_comma)
	{
		struct charset* left = retval;
		
		if (false
			|| tokenizer->token == t_vertical_bar
			|| tokenizer->token == t_comma)
		{
			read_token(tokenizer, charset_inside_union_machine);
		}
		
		struct charset* right = read_symdiff_charset(arena, tokenizer, scope);
		
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
				retval = charset_union(arena, left, right, false);
			}
		}
		
		free_charset(left), free_charset(right);
	}
	
	EXIT;
	return retval;
}










