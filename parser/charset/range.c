
#include <assert.h>

#include <stdlib.h>

#include <enums/error.h>

#include <debug.h>

#include <macros/min.h>
#include <macros/max.h>

#include "charset/struct.h"
#include "charset/inc.h"
#include "charset/free.h"
#include "charset/new_from_range.h"

#include "../tokenizer/struct.h"
#include "../tokenizer/read_token.h"
#include "../tokenizer/machines/charset/inside_range.h"

#include "complement.h"
#include "range.h"

struct charset* read_range_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	struct charset* retval;
	ENTER;
	
	struct charset* left = read_complement_charset(tokenizer, scope);
	struct charset* right = NULL;
	
	if (tokenizer->token == t_hypen)
	{
		read_token(tokenizer, charset_inside_range_machine);
		
		right = read_complement_charset(tokenizer, scope);
		
		if (false
			|| left->is_complement || left->len != 1
			|| right->is_complement || right->len != 1)
		{
			TODO;
			exit(e_bad_input_file);
		}
		
		char l = left->chars[0], r = right->chars[0];
		
		dpvc(l);
		dpvc(r);
		
		retval = new_charset_from_range(min(l, r), max(l, r));
	}
	else
	{
		retval = inc_charset(left);
	}
	
	free_charset(left), free_charset(right);
	
	EXIT;
	return retval;
}













