
#include <debug.h>

#include <set/of_tokens/free.h>

#include "struct.h"
#include "free.h"

void free_named_tokenset(void* a)
{
	struct named_tokenset* this = a;
	ENTER;
	
	free_tokenset(this->tokenset);
	
	free(a);
	
	EXIT;
}

