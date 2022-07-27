
#include <assert.h>

#include <debug.h>

#include "charset/inc.h"
#include "charset/free.h"

#include "../tokenizer/struct.h"

#include "intersect.h"
#include "symdiff.h"

struct charset* read_symdiff_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	struct charset* left = read_intersect_charset(tokenizer, scope);
	struct charset* right = NULL;
	
	if (tokenizer->token == t_caret)
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











