
#include <assert.h>

#include <debug.h>

#include "charset/free.h"

#include "../tokenizer/struct.h"

#include "2.intersect.h"
#include "3.symdiff.h"

struct charset* read_symdiff_charset(
	struct tokenizer* tokenizer,
	struct scope* scope)
{
	ENTER;
	
	struct charset* retval;
	
	struct charset* inner = read_intersect_charset(tokenizer, scope);
	
	if (tokenizer->token == t_caret)
	{
		TODO;
	}
	else
	{
		retval = inner;
	}
	
	EXIT;
	return retval;
}









	#if 0
	struct charset* retval;
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
	#endif

