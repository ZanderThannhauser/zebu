
#include <assert.h>

#include <stdlib.h>

#include <enums/error.h>

#include <debug.h>

#include <macros/min.h>
#include <macros/max.h>

#include "charset/struct.h"
#include "charset/free.h"
#include "charset/new_from_range.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_range.h"

#include "highest.h"
#include "range.h"

struct charset* read_range_charset(
	struct memory_arena* arena,
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	struct charset* inner = read_highest_charset(arena, tokenizer, scope);
	
	if (tokenizer->token == t_hypen)
	{
		#define left (inner)
		
		read_token(tokenizer, charset_inside_range_machine);
		
		struct charset* right = read_highest_charset(arena, tokenizer, scope);
		
		if (left->is_complement || right->is_complement)
		{
			TODO;
			exit(e_bad_input_file);
		}
		
		char l = left->chars[0], r = right->chars[right->len - 1];
		
		dpvc(l);
		dpvc(r);
		
		retval = new_charset_from_range(arena, min(l, r), max(l, r));
		
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









