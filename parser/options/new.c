
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct options* new_options()
{
	ENTER;
	
	struct options* this = malloc(sizeof(*this));
	
	this->skip = NULL;
	this->token_skip = NULL;
	
	#if 0
	this->disambiguatations.head = NULL;
	this->disambiguatations.tail = NULL;
	#endif
	
	EXIT;
	return this;
}
