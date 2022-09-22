
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_named_structinfo(void* ptr)
{
	ENTER;
	
	struct named_structinfo* this = ptr;
	
	free_string(this->name);
	
	free_structinfo(this->structinfo);
	
	free(this);
	
	EXIT;
}

