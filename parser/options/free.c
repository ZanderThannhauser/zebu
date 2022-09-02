
#include <debug.h>

#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <regex/state/free.h>

#include "struct.h"
#include "free.h"

void free_options(struct options* this)
{
	ENTER;
	
	free_regex(this->skip);
	
	free(this);
	
	EXIT;
}











