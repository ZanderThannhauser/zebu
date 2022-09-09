
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <set/unsigned/free.h>

#include "struct.h"
#include "free.h"

void free_named_unsignedset(void* ptr)
{
	struct named_unsignedset* this = ptr;
	
	free_string(this->name);
	
	free_unsignedset(this->unsignedset);
	
	free(this);
}

