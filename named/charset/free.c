
#include <assert.h>

#include <debug.h>

#include <parser/charset/charset/free.h>

#include "struct.h"
#include "free.h"

void free_named_charset(void* ptr)
{
	struct named_charset* this = ptr;
	ENTER;
	
	free(this->name);
	
	free_charset(this->charset);
	
	free(this);
	
	EXIT;
}

