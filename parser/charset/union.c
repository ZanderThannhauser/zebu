
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
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct charset* retval = read_symdiff_charset(arena, tokenizer, scope);
	#else
	struct charset* retval = read_symdiff_charset(tokenizer, scope);
	#endif
	
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
		
		#ifdef WITH_ARENAS
		struct charset* right = read_symdiff_charset(arena, tokenizer, scope);
		#else
		struct charset* right = read_symdiff_charset(tokenizer, scope);
		#endif
		
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
				#ifdef WITH_ARENAS
				retval = charset_union(arena, left, right, false);
				#else
				retval = charset_union(left, right, false);
				#endif
			}
		}
		
		free_charset(left), free_charset(right);
	}
	
	EXIT;
	return retval;
}










