
#include <debug.h>

#include "charset/inc.h"
#include "charset/free.h"

#include "../tokenizer/struct.h"

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

