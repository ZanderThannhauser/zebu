
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_reductioninfo(struct reductioninfo* this)
{
	if (this && !--this->refcount)
	{
		free_structinfo(this->structinfo);
		
		free_string(this->grammar);
		
		free_reductioninfo(this->prev);
		
		free(this);
	}
}

