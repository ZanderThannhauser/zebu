
#include <debug.h>

#include "charset/inc.h"
#include "charset/free.h"

#include "../tokenizer/struct.h"

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
	
	if (tokenizer->token == t_vertical_bar)
	{
		TODO;
	}
	else
	{
		retval = inc_charset(left);
	}
	
	free_charset(left), free_charset(right);
	
	EXIT;
	return retval;
}

