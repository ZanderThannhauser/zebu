
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <set/string/free.h>

#include "struct.h"
#include "free.h"

void free_named_stringset(void* ptr)
{
	struct named_stringset* this = ptr;
	
	free_string(this->name);
	
	free_stringset(this->stringset);
	
	free(this);
}

